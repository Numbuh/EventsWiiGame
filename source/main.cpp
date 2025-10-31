#include <gccore.h>
#include <wiiuse/wpad.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>

// Screen states
enum GameState {
    STATE_START,
    STATE_MAIN_MENU,
    STATE_FILE_SELECTION,
    STATE_UPLOADING,
    STATE_UPLOAD_COMPLETE,
    STATE_EXIT
};

// GBA Communication structures
struct GBAFile {
    char filename[64];
    u8* data;
    u32 size;
    bool isLoaded;
};

struct UploadStatus {
    bool isUploading;
    int progress;
    char statusMessage[128];
    bool hasError;
};

// Global variables
static void *xfb = NULL;
static GXRModeObj *rmode;

GameState currentState = STATE_START;
GameState lastState = STATE_START;
int startScreenTimer = 0;

// GBA Communication globals
GBAFile currentFile = {0};
UploadStatus uploadStatus = {0};
bool gbaConnected = false;

// Function prototypes
void DrawStartScreen();
void DrawMainMenu();
void DrawFileSelection();
void DrawUploading();
void DrawUploadComplete();

// GBA Communication functions
bool CheckGBAConnection();
bool LoadEventFile(const char* filename);
void StartUpload();
void UpdateUploadProgress();
void CompleteUpload();

// GBA Communication Functions
bool CheckGBAConnection() {
    // Check if GBA is connected via GameCube controller port
    // This would use SI (Serial Interface) to detect GBA connection
    // For now, we'll simulate no connection until real implementation
    
    // TODO: Implement actual SI communication to detect GBA
    // SI_GetStatus() or similar function would be used here
    
    return false; // Simulate no GBA connected
}

bool LoadEventFile(const char* filename) {
    // Load Pokemon event file from project directory
    FILE *file = fopen(filename, "rb");
    if (!file) {
        // Try loading the actual GBA file in the project
        file = fopen("BUUJ - ROCKS Metang (ENG).gba", "rb");
        if (!file) {
            return false;
        }
        strcpy(currentFile.filename, "BUUJ - ROCKS Metang (ENG).gba");
    } else {
        strcpy(currentFile.filename, filename);
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    currentFile.size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate memory for file data
    currentFile.data = (u8*)malloc(currentFile.size);
    if (!currentFile.data) {
        fclose(file);
        return false;
    }
    
    // Read file data
    size_t bytesRead = fread(currentFile.data, 1, currentFile.size, file);
    fclose(file);
    
    if (bytesRead != currentFile.size) {
        free(currentFile.data);
        currentFile.data = NULL;
        return false;
    }
    
    currentFile.isLoaded = true;
    return true;
}

void StartUpload() {
    uploadStatus.isUploading = true;
    uploadStatus.progress = 0;
    uploadStatus.hasError = false;
    strcpy(uploadStatus.statusMessage, "Starting upload...");
    currentState = STATE_UPLOADING;
}

void UpdateUploadProgress() {
    if (!uploadStatus.isUploading) return;
    
    // Simulate upload progress
    uploadStatus.progress += 2;
    if (uploadStatus.progress >= 100) {
        CompleteUpload();
    }
}

void CompleteUpload() {
    uploadStatus.isUploading = false;
    uploadStatus.progress = 100;
    strcpy(uploadStatus.statusMessage, "Upload complete!");
    currentState = STATE_UPLOAD_COMPLETE;
}

int main(int argc, char **argv) {
    // Initialize video system
    VIDEO_Init();
    WPAD_Init();
    
    // Get video mode
    rmode = VIDEO_GetPreferredMode(NULL);
    
    // Allocate single framebuffer
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    
    // Configure video
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
    
    // Initialize console
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->efbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    
    // Main game loop
    while(currentState != STATE_EXIT) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);
        
        // Only clear screen when state changes
        if (currentState != lastState) {
            printf("\x1b[2J");
            lastState = currentState;
        }
        
        // Handle state-specific input and rendering
        switch(currentState) {
            case STATE_START:
                DrawStartScreen();
                startScreenTimer++;
                
                if (pressed & WPAD_BUTTON_A || pressed & WPAD_BUTTON_2) {
                    currentState = STATE_MAIN_MENU;
                }
                break;
                
            case STATE_MAIN_MENU:
                DrawMainMenu();
                
                // Check GBA connection status
                gbaConnected = CheckGBAConnection();
                
                if (pressed & WPAD_BUTTON_A) {
                    if (gbaConnected) {
                        currentState = STATE_FILE_SELECTION;
                    }
                }
                break;
                
            case STATE_FILE_SELECTION:
                // Auto-load the GBA file when entering this screen
                if (!currentFile.isLoaded) {
                    LoadEventFile("BUUJ - ROCKS Metang (ENG).gba");
                }
                
                DrawFileSelection();
                
                if (pressed & WPAD_BUTTON_B) {
                    currentState = STATE_MAIN_MENU;
                }
                
                if (pressed & WPAD_BUTTON_A) {
                    if (currentFile.isLoaded) {
                        StartUpload();
                    }
                }
                break;
            
            case STATE_UPLOADING:
                DrawUploading();
                UpdateUploadProgress();
                break;
            
            case STATE_UPLOAD_COMPLETE:
                DrawUploadComplete();
                
                if (pressed & WPAD_BUTTON_A) {
                    currentState = STATE_MAIN_MENU;
                }
                break;
        }
        
        // Simple frame rendering (no double buffering to reduce flashing)
        VIDEO_Flush();
        VIDEO_WaitVSync();
    }
    
    return 0;
}

void DrawStartScreen() {
    printf("\x1b[5;15H========================================\n");
    printf("\x1b[6;15H    Pokemon Event File Uploader\n");
    printf("\x1b[7;15H========================================\n");
    printf("\x1b[10;20HWelcome to the Pokemon Event Uploader!\n");
    printf("\x1b[12;20HThis tool uploads Pokemon event files\n");
    printf("\x1b[13;20Hto your Game Boy Advance via the\n");
    printf("\x1b[14;20HGameCube controller to GBA cable.\n");
    
    if (startScreenTimer >= 60 && (startScreenTimer / 30) % 2 == 0) {
        printf("\x1b[18;25H>>> Press A to Continue <<<\n");
    }
}

void DrawMainMenu() {
    printf("\x1b[5;15H========================================\n");
    printf("\x1b[6;15H    Pokemon Event File Uploader\n");
    printf("\x1b[7;15H========================================\n");
    
    printf("\x1b[10;20HGBA Connection Status:\n");
    if (gbaConnected) {
        printf("\x1b[11;20H[OK] GBA Connected\n");
        printf("\x1b[13;20HReady to upload event files!\n");
        printf("\x1b[20;25H>>> Press A to Upload <<<\n");
    } else {
        printf("\x1b[11;20H[ERROR] GBA Not Connected\n");
        printf("\x1b[13;20HPlease connect your GBA first:\n");
        printf("\x1b[15;20H1. Use GameCube controller to GBA cable\n");
        printf("\x1b[16;20H2. Insert Pokemon game cartridge\n");
        printf("\x1b[17;20H3. Power on the GBA\n");
        printf("\x1b[19;20HUpload disabled until GBA is connected\n");
    }
    
    printf("\x1b[22;25H>>> Press HOME to Exit <<<\n");
}

void DrawFileSelection() {
    printf("\x1b[5;15H========================================\n");
    printf("\x1b[6;15H    Select Event File\n");
    printf("\x1b[7;15H========================================\n");
    
    printf("\x1b[10;20HAvailable Event Files:\n");
    printf("\x1b[12;20H1. BUUJ - ROCKS Metang (ENG).gba\n");
    printf("\x1b[13;20H   Pokemon Ruby/Sapphire/Emerald\n");
    printf("\x1b[14;20H   Metang Distribution Event\n");
    
    printf("\x1b[17;20HFile Information:\n");
    printf("\x1b[18;20HName: %s\n", currentFile.filename);
    printf("\x1b[19;20HSize: %d bytes (%.1f KB)\n", currentFile.size, currentFile.size / 1024.0f);
    printf("\x1b[20;20HLoaded: %s\n", currentFile.isLoaded ? "Yes" : "No");
    
    printf("\x1b[22;20H>>> Press A to Upload File <<<\n");
    printf("\x1b[24;20H>>> Press B to Go Back <<<\n");
}

void DrawUploading() {
    printf("\x1b[5;15H========================================\n");
    printf("\x1b[6;15H    Uploading Event File\n");
    printf("\x1b[7;15H========================================\n");
    
    printf("\x1b[10;20HFile: %s\n", currentFile.filename);
    printf("\x1b[11;20HSize: %d bytes\n", currentFile.size);
    printf("\x1b[12;20HStatus: %s\n", uploadStatus.statusMessage);
    
    printf("\x1b[15;20HProgress: [");
    int barWidth = 30;
    int filledWidth = (uploadStatus.progress * barWidth) / 100;
    
    for(int i = 0; i < barWidth; i++) {
        if(i < filledWidth) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", uploadStatus.progress);
    
    printf("\x1b[18;20HPlease do not disconnect the GBA\n");
    printf("\x1b[19;20Hor remove the cartridge during upload.\n");
}

void DrawUploadComplete() {
    printf("\x1b[5;15H========================================\n");
    printf("\x1b[6;15H    Upload Complete!\n");
    printf("\x1b[7;15H========================================\n");
    
    printf("\x1b[10;20HSUCCESS!\n");
    printf("\x1b[12;20HThe Pokemon event file has been\n");
    printf("\x1b[13;20Hsuccessfully uploaded to your GBA.\n");
    
    printf("\x1b[16;20HFile: %s\n", currentFile.filename);
    printf("\x1b[17;20HSize: %d bytes\n", currentFile.size);
    
    printf("\x1b[20;20HYou can now:\n");
    printf("\x1b[21;20H- Start your Pokemon game\n");
    printf("\x1b[22;20H- Access the event in-game\n");
    printf("\x1b[23;20H- Upload another event file\n");
    
    printf("\x1b[25;25H>>> Press A to Continue <<<\n");
}