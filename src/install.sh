#!/bin/bash

DIR=""
echo "Введите директорию для установки приложения (для установки в текущую директорию нажмите enter)"
read DIR

if [ "$DIR" == "" ]; then
    cmake -B build
    make -C build
    cp build/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
else
    cmake -B $DIR/build
    make -C $DIR/build
    cp $DIR/build build/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
fi
