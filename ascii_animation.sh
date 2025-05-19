#!/bin/bash

# Add --chars="$CHARS" flag to jp2a to only use the following characters
CHARS=".:!_-~=MAL0O"

FPS=$(ffprobe -v error -select_streams v:0 -show_entries stream=r_frame_rate -of default=noprint_wrappers=1:nokey=1 $1 | bc -l)
frame_time=$(bc --expression="scale = 10; 1 / ${FPS}")

ffmpeg -i $1 -v error -vf scale=320:-1 frames/frame_%03d.png

precise_sleep() {
    local ms=$1
    local sec=$(echo "scale=6; $ms/1000" | bc)
    
    # Use perl for microsecond precision sleep
    # This has less overhead than bash's built-in sleep
    perl -e "select(undef, undef, undef, $sec);"
}

start_video_buffer(){
    clear
    tput civis
    echo -e "\033[?1049h"
}

end_video_buffer(){
    echo -e "\033[?1049l"
    tput cnorm
    clear
    rm frames/*.png
}

start_video_buffer
for frame in frames/frame_*.png; do
    # Unccoment for debbuggin purpose
    # echo "FPS:[${FPS}] Frame Time:[${frame_time}]" 
    output=$(jp2a --color-depth=24 --width=150 "$frame")
    echo -e "\033[H\033[J${output}"
    precise_sleep $frame_time
done
end_video_buffer