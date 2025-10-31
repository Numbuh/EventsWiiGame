#!/bin/bash

# Build script for Pokemon Event Archive Wii Game

echo "================================"
echo "Building Pokemon Event Archive"
echo "================================"

# Check if DEVKITPPC is set
if [ -z "$DEVKITPPC" ]; then
    echo "ERROR: DEVKITPPC is not set!"
    echo "Please set it with: export DEVKITPPC=/opt/devkitpro/devkitPPC"
    exit 1
fi

# Clean previous build
echo "Cleaning previous build..."
make clean

# Build the project
echo "Building project..."
make

# Check if build was successful
if [ -f "event_wii_game.dol" ]; then
    echo ""
    echo "================================"
    echo "Build successful!"
    echo "================================"
    echo "Output file: event_wii_game.dol"
    echo ""
    echo "To install on Wii:"
    echo "1. Copy event_wii_game.dol to SD:/apps/event_wii_game/boot.dol"
    echo "2. Copy meta.xml to SD:/apps/event_wii_game/meta.xml"
    echo "3. Copy icon.png to SD:/apps/event_wii_game/icon.png (optional)"
    echo ""
    echo "Or use: make run (requires wiiload and network setup)"
else
    echo ""
    echo "================================"
    echo "Build failed!"
    echo "================================"
    echo "Please check the error messages above."
    exit 1
fi

