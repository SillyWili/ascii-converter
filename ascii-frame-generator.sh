#!/bin/bash

echo "" > frames.txt

DEFAULT_JP2A_OPTIONS=(--color-depth=24 --width=80)
ffmpeg -i $1 -v error -vf scale=320:-1 frames/frame_%03d.png

for frame in frames/frame_*.png; do
    output=$(jp2a --color-depth=24 --width=80 "$frame")
    echo "$output\n" >> frames.txt
done

rm frames/*.png