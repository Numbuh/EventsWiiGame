# Pokemon Event Archive - Wii Homebrew Game

A Wii homebrew application that showcases Pokemon event distributions from Generation 1, 2, and 3 games.

## Features

- **Start Screen**: Animated intro with "Press A to Play" prompt
- **Main Menu**: Five sleek buttons for navigation
  - Gen 1 Events (Red/Blue/Yellow)
  - Gen 2 Events (Gold/Silver/Crystal)
  - Gen 3 Events (Ruby/Sapphire/Emerald/FR/LG)
  - Event Details (Information about Pokemon events)
  - Exit Game
- **Interactive UI**: Point and click with Wiimote
- **Clean Design**: Modern, sleek interface optimized for Wii

## Building

### Prerequisites

1. **DevkitPro**: Install DevkitPro with DevkitPPC
   ```bash
   # On macOS with Homebrew
   brew install devkitpro-pacman
   
   # Or download from: https://github.com/devkitPro/installer/releases
   ```

2. **Install Wii libraries**:
   ```bash
   sudo dkp-pacman -S wii-dev
   sudo dkp-pacman -S libogc
   sudo dkp-pacman -S libfat-ogc
   sudo dkp-pacman -S ppc-libpng
   sudo dkp-pacman -S ppc-libjpeg-turbo
   ```

3. **Install GRRLIB** (graphics library):
   ```bash
   sudo dkp-pacman -S grrlib
   ```

### Set Environment Variables

Add to your `~/.zshrc` or `~/.bash_profile`:

```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
export PATH=$DEVKITPRO/tools/bin:$PATH
```

Then reload:
```bash
source ~/.zshrc
```

### Compile

```bash
make clean
make
```

This will generate:
- `event_wii_game.elf` - ELF executable
- `event_wii_game.dol` - DOL file for Wii

## Installation on Wii

### Method 1: Homebrew Channel

1. Copy `event_wii_game.dol` and `meta.xml` to your SD card:
   ```
   SD:/apps/event_wii_game/boot.dol
   SD:/apps/event_wii_game/meta.xml
   ```

2. Insert SD card into Wii
3. Launch Homebrew Channel
4. Run "Pokemon Event Archive"

### Method 2: Convert to WBFS (for USB Loader)

```bash
# Install wbfs tools
brew install wbfs

# Convert DOL to ISO first (requires additional tools)
# Then convert to WBFS:
wbfs_file add event_wii_game.iso event_wii_game.wbfs
```

**Note**: WBFS format is primarily for full games. Homebrew apps are typically run via Homebrew Channel using DOL format.

### Method 3: Load via Network (wiiload)

```bash
# Install wiiload on your Mac
brew install wiiload

# Run on Wii (have Homebrew Channel running with network)
make run
# or
wiiload event_wii_game.dol
```

## Controls

- **Wiimote Pointer**: Navigate and hover over buttons
- **A Button**: Select/Confirm
- **B Button**: Go back to main menu
- **HOME Button**: Return to main menu (from any screen)

## Project Structure

```
Event wii game/
├── source/
│   └── main.cpp          # Main game code
├── build/                # Compiled objects (generated)
├── Makefile              # Build configuration
├── meta.xml              # Homebrew Channel metadata
└── README.md             # This file
```

## Development Notes

- Built with **GRRLIB** for 2D graphics rendering
- Uses **libogc** for Wii hardware access
- **Wiimote IR pointer** for cursor control
- Designed for **640x480** resolution

## Troubleshooting

### "DEVKITPPC not set" error
Make sure environment variables are set:
```bash
export DEVKITPPC=/opt/devkitpro/devkitPPC
```

### Missing libraries
Install all required libraries:
```bash
sudo dkp-pacman -S wii-dev grrlib libogc libfat-ogc
```

### Wiimote not responding
- Make sure WPAD is initialized (done in code)
- Check that IR sensor bar is connected
- Try syncing Wiimote again

## Credits

- **DevkitPro** - Wii homebrew toolchain
- **GRRLIB** - Graphics library
- **libogc** - GameCube/Wii library

## License

Free for personal and educational use.

