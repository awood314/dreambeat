#!/bin/bash
for i in `find src -name "*.*"`
do
    clang-format -i $i
done
