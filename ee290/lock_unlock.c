// See LICENSE for license details.

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BAREMETAL
#include <sys/mman.h>
#endif
#include "include/gemmini.h"

int main() {
#ifndef BAREMETAL
    if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
      perror("mlockall failed");
      exit(1);
    }
#endif

  //printf("locking\n");
  gemmini_lock();
  //printf("locked\n");
  //printf("Flush Gemmini TLB of stale virtual addresses\n");
  gemmini_flush(0);

  //printf("unlocking\n");
  gemmini_unlock();
  printf("Done\n");

  exit(0);
}

