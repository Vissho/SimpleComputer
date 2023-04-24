#include <ctest.h>
#include <mySignal.h>
#include <stdio.h>

CTEST (timer, correctly_timer)
{
  int flag = timer ();
  ASSERT_EQUAL (0, flag);
}

CTEST (source, correctly_source)
{
  int flag = source ();
  ASSERT_EQUAL (0, flag);
}

CTEST (reboot, correctly_reboot)
{
  int flag = reboot ();
  ASSERT_EQUAL (0, flag);
}
