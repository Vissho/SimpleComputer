#include <ctest.h>
#include <mySimpleComputer.h>

CTEST (initialization_of_memory_and_register,
       correctly_initialization_of_memory_and_register)
{
  sc_memoryInit ();
  sc_regInit ();

  ASSERT_NOT_NULL (&REGISTER);
  ASSERT_NOT_NULL (&RAM);
}

CTEST (memory_set_and_get, correctly_memory_set_and_get)
{
  sc_memoryInit ();
  sc_regInit ();

  int temp;
  sc_memorySet (55, 55);
  sc_memoryGet (55, &temp);

  ASSERT_EQUAL (55, temp);
}

CTEST (memory_save_and_load, correctly_memory_save_and_load)
{
  sc_memoryInit ();
  sc_regInit ();

  sc_memorySet (55, 55);
  sc_memorySet (1, 6);
  sc_memorySet (7, 9);

  sc_memorySave ("test/file.bin");

  sc_memorySet (55, 0);
  sc_memorySet (1, 0);
  sc_memorySet (7, 0);

  sc_memoryLoad ("test/file.bin");

  int s1, s2, s3;
  sc_memoryGet (55, &s1);
  sc_memoryGet (1, &s2);
  sc_memoryGet (7, &s3);

  ASSERT_EQUAL (55, s1);
  ASSERT_EQUAL (6, s2);
  ASSERT_EQUAL (9, s3);
}

CTEST (register_set_and_get, correctly_register_set_and_get)
{
  sc_memoryInit ();
  sc_regInit ();

  int temp;
  sc_regSet (M, 1);
  sc_regGet (M, &temp);

  ASSERT_EQUAL (1, temp);
}

CTEST (command_encode_and_decode, correctly_command_encode_and_decode)
{
  sc_memoryInit ();
  sc_regInit ();

  int n = 0, com = 0, oper = 0;
  sc_commandEncode (33, 59, &n);
  sc_commandDecode (n, &com, &oper);

  ASSERT_EQUAL (4283, n);
  ASSERT_EQUAL (33, com);
  ASSERT_EQUAL (59, oper);
}
