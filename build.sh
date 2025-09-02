#!/bin/bash

mkdir -p build/

gcc ./src/main.c -g \
  -I./lib/raylib/include \
  -L./lib/raylib/lib -Wl,-rpath=./lib/raylib/lib \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
  -o ./build/tradebinder
