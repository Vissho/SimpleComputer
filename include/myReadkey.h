#pragma once

enum keys
{
  LOAD,
  SAVE,
  RUN,
  STEP,
  RESET,
  F5,
  F6,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER,
  OTHER
};

int rk_readkey (enum keys *k);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
