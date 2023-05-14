#pragma once

extern int instruction_counter;
extern int position;

void stop_timer (void);
void reboot_timer (void);
void signalhandler_1 (__attribute__ ((unused)) int signo);
void signalhandler_2 (__attribute__ ((unused)) int signo);
int timer (void);
int source (void);
