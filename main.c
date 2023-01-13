extern void game(void);

#define VIDEO_MEMORY ((volatile char*) 0x500FE800)
#define VIDEO_NUM_ROWS 36
#define VIDEO_NUM_COLS 64

static void clearScreen(void)
{
    for (unsigned i = 0; i < VIDEO_NUM_ROWS * VIDEO_NUM_COLS; ++i)
        VIDEO_MEMORY[i] = ' ';
}

static void printEndingMsg(void)
{
    VIDEO_MEMORY[0] = 'T';
    VIDEO_MEMORY[1] = 'h';
    VIDEO_MEMORY[2] = 'e';
    VIDEO_MEMORY[3] = ' ';
    VIDEO_MEMORY[4] = 'e';
    VIDEO_MEMORY[5] = 'n';
    VIDEO_MEMORY[6] = 'd';
    VIDEO_MEMORY[7] = '!';
}

int main()
{
    game();
    clearScreen();
    printEndingMsg();
    for (;;);
}
