#!/bin/bash

function run_long_core() {
  local c=$1
  ./speedup_avx2 data/long_32k.txt data/long_pat.txt 200 $c
}

function run_short_core() {
  local c=$1
  ./speedup_avx2 data/short_32k.txt data/short_pat.txt 200 $c
}

for i in a b c d e f g h i j k l m n o
do
  run_long_core $i
done
for i in a b c d e f g h i j k l m n o
do
  run_short_core $i
done
