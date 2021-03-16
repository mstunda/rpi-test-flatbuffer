#!/bin/bash
set -e

FBS_FOLDER="src/flatbuffers"
COMPILE_FILES="$FBS_FOLDER/teleop_car.fbs"

# CPP
CPP_FILE_FOLDER="src/cpp"
rm -rf $CPP_FILE_FOLDER/*
flatc --cpp -o $CPP_FILE_FOLDER -I $FBS_FOLDER $COMPILE_FILES

# C
C_FILE_FOLDER="src/c"
rm -rf $C_FILE_FOLDER/*
flatcc -a -o $C_FILE_FOLDER -I $FBS_FOLDER $COMPILE_FILES


# Dart
DART_FILE_FOLDER="src/dart"
rm -rf $DART_FILE_FOLDER/*
flatc --dart -o $DART_FILE_FOLDER -I $FBS_FOLDER $COMPILE_FILES
