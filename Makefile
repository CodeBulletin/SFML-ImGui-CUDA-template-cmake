BuildType ?= Debug

.PHONY: build run run-release clean

all: build run

build:
	@ echo "Building..."
	@ mkdir -p build/$(BuildType)
	@ echo "Generating build files..."
	@ cd build/$(BuildType) && cmake -DCMAKE_BUILD_TYPE=$(BuildType) -DCMAKE_CXX_COMPILER=$(which g++) -DCMAKE_C_COMPILER=gcc -S ../.. -B .
	@ echo "Compiling..."
	@ cd build/$(BuildType) && make -j4
	@ echo "Copying main..."
	@ mv build/$(BuildType)/src/main build/$(BuildType)/main

run: clear-scr
	@ echo "Running..."
	@ ./build/$(BuildType)/main

clean:
	@ echo "Cleaning..."
	@ rm -rf build/Release/*
	@ rm -rf build/Debug/*
	@ rm -rf build/RelWithDebInfo/*
	@ rm -rf build/MinSizeRel/*

clear-scr:
	@ clear

benchmark:
	@ echo "Running benchmark..."
	@ hyperfine --warmup 3 './build/$(BuildType)/main' --export-markdown benchmark.md

install:

uninstall:
	