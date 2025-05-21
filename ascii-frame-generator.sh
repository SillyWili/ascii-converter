#!/bin/bash

> frames.txt

ffmpeg -i $1 -v error -vf scale=320:-1 frames/frame_%03d.png

for frame in frames/frame_*.png; do
    jp2a --color-depth=24 --width=80 "$frame" >> frames.txt
    echo "" >> frames.txt
done

rm frames/*.png