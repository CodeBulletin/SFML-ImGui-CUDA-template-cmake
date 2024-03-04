BuildType ?= Debug

.PHONY: build run run-release clean

all: build run

build:
	@ echo "Building..."
	@ mkdir -p build/$(BuildType)
	@ cd build/$(BuildType) && cmake -DCMAKE_BUILD_TYPE=$(BuildType) -S ../.. -B .
	@ cd build/$(BuildType) && make -j4
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