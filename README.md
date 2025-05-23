# Ascii Converter

Just some useful scripts to convert/display ascii art on the terminal and with [Fastfetch](https://github.com/fastfetch-cli/fastfetch).

Useful tools are ffmpeg and jp2a.

Run ffmpeg to export every frame of a video/gif:

```
ffmpeg -i your_file.mp4 -vf scale=320:-1 folder_name/frame_%03d.png
```

Then to convert an image to ascii use jp2a:

```
jp2a your_file
```

Also there are many useful flags for jp2a like:

```
--width=value --height=value --color --invert
```

## Usage

To compile and execute the file just run:

```
make
```

The [convertSymbol.c]() is useful in the event that jp2a doesn't convert the image correctly.

With [convertSymbol.c]() you can replace a specific symbol/character with another one of your choice.

Finally with the [ascii_animation.sh]() you can play an animation with every frame of a video/gif exported with ffmpeg.
