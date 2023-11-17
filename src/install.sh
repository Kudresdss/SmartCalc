#!/bin/bash

DIR=""
echo "Введите директорию для установки приложения"
read DIR

if [ "$DIR" == "" ]; then
    cmake --build build
    cp cp build/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
else
    cmake --build $DIR/build
fi
