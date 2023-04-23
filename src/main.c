#include <interface.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

int
main ()
{
  if (!isatty (0) || !isatty (1))
    {
      fprintf (stderr, "Ошибка открытия терминала.\n");
      return -1;
    }

  sc_memoryInit ();
  sc_regInit ();

  interface ();

  return 0;
}
