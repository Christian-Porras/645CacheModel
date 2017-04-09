/*-------------------------------------------------------------
* Project 1: Cache Simulation
* Authors: Chris Porras, Brad Gibbons, Evan Bissell
* Version: V 1.0
* Date: April 13th, 2017
* Description: Simulates a cache by reading in addresses from a file and placing them
* in an array
*-------------------------------------------------------------- */

//Libraries
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

//define the cache size
#define cacheSize_exp 15
#define cacheSize_num (1 << cacheSize_exp)

//define address size
#define address_size 32

//define block size
#define blockSize_exp 6
#define blockSize_num (1 << blockSize_exp)
#define blockSize_mask (blockSize_num - 1)

int main(int argc, char ** argv){
  uint32_t *address;
  FILE* fp = fopen("/home/gminden/EECS_645/AddressTrace_FirstIndex.bin", "rb");
  /*while(fread(address,4,1,fp)) {
    printf("%x\n",*address);
  }*/
  fclose(fp);
  printf("Hello World\n" );
  return 0;
}
