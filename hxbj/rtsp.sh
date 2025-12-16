#!/bin/bash

RTSP_SERVER="192.168.69.78"
RTSP_PORT="8554"
STREAM_NAME="camera"
VIDEO_DEVICE="/dev/video0"
RESOLUTION="1280x720"
FRAMERATE="30"
BITRATE="2000k"


ffmpeg -f v4l2 \
  -input_format yuyv422 \
  -video_size $RESOLUTION \
  -framerate $FRAMERATE \
  -i $VIDEO_DEVICE \
  -c:v libx264 \
  -preset veryfast \
  -tune zerolatency \
  -b:v $BITRATE \
  -pix_fmt yuv420p \
  -g 50 \
  -f rtsp \
  -rtsp_transport tcp \
  "rtsp://$RTSP_SERVER:$RTSP_PORT/$STREAM_NAME"
