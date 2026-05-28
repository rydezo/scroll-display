#include "scroll.h"
#include "framebuffer.h"

static pi_framebuffer_t *fb = NULL;

/* helper to wrap coordinates */
int wrap(int v) {
    return ((v % 8) + 8) % 8;
}

/* helper to set a pixel safely */
extern int rotation;

void set_pixel(int x, int y, uint16_t color) {

    int rx = x;
    int ry = y;

    if (rotation == 90) {
        int temp = rx;
        rx = ry;
        ry = 7 - temp;
    }
    else if (rotation == 180) {
        rx = 7 - rx;
        ry = 7 - ry;
    }
    else if (rotation == 270) {
        int temp = rx;
        rx = 7 - ry;
        ry = temp;
    }

    fb->bitmap->pixel[wrap(rx)][wrap(ry)] = color;
}


void open_display(void) {
    if (fb != NULL) return;

    fb = getFrameBuffer();
    if (fb == NULL) return;

    clearFrameBuffer(fb, 0);
}

void close_display(void) {
    if (fb != NULL) {
        freeFrameBuffer(fb);
        fb = NULL;
    }
}

void clear_display(void) {
    if (fb != NULL) {
        clearFrameBuffer(fb, 0);
    }
}

void draw_R(int x, int y, uint16_t c) {
    // fix R
    // top bar
    set_pixel(x+1, y+0, c);
    set_pixel(x+2, y+0, c);
    set_pixel(x+3, y+0, c);

    // left vertical + right edge
    set_pixel(x+0, y+1, c);
    set_pixel(x+3, y+1, c);

    set_pixel(x+0, y+2, c);
    set_pixel(x+3, y+2, c);

    // middle bar
    set_pixel(x+1, y+3, c);
    set_pixel(x+2, y+3, c);
    set_pixel(x+3, y+3, c);

    // diagonal leg
    set_pixel(x+1, y+4, c);

    set_pixel(x+3, y+4, c);
    set_pixel(x+3, y+5, c);
    set_pixel(x+0, y+5, c);
}

void draw_O(int x, int y, uint16_t c) {
    for (int i = 0; i < 4; i++) {
        set_pixel(x+i,y,c);
        set_pixel(x+i,y+5,c);
    }
    for (int i = 0; i < 6; i++) {
        set_pixel(x,y+i,c);
        set_pixel(x+3,y+i,c);
    }
}

void draw_A(int x, int y, uint16_t c) {
    for (int i = 1; i < 5; i++) {
        set_pixel(x+i,y,c);
    }
    for (int i = 0; i < 6; i++) {
        set_pixel(x,y+i,c);
        set_pixel(x+4,y+i,c);
    }
    for (int i = 0; i < 5; i++) {
        set_pixel(x+i,y+3,c);
    }
}

void draw_M(int x, int y, uint16_t c) {
    for (int i = 0; i < 6; i++) {
        set_pixel(x,y+i,c);
        set_pixel(x+4,y+i,c);
    }
    set_pixel(x+1,y+1,c);
    set_pixel(x+2,y+2,c);
    set_pixel(x+3,y+1,c);
}

// Main display function

void display_letter(char letter, int xOffset, int yOffset) {

    if (fb == NULL) return;

    clearFrameBuffer(fb, 0);

    extern uint16_t current_color;
    uint16_t white = current_color;

    int x = xOffset;
    int y = yOffset;

    if (letter == 'R') draw_R(x,y,white);
    else if (letter == 'O') draw_O(x,y,white);
    else if (letter == 'A') draw_A(x,y,white);
    else if (letter == 'M') draw_M(x,y,white);
}