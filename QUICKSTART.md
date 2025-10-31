# Quick Start Guide - Pokemon Event Archive Wii Game

## What You've Got

A complete Wii homebrew game with:
- ✅ Animated start screen with "Press A to Play"
- ✅ Main menu with 5 interactive buttons
- ✅ Gen 1, 2, and 3 Event information screens
- ✅ Event Details information page
- ✅ Wiimote pointer controls

## Building (One-Time Setup)

### Step 1: Install DevkitPro
```bash
# macOS
brew install devkitpro-pacman

# Then install Wii libraries
sudo dkp-pacman -S wii-dev grrlib libogc libfat-ogc
```

### Step 2: Set Environment Variables
Add to `~/.zshrc`:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
export PATH=$DEVKITPRO/tools/bin:$PATH
```

Apply:
```bash
source ~/.zshrc
```

### Step 3: Build
```bash
cd "/Users/adam/Desktop/Event wii game"
./build.sh
```

This creates `event_wii_game.dol` - your Wii game!

## Installing on Wii

### Quick Method: SD Card

1. **Format SD card as FAT32**

2. **Create folder structure on SD:**
   ```
   SD:/apps/event_wii_game/
   ```

3. **Copy files:**
   ```bash
   # Copy to SD card (adjust path to your SD card)
   cp event_wii_game.dol /Volumes/SDCARD/apps/event_wii_game/boot.dol
   cp meta.xml /Volumes/SDCARD/apps/event_wii_game/meta.xml
   ```

4. **Insert SD in Wii → Launch Homebrew Channel → Run "Pokemon Event Archive"**

## Game Controls

- **Wiimote Pointer** - Move cursor
- **A Button** - Select/Confirm
- **B Button** - Back to menu
- **HOME Button** - Back to menu

## Game Features

### Start Screen
- Animated background with floating circles
- Fade-in title: "Pokemon Event Archive"
- Pulsing "Press A to Play" text

### Main Menu (5 Buttons)
1. **Gen 1 Events** - Red/Blue/Yellow event Pokemon
2. **Gen 2 Events** - Gold/Silver/Crystal events
3. **Gen 3 Events** - RSE/FRLG distribution events
4. **Event Details** - What events are and how they work
5. **Exit Game** - Close application

### Individual Screens
Each generation shows:
- Event names and dates
- Distribution methods
- Exclusive Pokemon available
- Press B to return

## File Output

After building:
- `event_wii_game.dol` - The Wii executable
- `event_wii_game.elf` - ELF format (debug)
- `build/` - Compiled objects

## Troubleshooting

**Build fails?**
- Ensure DEVKITPPC is set: `echo $DEVKITPPC`
- Install missing libs: `sudo dkp-pacman -S grrlib libogc`

**Black screen on Wii?**
- Check SD card is FAT32
- Verify file is named `boot.dol`
- Update Homebrew Channel

**Wiimote doesn't work?**
- Check IR sensor bar is plugged in
- Resync Wiimote
- Replace batteries

## About WBFS Format

WBFS is for full Wii disc games, not homebrew apps. This game runs via:
- **Homebrew Channel** (recommended) - uses .dol format
- **wiiload** (network) - for development
- **USB loaders** (advanced) - can load .dol files

The .dol file IS the final game format for homebrew.

## What's Next?

You can customize:
- Event content in `source/main.cpp`
- Add images/graphics (see GRRLIB docs)
- Add sound effects (see asndlib)
- Create more screens

See `INSTALL.md` for detailed instructions.
See `README.md` for technical details.

---

**Ready to play? Build it and load it on your Wii!** 🎮

