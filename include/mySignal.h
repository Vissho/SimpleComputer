#pragma once

extern int instruction_counter;

void stop_timer (void);
void signalhandler_1 (__attribute__ ((unused)) int signo);
void signalhandler_2 (__attribute__ ((unused)) int signo);
void signalhandler_3 (__attribute__ ((unused)) int signo);
int timer (void);
int source (void);
int reboot (void);
