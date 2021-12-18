/* BEEBS local library variants

   Copyright (C) 2019 Embecosm Limited.

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of Embench and was formerly part of the Bristol/Embecosm
   Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

/* These are very simple local versions of library routines, to ensure the
   code is compiled with the flags used for the benchmark.  Not all library
   routines are here, just ones that cause a lot of unecessary load, or where
   there is variation between platforms and architectures. */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "beebsc.h"

/* Seed for the random number generator */

static long int seed = 0;

/* Heap records and sane initial values */

static void *heap_ptr = NULL;
static void *heap_end = NULL;
static size_t heap_requested = 0;


/* Yield a sequence of random numbers in the range [0, 2^15-1].

   long int is guaranteed to be at least 32 bits. The seed only ever uses 31
   bits (so is positive).

   For BEEBS this gets round different operating systems using different
   multipliers and offsets and RAND_MAX variations. */

int
rand_beebs (void)
{
  seed = (seed * 1103515245L + 12345) & ((1UL << 31) - 1);
  return (int) (seed >> 16);
}


/* Initialize the random number generator */

void
srand_beebs (unsigned int new_seed)
{
  seed = (long int) new_seed;
}




/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
