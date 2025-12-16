#!/bin/bash


mkfifo /tmp/video_fifo

gst-launch-1.0 v4l2src device=/dev/video0 ! tee name=t ! queue ! video/x-raw,format=NV12,width=640,height=480,framerate=30/1 ! kmssink t. ! queue ! mpph264enc ! h264parse !  filesink location=/tmp/video_fifo &
	
ffmpeg -re -i /tmp/video_fifo -c copy -f rtsp rtsp://192.168.69.78:8554/hxbj

