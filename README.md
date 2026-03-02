## Bad Apple

basic program i whipped up in like 5 hours that plays bad apple using ndless. it uses simple run length encoding (rle) to compress the video file. The final size of the whole program is about 7.7MiB


## Building

First, install [libnspire](https://github.com/Vogtinator/libnspire).

Then run `make` and select `y` when prompted to build `bad-apple.rle`.
To upload the files automatically too, run `make upload`. It defaults to using [nspirectl](https://github.com/0osh/nspirectl), but its easy enough to change the makefile to run your own upload command. If it's taking too long to upload, change this line in `bad-apple.data.c`
```c
for (int file_i = 0; file_i <= 6571; file_i+=1) {
```
change `file_i+=1` to `file_i+=2` to skip every other frame and the file size will half and change the delay at the end of the file to 60ms.


also how do i tell github that im not using c++ look in the languages progress bar thingy
