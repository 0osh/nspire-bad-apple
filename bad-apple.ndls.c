#include <libndls.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 320
#define HEIGHT 240

#define FILE_PATH "bad-apple.rle.tns"

#define FATAL(msg) show_msgbox("Fatal", msg); return 1;

int ret = 0;

int main(int argc, char *argv[]) {
	assert_ndless_rev(801);
	lcd_init(SCR_TYPE_INVALID);

	ret = enable_relative_paths(argv);
	if (ret != 0) { FATAL("Failed to enable relative paths"); }

	FILE *file = fopen(FILE_PATH, "rb");
	if (file == NULL) { FATAL("Failed to open " FILE_PATH); }


	uint16_t fb[HEIGHT][WIDTH];
	uint16_t *fb_linear = &fb[0][0];
	bool showEOF = true;

	uint16_t len;

	while (!isKeyPressed(KEY_NSPIRE_ESC)) {
		for (int i = 0; i < WIDTH * HEIGHT;) {
			if (fread(&len, sizeof(uint16_t), 1, file) != 1) { if (feof(file)) { break; } else { FATAL("Failed to read data"); }}

			// rle encoding
			// highest bit is 1 or 0 for colour, other 15 is the length
			// if length is greater than 2^15 then multiple entries should be made
			uint8_t colour = (len >> 15) * 0xFF;
			len &= 0x7FFF;

			memset(fb_linear + i, colour, len*2); // x2 because uint16_t uses 2 bytes
			i += len;
		}

		lcd_blit(fb, SCR_320x240_565);

		if (isKeyPressed(KEY_NSPIRE_SPACE)) {
			wait_no_key_pressed();
			do { wait_key_pressed(); } while (!isKeyPressed(KEY_NSPIRE_SPACE));
			wait_no_key_pressed();
		}

		idle();
		msleep(60);
	}


	lcd_init(SCR_TYPE_INVALID);

	return 0;
}
