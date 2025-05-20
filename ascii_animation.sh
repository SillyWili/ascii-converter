#!/bin/bash

# Add --chars="$CHARS" flag to jp2a to only use the following characters
CHARS=".:!_-~=MAL0O"
DEFAULT_JP2A_OPTIONS=(--color-depth=24 --width=80)

ffmpeg -i $1 -v error -vf scale=320:-1 frames/frame_%03d.png

# Directly extrapolate FPS from number of frames and video lenght for debugging
#
# number_of_frames=$(ls frames/*.png | wc -l)
video_lenght=$(ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 $1)
# FPS=$(bc --expression="scale = 6; ${number_of_frames} / ${video_lenght}")

FPS=$(ffprobe -v error -select_streams v:0 -show_entries stream=r_frame_rate -of default=noprint_wrappers=1:nokey=1 $1 | bc -l)
frame_time=$(bc --expression="scale = 6; 1 / ${FPS}") # could be an issue here with the conversion from s/ms

precise_sleep() {
    local ms=$1
    local sec=$(echo "scale=6; $ms/1000" | bc) #or here dedicing if s or ms should be used
    
    # Use perl for microsecond precision sleep
    # This has less overhead than bash's built-in sleep
    perl -e "select(undef, undef, undef, $sec);"
}

get_time() {
    perl -MTime::HiRes=time -e 'printf("%.9f\n", time)'
}

start_video_buffer() {
    clear
    tput civis
    echo -e "\033[?1049h"
}

end_video_buffer() {
    echo -e "\033[?1049l"
    tput cnorm
    clear
    rm frames/*.png
}

start_video_buffer
start_time=$(get_time)
i=0

for frame in frames/frame_*.png; do
    # Unccoment for debbuggin purpose
    # echo "FPS:[${FPS}] Frame Time:[${frame_time}]" 
    # finish_time=$(get_time)
    # echo "FPS:[${FPS}] Frame Time:[${frame_time}] Elapsed:[$(echo "$finish_time - $start_time" | bc -l)] Original lenght[${video_lenght}]"

    target_time=$(echo "$start_time + $i * $frame_time" | bc -l)

    output=$(jp2a "${DEFAULT_JP2A_OPTIONS[@]}" "$frame")
    echo -e "\033[H\033[J${output}"
    # precise_sleep $frame_time

    while :; do
        now=$(get_time)
        is_ready=$(echo "$now >= $target_time" | bc)
        [[ is_ready -eq 1 ]] && break
        precise_sleep 0,001
    done
    i=$((i++))
done
end_video_buffer

finish_time=$(get_time)
echo "FPS:[${FPS}] Frame Time:[${frame_time}] Elapsed:[$(echo "$finish_time - $start_time" | bc -l)] Original lenght[${video_lenght}]"