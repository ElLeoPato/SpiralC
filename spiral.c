#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 800

typedef struct {
    unsigned char red, green, blue;
} Pixel;

void generateSpiral(Pixel* image) {
    double centerX = IMAGE_WIDTH / 2.0;
    double centerY = IMAGE_HEIGHT / 2.0;
    double angleStep = 0.1;
    double maxRadius = sqrt(centerX * centerX + centerY * centerY);
    
    for (double angle = 0; angle < 500; angle += angleStep) {
        double radius = angle * 0.5;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        
        int posX = (int)x;
        int posY = (int)y;
        
        if (posX >= 0 && posX < IMAGE_WIDTH && posY >= 0 && posY < IMAGE_HEIGHT) {
            Pixel* pixel = &image[posY * IMAGE_WIDTH + posX];
            
            pixel->red = (unsigned char)(255 * sin(angle) * cos(x) * sin(y));
            pixel->green = (unsigned char)(255 * sin(angle) * sin(x) * cos(y));
            pixel->blue = (unsigned char)(255 * cos(angle) * sin(x) * sin(y));
        }
    }
}

int main() {
    Pixel* image = (Pixel*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(Pixel));
    if (!image) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    generateSpiral(image);

    FILE* file = fopen("trippy_spiral.ppm", "wb");
    if (!file) {
        fprintf(stderr, "Error: Unable to create the output file\n");
        free(image);
        return 1;
    }

    fprintf(file, "P6\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    fwrite(image, sizeof(Pixel), IMAGE_WIDTH * IMAGE_HEIGHT, file);
    fclose(file);

    free(image);

    printf("Image successfully generated as 'trippy_spiral.ppm'\n");

    return 0;
}
