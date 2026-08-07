#!/bin/bash
# Build script for Student Manager Project
# Run this from the project root: ./scripts/build.sh


# Welcome to the Student Manager build script! This script will compile the C source files and create an executable named "main". 
# Make sure you have gcc installed and available in the PATH of your computerbefore running this script.
# If you are on Windows, you can use Git Bash or WSL to run this script.
# Homework done by: Cornet Ezna, Dely Judekerly and Janvier Djevenson.

set -e  # Stop the script if any command fails

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT"

echo "Building Student Manager..."

mkdir -p data

gcc src/main.c src/student.c -Iinclude -Wall -Wextra -o main

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Launching the program..."
    echo ""
    echo ""
    ./main
else
    echo "Build failed."
    exit 1
fi