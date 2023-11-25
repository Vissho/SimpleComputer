#pragma once

enum keys {
    LOAD,
    SAVE,
    RUN,
    STEP,
    RESET,
    F5,
    F6,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    OTHER
};

#define F5_KEY "\E[15~"
#define F6_KEY "\E[17~"
#define DOWN_KEY "\E[B"
#define UP_KEY "\E[A"
#define LEFT_KEY "\E[D"
#define RIGHT_KEY "\E[C"
#define ENTER_KEY "\n"

extern struct termios tsaved;

int rk_readkey(enum keys* k);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
