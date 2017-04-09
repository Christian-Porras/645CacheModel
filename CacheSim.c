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

//define associativity variables. These will be defined within main
#define cacheAssociativity_exp 0
#define cacheAssociativity_num (1<<cacheAssociativity_exp)

//declare line variables. These will be defined within main
#define lines_exp ((cacheSize_exp) - (cacheAssociativity_exp + blockSize_exp))
#define lines_num (1 << lines_exp)
#define lines_mask (lines_num - 1)

//declare tag variables. These will be defined within main
int tag_exp;
int tag_num;
int tag_mask;

//hit variable
int hit;

//struct for an element
//elements are the addresses stored in the cache from the address trace
struct element{
  int tag;
  int line;
  int valid;
};

//declare cache array
struct element cache[lines_num][cacheAssociativity_num];



void printResults(double hitRatio, char * fileName){
  printf("Name of File read: %s\n", fileName);
  printf("Associativity used: %i\n", cacheAssociativity_num);
  printf("Number of Hits: %i\n", hit );
  printf("Hit Ratio: %f\n", hitRatio);
  return;
}

//replace element in the cache with current element passed through as an argument
//currently set up for random replacement
void bump(struct element entry){
  int i = rand() % cacheAssociativity_num;
  cache[entry.line][i].tag = entry.tag;
  cache[entry.line][i].line = entry.line;
  cache[entry.line][i].valid = entry.valid;
}



//place an element into the cache

int place(struct element entry){
  for(int i = 0; i < cacheAssociativity_num; i++){
    //Check for element validity
    if(cache[entry.line][i].valid){
      //compare tag values
      if(entry.tag == cache[entry.line][i].tag){
        return 1;
      }
    }
  }
  //if not found, check for open block
  for(int i = 0; i< cacheAssociativity_num; i++){
    if (! cache[entry.line][i].valid){
      cache[entry.line][i].tag = entry.tag;
      cache[entry.line][i].line = entry.line;
      cache[entry.line][i].valid = entry.valid;
      return 0;
    }
  }
  //if full, bump and replace
  bump(entry);
  return 0;
}


int main(int argc, char ** argv){

  //determine the tag size
  tag_exp = (address_size - blockSize_exp - lines_exp);
  tag_num = (1 << tag_exp);
  tag_mask = (tag_num - 1);

  //initialize hit to 0
  hit = 0;

  uint32_t *address;
  FILE* fp = fopen(argv[1], "rb");
  while(fread(address,4,1,fp)) {
    //printf("%x\n",*address);

    struct element entry;
    entry.tag = ((*address) >> (blockSize_exp+lines_exp)) & tag_mask;
    entry.line = ((*address) >> blockSize_exp) & lines_mask;
    entry.valid = 1;

    hit += place(entry);

  }
  fclose(fp);
  printf("Hello World\n" );

  float hitRatio = (float)hit/(1<<26);
  printResults(hitRatio, argv[1]);

  return 0;
}
