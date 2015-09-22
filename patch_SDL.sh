#!/bin/bash

source=/Library/Frameworks/SDL.framework/Headers
target=/opt/local/include/SDL

mkdir -p $target

for path in $source/*; do
  file=`basename $path`
  rm $target/$file
  ln -s $source/$file $target/$file
done
