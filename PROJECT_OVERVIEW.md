# Pokemon Event Archive - Wii Homebrew Game
## Complete Project Overview

---

## 🎮 What You Have

A **fully functional Wii homebrew game** built in C++ using official Wii development libraries. This game runs on real Wii hardware via the Homebrew Channel.

### Game Features

#### 1. Animated Start Screen
- Smooth fade-in animation
- Floating background circles animation
- "Pokemon Event Archive" title
- Pulsing "Press A to Play" prompt

#### 2. Main Menu (5 Buttons)
- **Gen 1 Events** - Explore Pokemon Red/Blue/Yellow event distributions
- **Gen 2 Events** - Browse Pokemon Gold/Silver/Crystal events
- **Gen 3 Events** - Discover Pokemon Ruby/Sapphire/Emerald/FR/LG events
- **Event Details** - Learn about what Pokemon events are
- **Exit Game** - Close the application

#### 3. Interactive UI
- Point-and-click with Wiimote IR pointer
- Hover effects on buttons (color changes)
- Smooth navigation between screens
- Professional gradient backgrounds

#### 4. Content Screens
Each event screen shows:
- Historical event information
- Distribution methods (Mystery Gift, E-Reader, etc.)
- Exclusive Pokemon available
- Event dates and locations
- Easy navigation back to menu

---

## 📁 Project Structure

```
Event wii game/
│
├── source/
│   └── main.cpp              # Main game source code (311 lines)
│
├── Makefile                  # DevkitPPC build configuration
├── meta.xml                  # Homebrew Channel metadata
│
├── build.sh                  # Automated build script
├── .gitignore                # Git ignore rules
├── .editorconfig             # Code style configuration
│
├── README.md                 # Technical documentation
├── INSTALL.md                # Detailed installation guide
├── QUICKSTART.md             # Fast setup guide
└── PROJECT_OVERVIEW.md       # This file
```

---

## 🛠️ Technical Details

### Development Stack
- **Language**: C++
- **Graphics**: GRRLIB (2D graphics library for Wii)
- **Input**: libwiiuse (Wiimote support with IR pointer)
- **File System**: libfat (SD card access)
- **Core**: libogc (GameCube/Wii hardware library)

### Compilation
- **Toolchain**: DevkitPPC (PowerPC compiler for Wii)
- **Target**: Wii console (PowerPC architecture)
- **Output**: .dol file (Wii executable format)

### Screen Resolution
- 640x480 pixels (standard Wii display)

### Input Support
- Wiimote IR pointer for cursor control
- A Button for selection
- B/HOME buttons for navigation back

---

## 🚀 How to Build

### Prerequisites
1. DevkitPro toolchain installed
2. DevkitPPC configured
3. Wii libraries (grrlib, libogc, libfat)

### Build Commands
```bash
# Quick build
./build.sh

# Manual build
make clean
make

# Network load (development)
make run
```

### Output
- `event_wii_game.dol` - Wii executable
- `event_wii_game.elf` - Debug symbols

---

## 📦 Installation on Wii

### What You Need
- Wii console with **Homebrew Channel installed**
- SD card (FAT32 formatted, 2GB-32GB)
- Built .dol file

### Installation Steps
1. Copy files to SD card:
   ```
   SD:/apps/event_wii_game/boot.dol
   SD:/apps/event_wii_game/meta.xml
   ```
2. Insert SD card into Wii
3. Launch Homebrew Channel
4. Select "Pokemon Event Archive"
5. Press A to start

---

## 🎯 Game Flow

```
[Power On]
    ↓
[Start Screen]
    - Animated background
    - "Press A to Play"
    ↓ (Press A)
[Main Menu]
    - 5 clickable buttons
    - Wiimote pointer cursor
    ↓ (Click button)
[Event Screen]
    - Display event information
    - Scrollable content
    ↓ (Press B)
[Back to Main Menu]
    ↓ (Select Exit)
[Exit to Homebrew Channel]
```

---

## 🎨 UI Design

### Color Scheme
- **Primary**: Dark blue gradients (#1E3A5F, #0F1D2F)
- **Accents**: Blue, Green, Orange, Purple, Red
- **Text**: White and Gray for contrast
- **Highlights**: Light blue on hover

### Button Design
- Shadow effect for depth
- Solid colored backgrounds
- White borders
- Centered text
- Hover state animation

### Layout
- Responsive to 640x480 TV display
- Safe area margins (40px from edges)
- Centered content boxes
- Clear visual hierarchy

---

## 🔧 Customization Guide

### Adding New Content
Edit `source/main.cpp`:

**Add new event screen:**
```cpp
case STATE_NEW_EVENT:
    DrawEventScreen("New Event Title",
        "Event content here\n\n"
        "- Bullet point 1\n"
        "- Bullet point 2");
    
    if (pressed & WPAD_BUTTON_B) {
        currentState = STATE_MAIN_MENU;
    }
    break;
```

**Add new button:**
```cpp
Button newButton = {240, 550, 360, 60, "New Button", COLOR_BLUE, COLOR_LIGHT_BLUE, false};
```

### Changing Colors
Modify color definitions:
```cpp
#define COLOR_CUSTOM 0xRRGGBBAA  // RGBA hex format
```

### Adding Images
1. Include image in data/ folder
2. Use GRRLIB_LoadTexture() functions
3. Draw with GRRLIB_DrawImg()

---

## 📚 Code Architecture

### Main Components

**1. State Machine**
```cpp
enum GameState {
    STATE_START,
    STATE_MAIN_MENU,
    STATE_GEN1_EVENTS,
    // ... etc
};
```

**2. Button System**
```cpp
struct Button {
    float x, y;
    float width, height;
    const char* text;
    u32 color, hoverColor;
    bool isHovered;
};
```

**3. Rendering Functions**
- `DrawStartScreen()` - Animated intro
- `DrawMainMenu()` - Menu with buttons
- `DrawEventScreen()` - Content display
- `DrawButton()` - Button rendering

**4. Input Handling**
- Wiimote IR pointer tracking
- Button press detection
- Hover state management

---

## 🐛 Common Issues & Solutions

### Build Issues
| Problem | Solution |
|---------|----------|
| "DEVKITPPC not set" | `export DEVKITPPC=/opt/devkitpro/devkitPPC` |
| "grrlib.h not found" | `sudo dkp-pacman -S grrlib` |
| "undefined reference" | Check Makefile LIBS order |

### Runtime Issues
| Problem | Solution |
|---------|----------|
| Black screen | Check FAT32 format, verify boot.dol |
| No cursor | IR sensor bar not connected |
| No response | Resync Wiimote, check batteries |

---

## 📖 Resources

### Official Documentation
- [DevkitPro Docs](https://devkitpro.org/wiki/Getting_Started)
- [GRRLIB GitHub](https://github.com/GRRLIB/GRRLIB)
- [WiiBrew Wiki](https://wiibrew.org/)

### Libraries Used
- **GRRLIB** - Graphics rendering
- **libogc** - Wii hardware access
- **libwiiuse** - Wiimote input
- **libfat** - SD card filesystem

---

## ✅ Features Implemented

- [x] Animated start screen with fade-in
- [x] "Press A to Play" pulsing text
- [x] Main menu with 5 interactive buttons
- [x] Wiimote IR pointer cursor
- [x] Button hover effects
- [x] Gen 1/2/3 event information screens
- [x] Event details information page
- [x] Navigation system (A to select, B to back)
- [x] Professional UI design
- [x] Gradient backgrounds
- [x] Complete build system
- [x] Homebrew Channel integration

---

## 🎓 What You Learned

This project demonstrates:
1. **Wii Homebrew Development** - C++ for embedded systems
2. **Graphics Programming** - 2D rendering with GRRLIB
3. **Input Handling** - Wiimote IR pointer tracking
4. **State Management** - Game state machine
5. **UI/UX Design** - Interactive menu systems
6. **Build Systems** - Makefiles and cross-compilation
7. **Embedded Systems** - PowerPC architecture

---

## 🚀 Next Steps

### Enhancements You Could Add
1. **Sound Effects** - Use asndlib for audio
2. **Background Music** - MP3 playback
3. **More Events** - Gen 4, 5, 6+ content
4. **Images** - Pokemon sprites and event images
5. **Search Feature** - Find specific events
6. **Favorites** - Save favorite events
7. **Animations** - Smooth transitions between screens
8. **Multi-language** - Support different languages

### Advanced Features
- Save data to SD card
- Load event data from external files
- Network features (WiiConnect24)
- Screenshot capability
- Custom font rendering

---

## 📄 License

This project is for educational purposes. Feel free to modify and learn from it!

**Important:**
- This is homebrew software (not piracy)
- Use only on your own Wii console
- Don't distribute commercial game files
- Respect Nintendo's intellectual property

---

## 🎮 Enjoy Your Wii Game!

You've created a real, working Wii game that runs on actual hardware. This is proper homebrew development using official tools and libraries.

**Build it. Install it. Play it on your Wii!**

For questions, see:
- `QUICKSTART.md` - Fast setup guide
- `INSTALL.md` - Detailed instructions  
- `README.md` - Technical details

---

*Built with DevkitPro • Powered by GRRLIB • Made for Wii Homebrew*

