#include <myReadkey.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static int N = 16;
struct termios tsaved;

int rk_readkey(enum keys* k)
{
    if (rk_mytermsave())
        return -5;

    if (rk_mytermregime(0, 0, 0, 0, 1))
        return -5;

    char str[N];
    if (read(0, str, sizeof(str)) == -1)
        return -5;

    if (str[0] == 'l') {
        *k = LOAD;
    } else if (str[0] == 's') {
        *k = SAVE;
    } else if (str[0] == 'r') {
        *k = RUN;
    } else if (str[0] == 't') {
        *k = STEP;
    } else if (str[0] == 'i') {
        *k = RESET;
    } else if (strncmp(str, F5_KEY, 4) == 0) {
        *k = F5;
    } else if (strncmp(str, F6_KEY, 4) == 0) {
        *k = F6;
    } else if (strncmp(str, DOWN_KEY, 3) == 0) {
        *k = DOWN;
    } else if (strncmp(str, UP_KEY, 3) == 0) {
        *k = UP;
    } else if (strncmp(str, LEFT_KEY, 3) == 0) {
        *k = LEFT;
    } else if (strncmp(str, RIGHT_KEY, 3) == 0) {
        *k = RIGHT;
    } else if (strncmp(str, ENTER_KEY, 1) == 0) {
        *k = ENTER;
    } else {
        *k = OTHER;
    }

    if (rk_mytermrestore())
        return -5;

    return 0;
}

int rk_mytermsave(void)
{
    if (tcgetattr(0, &tsaved))
        return -5;

    return 0;
}

int rk_mytermrestore(void)
{
    if (tcsetattr(0, TCSANOW, &tsaved))
        return -5;

    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios temp;

    if (tcgetattr(0, &temp))
        return -5;

    if (regime == 1) {
        temp.c_lflag |= ICANON;
    } else if (regime == 0) {
        temp.c_lflag &= ~ICANON;
    } else {
        return -5;
    }

    if (vtime == 1) {
        temp.c_lflag |= VTIME;
    } else if (vtime == 0) {
        temp.c_lflag &= ~VTIME;
    } else {
        return -5;
    }

    if (vmin == 1)
        temp.c_lflag |= VMIN;
    else if (vmin == 0) {
        temp.c_lflag &= ~VMIN;
    } else {
        return -5;
    }

    if (echo == 1)
        temp.c_lflag |= ECHO;
    else if (echo == 0)
        temp.c_lflag &= ~ECHO;
    else {
        return -5;
    }

    if (sigint == 1)
        temp.c_lflag |= ISIG;
    else if (sigint == 0)
        temp.c_lflag &= ~ISIG;
    else {
        return -5;
    }

    if (tcsetattr(0, TCSANOW, &temp))
        return -5;

    return 0;
}
