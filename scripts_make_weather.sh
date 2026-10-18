#!/usr/bin/env bash
set -e
mkdir -p assets/audio/weather
road=assets/audio/ambience/base_road_cc0.ogg
water=assets/audio/source/sfx100/sfx100v2_loop_water_01.ogg
thunder=assets/audio/source/sfx100/sfx100v2_thunder_01.ogg
ffmpeg -y -loglevel error -i "$road" -af 'volume=0.55' -t 20 assets/audio/weather/clear.ogg
ffmpeg -y -loglevel error -i "$road" -af 'volume=0.45,lowpass=f=2600,aecho=0.8:0.9:80:0.25' -t 20 assets/audio/weather/rain.ogg
ffmpeg -y -loglevel error -i "$thunder" -af 'volume=0.8,aloop=loop=-1:size=2e+09' -t 20 assets/audio/weather/storm.ogg
ffmpeg -y -loglevel error -i assets/audio/source/sfx100/sfx100v2_air_01.ogg -af 'volume=0.8,aloop=loop=-1:size=2e+09' -t 20 assets/audio/weather/wind.ogg
ffmpeg -y -loglevel error -i "$water" -af 'volume=0.38,lowpass=f=900' -t 20 assets/audio/weather/humid.ogg
ffmpeg -y -loglevel error -i assets/audio/source/sfx100/sfx100v2_air_02.ogg -af 'volume=0.35,lowpass=f=700' -t 20 assets/audio/weather/cold.ogg
ffmpeg -y -loglevel error -i "$water" -af 'volume=0.22,highpass=f=2200' -t 20 assets/audio/weather/snow.ogg
ffmpeg -y -loglevel error -i assets/audio/source/sfx100/sfx100v2_air_03.ogg -af 'volume=0.25,highpass=f=3200' -t 20 assets/audio/weather/ice.ogg
ffmpeg -y -loglevel error -i assets/audio/source/sfx100/sfx100v2_air_01.ogg -af 'volume=0.42,lowpass=f=1200' -t 20 assets/audio/weather/desert.ogg
ffmpeg -y -loglevel error -i assets/audio/source/sfx100/sfx100v2_air_02.ogg -af 'volume=0.36,lowpass=f=1700,aecho=0.8:0.7:120:0.25' -t 20 assets/audio/weather/mountain.ogg
ffmpeg -y -loglevel error -i "$road" -af 'volume=0.40,lowpass=f=1900' -t 20 assets/audio/weather/farm.ogg
