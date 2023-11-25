#include <ctest.h>
#include <myReadkey.h>
#include <stdio.h>

CTEST(rk_readkey, correctly_rk_readkey)
{
    enum keys k;
    int flag = rk_readkey(&k);
    ASSERT_EQUAL(0, flag);
}

CTEST(rk_mytermsave, correctly_rk_mytermsave)
{
    int flag = rk_mytermsave();
    ASSERT_EQUAL(0, flag);
}

CTEST(rk_mytermrestore, correctly_rk_mytermrestore)
{
    int flag = rk_mytermrestore();
    ASSERT_EQUAL(0, flag);
}

CTEST(rk_mytermregime, correctly_rk_mytermregime)
{
    int flag = rk_mytermregime(1, 0, 0, 1, 1);
    ASSERT_EQUAL(0, flag);
}
