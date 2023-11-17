#!/bin/bash

DIR=""
echo "Введите директорию для установки приложения (для установки в текущую директорию нажмите enter)"
read DIR

if [ "$DIR" == "" ]; then
    cmake -B smart_calculator
    make -C smart_calculator
    cp smart_calculator/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
else
    cmake -B $DIR/smart_calculator
    make -C $DIR/smart_calculator
    cp $DIR/smart_calculator/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
fi
