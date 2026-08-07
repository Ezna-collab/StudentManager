#!/bin/bash
# Build script for Student Manager
# Run this from the project root: ./scripts/build.sh
# Homework done by: Cornet Ezna, Dely Judekerly et Janvier Djevenson.

set -e  # Stop the script if any command fails

# Get the directory where this script is located, then go to project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT"

echo "Building Student Manager..."

# Make sure the data folder exists (needed for saving students.txt)
mkdir -p data

gcc src/main.c src/student.c -Iinclude -Wall -Wextra -o main

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Launching the program..."
    echo ""
    ./main
else
    echo "Build failed."
    exit 1
fi