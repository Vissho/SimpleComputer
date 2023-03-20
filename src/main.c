#include <interface.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

int
main ()
{
  //fd = open ("/dev/tty", O_WRONLY);
  if (!isatty (0) || !isatty (1))
    {
      fprintf (stderr, "Ошибка открытия терминала.\n");
      //close (fd);
      return -1;
    }

  sc_memoryInit ();
  sc_regInit ();

  sc_memorySet (0, 0x7fff);
  sc_memorySet (10, 1010);
  sc_memorySet (15, 0001);
  sc_memorySet (27, 10);
  sc_memorySet (33, 100);
  sc_memorySet (55, 5555);
  sc_memorySet (99, -9999);
  sc_memorySet (20, 39321);
  sc_memorySet (1, 123);
  sc_memorySet (2, 4567);
  sc_memorySet (3, 8900);

  //sc_regSet (M, 1);

  interface ();

  close (fd);
  return 0;
}
