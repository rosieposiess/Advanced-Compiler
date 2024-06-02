#!/bin/bash
cmake -S project1 -G Ninja -B build
cmake --build build
clang -O0 -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names test.c -o test.ll
opt -S -load-pass-plugin='build/lib/libInstructionCounter.so' -passes='instruction-counter' test.ll -disable-output 2> test.out
