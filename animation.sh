#!/usr/bin/env bash
set -e
make
rm -rf tmp_video
mkdir tmp_video
for j in 0 1 2 3; do
  i="0"
  while [ $i -le 90 ]; do
    k=$(($i+$j*90))
    ./sin -x 40 -y 40 -t $k | ./makegrid -x 40 | ./j3D -x -35.26 -y 35.26 -z -45 | jgraph | convert -density 600 - tmp_video/$(printf "%01d%02d" $j $i).jpg& i=$(($i + 1))
  done;
  wait
done;

ffmpeg -framerate 30 -pattern_type glob -i "tmp_video/*.jpg" -c:v libx264 -vf scale=480:-1 out/out.mp4
