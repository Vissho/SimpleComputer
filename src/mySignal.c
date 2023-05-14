#include <interface.h>
#include <myCU.h>
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
reboot_timer (void)
{

  struct itimerval tval;

  tval.it_interval.tv_sec = 0;
  tval.it_interval.tv_usec = 100000;
  tval.it_value.tv_sec = 0;
  tval.it_value.tv_usec = 100000;

  setitimer (ITIMER_REAL, &tval, NULL);
}

void
signalhandler_1 (__attribute__ ((unused)) int signo)
{
  instruction_counter_old = instruction_counter;
  CU ();
  if (instruction_counter_old == instruction_counter)
    instruction_counter++;
  if (instruction_counter == 100)
    raise (SIGUSR1);
  position = instruction_counter;
}

void
signalhandler_2 (__attribute__ ((unused)) int signo)
{
  stop_timer ();
  instruction_counter = instruction_counter_old;
  sc_regSet (T, 0);
}

int
timer (void)
{
  struct itimerval nval, oval;

  signal (SIGALRM, signalhandler_1);
  signal (SIGUSR1, signalhandler_2);

  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 100000;
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 100000;

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
