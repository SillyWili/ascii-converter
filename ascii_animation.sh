 for f in frame_*.png; do
    clear
    jp2a --width=80 "$f"
    sleep 0.00005
done
