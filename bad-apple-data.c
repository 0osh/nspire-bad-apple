#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 320
#define HEIGHT 240

#define vertical(x) (x % HEIGHT) * WIDTH + x / HEIGHT

#define BUFFER_SIZE 4096

#define FILE_PATH "bad-apple.rle"

int main(void) {
	FILE *file = fopen(FILE_PATH, "w");
	if (file == NULL) { perror("Failed to open " FILE_PATH); return 1; }

	uint16_t buffer[BUFFER_SIZE];
	int buffer_len = 0;

	for (int file_i = 0; file_i <= 6571; file_i+=1) {
		char frame_path[32] = "frames/";
		sprintf(frame_path+7, "%04d.png", file_i);
		if (file_i % 100 == 0) { printf("encoding %s...\n", frame_path); }
		int image_w, image_h, image_channels;
		uint8_t *image = stbi_load(frame_path, &image_w, &image_h, &image_channels, 1);

		int i = 0;
		while (i < WIDTH*HEIGHT) {
			int start = i;
			while (i < WIDTH*HEIGHT && image[vertical(i)] == image[vertical(start)] && i - start < 0x7FFF) { i++; }
			uint16_t len = ((uint16_t) (i - start) & 0x7FFF) | (image[vertical(start)] << 15);
			buffer[buffer_len++] = len;
			if (buffer_len >= BUFFER_SIZE) { fwrite(buffer, sizeof(uint16_t), buffer_len, file); buffer_len = 0; }
		}

		stbi_image_free(image);
	}

	fwrite(buffer, sizeof(uint16_t), buffer_len, file);

	fclose(file);

	return 0;
}
