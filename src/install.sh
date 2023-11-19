#!/bin/bash

DIR=""
echo "Please enter the installation directory path (press [return] to choose current directory)"
read DIR

if [ "$DIR" == "" ]; then
    cmake -DCMAKE_PREFIX_PATH="$QTDIR"/cmake -B smart_calculator
    make -C smart_calculator
    cp smart_calculator/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
else
    cmake -DCMAKE_PREFIX_PATH="$QTDIR"/cmake -B $DIR/smart_calculator
    make -C $DIR/smart_calculator
    cp $DIR/smart_calculator/SmartCalculator.app/Contents/MacOs/SmartCalculator SmartCalculator
fi
