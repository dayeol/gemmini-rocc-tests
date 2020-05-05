// See LICENSE for license details.

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BAREMETAL
#include <sys/mman.h>
#endif
#include "include/gemmini.h"

int main(int argc, void** argv) {
#ifndef BAREMETAL
    if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
      perror("mlockall failed");
      exit(1);
    }
#endif
		
	elem_t In[DIM][DIM];
  elem_t Out[DIM][DIM];
  elem_t Identity[DIM][DIM];
	uintptr_t addr = 0x3fffffeff0;
	printf("trying to read out virt: 0x%x\n", addr);

  // printf("Flush Gemmini TLB of stale virtual addresses\n");
  // printf("Calculate the scratchpad addresses of all our matrices\n");
  // printf("  Note: The scratchpad is \"row-addressed\", where each address contains one matrix row\n");
  size_t In_sp_addr = 0;
  size_t Out_sp_addr = BANK_ROWS;
  size_t Identity_sp_addr = 2*BANK_ROWS;

  gemmini_mvin(addr, In_sp_addr);
  gemmini_mvout(Out, In_sp_addr);	
  // printf("Move \"In\" matrix from main memory into Gemmini's scratchpad\n");
  //gemmini_mvin(In, In_sp_addr);

  // printf("Move \"Identity\" matrix from main memory into Gemmini's scratchpad\n");
  //gemmini_mvin(Identity, Identity_sp_addr);

  // printf("Multiply \"In\" matrix with \"Identity\" matrix with a bias of 0\n");
  //gemmini_config_ex(WEIGHT_STATIONARY, 0, 0, 0, 0);
  //gemmini_preload(Identity_sp_addr, Out_sp_addr);
  //gemmini_compute_preloaded(In_sp_addr, GARBAGE_ADDR);

  // printf("Move \"Out\" matrix from Gemmini's scratchpad into main memory\n");
  //gemmini_mvout(Out, Out_sp_addr);

  // printf("Fence till Gemmini completes all memory operations\n");
  gemmini_fence();

  printf("\"Out\" matrix:\n");
	printMatrix(Out);
  printf("\n");

  // printf("Check whether \"In\" and \"Out\" matrices are identical\n");
  /*
	if (!is_equal(In, Out)) {
    printf("Input and output matrices are different!\n");
    printf("\"In\" matrix:\n");
    printMatrix(In);
    printf("\"Out\" matrix:\n");
    printMatrix(Out);
    printf("\n");

    printf("FAIL\n");
    exit(1);
  }

  printf("Input and output matrices are identical, as expected\nPASS\n");
	*/
  exit(0);
}

