#!/bin/bash -e

mkdir -p tmp

find src/. -regex '^.*\.h$' | while read CCFILE; do
  CCFILENAME="${CCFILE##*/}"
  clang -x c++ -Wall -std=gnu++17 $CCFILE -Isrc -c -o tmp/${CCFILENAME}.o
  echo "$CCFILENAME is well compiled solely !"
done

find src/. -regex '^.*\.cc$' | while read CCFILE; do
  CCFILENAME="${CCFILE##*/}"
  clang -x c++ -Wall -std=gnu++17 $CCFILE -Isrc -c -o tmp/${CCFILENAME}.o
  echo "$CCFILENAME is well compiled solely !"
done

