#include <interface.h>
#include <mySignal.h>
#include <mySimpleComputer.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static int instruction_counter_old = -1;

void
stop_timer (void)
{
  struct itimerval tval;

  tval.it_interval.tv_sec = 0;
  tval.it_interval.tv_usec = 0;
  tval.it_value.tv_sec = 0;
  tval.it_value.tv_usec = 0;

  setitimer (ITIMER_REAL, &tval, NULL);
}

void
signalhandler_1 (__attribute__ ((unused)) int signo)
{
  if (instruction_counter_old == -1)
    instruction_counter_old = instruction_counter;
  instruction_counter++;
  print_instructionCounter ();
}

void
signalhandler_2 (__attribute__ ((unused)) int signo)
{
  stop_timer ();
  instruction_counter = instruction_counter_old;
  print_instructionCounter ();
}

void
signalhandler_3 (__attribute__ ((unused)) int signo)
{

  struct itimerval tval;

  tval.it_interval.tv_sec = 5;
  tval.it_interval.tv_usec = 0;
  tval.it_value.tv_sec = 5;
  tval.it_value.tv_usec = 0;

  setitimer (ITIMER_REAL, &tval, NULL);
  print_instructionCounter ();
}

int
timer (void)
{
  struct itimerval nval, oval;

  signal (SIGALRM, signalhandler_1);
  signal (SIGUSR1, signalhandler_2);
  signal (SIGUSR2, signalhandler_3);

  nval.it_interval.tv_sec = 5;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 5;
  nval.it_value.tv_usec = 0;

  if (setitimer (ITIMER_REAL, &nval, &oval))
    return -5;

  return 0;
}

int
source (void)
{
  raise (SIGUSR1);

  return 0;
}

int
reboot (void)
{
  raise (SIGUSR2);

  return 0;
}
