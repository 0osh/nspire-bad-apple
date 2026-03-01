## Bad Apple

basic program that plays bad apple using ndless. it uses simple run length encoding (rle) to compress the video file. The final size of the whole program is ≈ 8.7MiB


## Building

First, install [libnspire](https://github.com/Vogtinator/libnspire).

Then run `make` and select `y` when prompted to build `bad-apple.rle`.
If you have [nspirectl](https://github.com/0osh/nspirectl) installed then run make with `NSPIRECTL` set to any value to use it to upload the files automatically. Or edit the makefile and set it there. If it's taking too long to upload, change this line in `bad-apple.data.c`
```c
for (int file_i = 0; file_i <= 6571; file_i+=1) {
```
change `file_i+=1` to `file_i+=2` to skip every other frame and the file size will half. It doesn't reduce quality to much :)


also how do i tell github that im not using c++ look in the langauges progress bar thingy
