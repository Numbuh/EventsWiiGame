# Installation Guide - Pokemon Event Archive for Wii

## Prerequisites for Building

### 1. Install DevkitPro

#### macOS (via Homebrew)
```bash
brew install devkitpro-pacman
```

#### Manual Installation
Download the installer from: https://github.com/devkitPro/installer/releases

### 2. Install Required Libraries

```bash
# Update pacman
sudo dkp-pacman -Syu

# Install Wii development tools
sudo dkp-pacman -S wii-dev

# Install required libraries
sudo dkp-pacman -S libogc
sudo dkp-pacman -S grrlib
sudo dkp-pacman -S libfat-ogc
sudo dkp-pacman -S ppc-libpng
sudo dkp-pacman -S ppc-libjpeg-turbo
sudo dkp-pacman -S ppc-zlib
```

### 3. Set Environment Variables

Add to your `~/.zshrc` (macOS) or `~/.bashrc` (Linux):

```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
export PATH=$DEVKITPRO/tools/bin:$PATH
```

Apply changes:
```bash
source ~/.zshrc  # or source ~/.bashrc
```

## Building the Game

### Option 1: Using the build script (recommended)

```bash
chmod +x build.sh
./build.sh
```

### Option 2: Using make directly

```bash
make clean
make
```

## Installing on Wii

### Method 1: Homebrew Channel (Recommended)

1. **Prepare SD Card Structure:**
   ```
   SD:/apps/event_wii_game/
   ├── boot.dol
   ├── meta.xml
   └── icon.png (optional)
   ```

2. **Copy Files:**
   ```bash
   # Format SD card as FAT32
   # Copy the built files
   cp event_wii_game.dol /Volumes/SD/apps/event_wii_game/boot.dol
   cp meta.xml /Volumes/SD/apps/event_wii_game/meta.xml
   cp icon.png /Volumes/SD/apps/event_wii_game/icon.png  # if you have one
   ```

3. **Run on Wii:**
   - Insert SD card into Wii
   - Launch Homebrew Channel
   - Select "Pokemon Event Archive"
   - Press A to launch

### Method 2: Network Loading (wiiload)

1. **Install wiiload on your computer:**
   ```bash
   # macOS
   brew install wiiload
   
   # Or build from source
   git clone https://github.com/devkitPro/wiiload.git
   cd wiiload
   make
   sudo make install
   ```

2. **Configure Wii for network loading:**
   - Launch Homebrew Channel
   - Press 1 on the Wiimote to see IP address
   - Note down the IP address

3. **Send game to Wii:**
   ```bash
   # Set Wii IP address
   export WIILOAD=tcp:192.168.1.XXX  # Replace with your Wii's IP
   
   # Load the game
   wiiload event_wii_game.dol
   
   # Or use make run
   make run
   ```

### Method 3: USB Loader (Advanced)

This is primarily for full games. For homebrew apps, use Homebrew Channel instead.

## Verifying Installation

### On Wii:
1. Power on Wii with SD card inserted
2. Launch Homebrew Channel
3. You should see "Pokemon Event Archive" in the list
4. Select it and press A

### Expected Behavior:
- Animated start screen appears
- "Press A to Play" text appears
- After pressing A, main menu with 5 buttons shows:
  - Gen 1 Events
  - Gen 2 Events
  - Gen 3 Events
  - Event Details
  - Exit Game

## Troubleshooting

### Build Errors

**Error: "DEVKITPPC not set"**
```bash
export DEVKITPPC=/opt/devkitpro/devkitPPC
```

**Error: "grrlib.h: No such file or directory"**
```bash
sudo dkp-pacman -S grrlib
```

**Error: "undefined reference to `GRRLIB_Init`"**
- Check that GRRLIB is properly installed
- Verify library paths in Makefile

### Runtime Errors

**Black screen on Wii:**
- Ensure SD card is FAT32 formatted
- Check that boot.dol is not corrupted
- Verify Homebrew Channel is up to date

**Wiimote not responding:**
- Make sure IR sensor bar is connected
- Try resyncing the Wiimote
- Check batteries

**No graphics display:**
- Ensure GRRLIB is properly linked
- Check that video mode is supported by your TV

**SD card not detected:**
- Reformat SD card as FAT32
- Use SD card 2GB-32GB (SDHC supported)
- Ensure card is properly inserted

## Controls

- **Wiimote Pointer**: Navigate cursor
- **A Button**: Select/Confirm
- **B Button**: Go back to main menu
- **HOME Button**: Return to main menu
- **2 Button**: Alternative start button (on start screen)

## File Structure

```
Event wii game/
├── source/
│   └── main.cpp          # Main game source code
├── build/                # Build output (generated)
├── Makefile              # Build configuration
├── meta.xml              # Homebrew metadata
├── icon.png              # Homebrew Channel icon (optional)
├── build.sh              # Build script
├── README.md             # Project overview
└── INSTALL.md            # This file
```

## Additional Resources

- **DevkitPro Documentation**: https://devkitpro.org/wiki/Getting_Started
- **GRRLIB Documentation**: https://github.com/GRRLIB/GRRLIB
- **WiiBrew Wiki**: https://wiibrew.org/wiki/Main_Page
- **Homebrew Channel**: https://wiibrew.org/wiki/Homebrew_Channel

## Support

For issues:
1. Check that all prerequisites are installed
2. Verify environment variables are set correctly
3. Ensure Wii has Homebrew Channel installed
4. Check SD card formatting (must be FAT32)

## Safety Notes

- This is homebrew software for educational purposes
- Always use official Nintendo hardware
- Don't pirate games or commercial software
- Homebrew won't damage your Wii if used properly

