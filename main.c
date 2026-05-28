#include "scroll.h"

uint16_t current_color;
int rotation = 0;
int initial_speed = 1;

void dot_roll(void);

char letters[] = {'R', 'O', 'A', 'M'};
int numLetters = 4;

int currentLetterIndex = 0;

double x = 0;
double y = 0;

int vx = 0;
int vy = 0;

int running = 1;

void print_help(char *progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Options:\n");
    printf("  -h              Show this help message and exit\n");
    printf("  -c COLOR        Set color (white, red, green, blue)\n");
    printf("  -r DEGREES      Rotate display (0, 90, 180, 270)\n");
    printf("  -s SPEED        Set initial scroll speed (1-10)\n");
    printf("\n");
    printf("Use joystick to move and press to switch letters.\n");
}

void handler(unsigned int code) {
    if (code == KEY_UP) {
        vx -= 1;
    }
    else if (code == KEY_DOWN) {
        vx += 1;
    }
    else if (code == KEY_RIGHT) {
        vy += 1;
    }
    else if (code == KEY_LEFT) {
        vy -= 1;
    }
    else if (code == KEY_ENTER) {
        currentLetterIndex++;

        if (currentLetterIndex >= numLetters) {
            clear_display();
            running = 0;
        }
    }

    // clamp speeds to [-10, 10]
    if (vx > 10) vx = 10;
    if (vx < -10) vx = -10;

    if (vy > 10) vy = 10;
    if (vy < -10) vy = -10;
}

int main(int argc, char *argv[]) {
    
    // default values
current_color = getColor(255,255,255); // white

for (int i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-h") == 0) {
        print_help(argv[0]);
        return 0;
    }

    else if (strcmp(argv[i], "-c") == 0) {
        if (i + 1 >= argc) {
            print_help(argv[0]);
            return 1;
        }

        i++;

        if (strcmp(argv[i], "white") == 0)
            current_color = getColor(255,255,255);
        else if (strcmp(argv[i], "red") == 0)
            current_color = getColor(255,0,0);
        else if (strcmp(argv[i], "green") == 0)
            current_color = getColor(0,255,0);
        else if (strcmp(argv[i], "blue") == 0)
            current_color = getColor(0,0,255);
        else {
            print_help(argv[0]);
            return 1;
        }
    }

    else if (strcmp(argv[i], "-r") == 0) {
        if (i + 1 >= argc) {
            print_help(argv[0]);
            return 1;
        }

        i++;
        rotation = atoi(argv[i]);

        if (rotation != 0 && rotation != 90 &&
            rotation != 180 && rotation != 270) {
            print_help(argv[0]);
            return 1;
        }
    }

    else if (strcmp(argv[i], "-s") == 0) {
        if (i + 1 >= argc) {
            print_help(argv[0]);
            return 1;
        }

        i++;
        initial_speed = atoi(argv[i]);

        if (initial_speed < 1 || initial_speed > 10) {
            print_help(argv[0]);
            return 1;
        }

        vx = initial_speed;
        vy = initial_speed;
    }

    else {
        print_help(argv[0]);
        return 1;
    }
}

    open_display();
    open_input();

    double dt = 0.05; // 50 ms

    while (running) {

        // check joystick input
        check_input(handler, 50);

        //  update position using velocity
        x += vx * dt;
        y += vy * dt;

        // draw current letter
        display_letter(
            letters[currentLetterIndex],
            (int)x,
            (int)y
        );

        // control speed of loop
        usleep(dt * 1000000);
    }

    close_input();
    close_display();

    return 0;
}    

void dot_roll(void) {
    int vx;
    int vy;

    printf("Enter vx: ");
    scanf("%d", &vx);

    printf("Enter vy: ");
    scanf("%d", &vy);

    double x = 0;
    double y = 0;

    double dt = 0.05;

    while (1)
    {
        display_letter('a', (int)x, (int)y);

        usleep(dt * 1000000);

        x = x + dt * vx;
        y = y + dt * vy;
    }
}