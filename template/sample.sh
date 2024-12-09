#!/bin/bash
set -e

echo "Building..."
./build.sh

echo "Running..."
./main sample.txt


