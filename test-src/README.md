This folder contains the source code for the debugger program, which prints the ID3 info for a given MP3.

Most of the code is from the original ices0 source, with small modifications to read from a file rather than an Icecast stream, and to simplify logging.


## Build

To build the program, compile the C source:

```
gcc -I /usr/include -o test test.c mp3.c id3.c metadata.c util.c -lshout
```

You will need to install the Icecast/Shoutcast development files first. (This is the `libshout3-dev` package on Ubuntu/Debian.)

My development libraries are in `/usr/include` — you may have to adjust that path for your machine. The compile will generate a lot of warnings, but they can be ignored.

## Usage

Specify an MP3 file to print out its ID3 (and other) info:

```
> ./test good.mp3
Filename cleaned up from [good.mp3] to [good]
ID3v1: Title: One Of Those Christmas Days
ID3v1: Artist: Third Eye Blind
MPEG-1 layer III, 128 kbps, 44100 Hz, j-stereo
Ext: 0  Mode_Ext: 2 Copyright: 0  Original: 1
Error Protection: 0 Emphasis: 0 Padding: 0
done.
```
