#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 320
#define HEIGHT 240

#define FILE_PATH "bad-apple.rle"

int main(void) {
	FILE *file = fopen(FILE_PATH, "w");
	if (file == NULL) { perror("Failed to open " FILE_PATH); return 1; }

	for (int file_i = 0; file_i <= 6571; file_i+=1) {
		char frame_path[32] = "frames/";
		sprintf(frame_path+7, "%04d.png", file_i);
		if (file_i % 100 == 0) { printf("encoding %s...\n", frame_path); }
		int image_w, image_h, image_channels;
		uint8_t *image = stbi_load(frame_path, &image_w, &image_h, &image_channels, 1);

		int i = 0;
		while (i < WIDTH*HEIGHT) {
			int start = i;
			while (i < WIDTH*HEIGHT && image[i] == image[start] && i - start < 0x7FFF) { i++; }
			uint16_t len = ((uint16_t) (i - start) & 0x7FFF) | (image[start] << 15);
			fwrite(&len, sizeof(uint16_t), 1, file);
		}

		stbi_image_free(image);
	}

	fclose(file);

	return 0;
}
