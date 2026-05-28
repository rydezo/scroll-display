#ifndef SCROLL_H
#define SCROLL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include "framebuffer.h"
#include "sense.h"

void open_display(void);
void close_display(void);
void display_letter(char letter, int xOffset, int yOffset);
void clear_display(void);
void open_input(void);
void close_input(void);
void check_input(void (*callback)(unsigned int code), int delay);

#endif