# % = wildcard
# $@ = target
# $< = first prerequisite
# $^ = every prerequisite

CFLAGS := -Wall -Wextra

all: bad-apple bad-apple.rle

bad-apple: bad-apple.ndls.c bad-apple.rle
	@nspire-ld $(CFLAGS) bad-apple.ndls.c -o bad-apple
	@genzehn --input bad-apple --output bad-apple
ifdef NPSIRECTL
	@nspirectl send bad-apple /
endif



bad-apple.rle: bad-apple-data.c
	@echo -n "Build rle file? (y/n)  "; \
	read BUILD_RLE; \
	if [ "$$BUILD_RLE" = "y" ]; then \
		echo "Building rle file..."; \
		gcc bad-apple-data.c $(CFLAGS) -fsanitize=address -g -lm -o bad-apple-data; \
		./bad-apple-data; \
		if [ "$(NSPIRECTL)" != "" ]; then \
			@echo "Uploading..."; \
			@nspirectl send bad-apple.rle /; \
			@echo "done"; \
		fi; \
	fi

clean:
	@rm -f bad-apple bad-apple-data bad-apple.rle
