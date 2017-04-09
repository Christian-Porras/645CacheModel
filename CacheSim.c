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
int cacheAssociativity_exp;
int cacheAssociativity_num;

//declare line variables. These will be defined within main
int lines_exp;
int lines_num;
int lines_mask;

//declare tag variables. These will be defined within main
int tag_exp;
int tag_num;
int tag_mask;

//struct for an element
//elements are the addresses stored in the cache from the address trace
struct element{
  int tag;
  int line;
  int valid;
};

//declare cache array
struct element ** cache;

int main(int argc, char ** argv){

  if(argv[1] == NULL){
    printf("Please input a value 0-3 for the exponent of the cache associativity.\n" );
    return 0;
  }
  else if(atoi(argv[1])>3 || atoi(argv[1])<0){
      printf("Invalid size for cache associativity. Please enter 0-3. \n");
      return 0;
  }

  //use the second argument to set the size of the associativity of the cache
  //assume valid input of 0-3 for sizes of 1, 2, 4, or 8
  cacheAssociativity_exp = atoi(argv[1]);
  cacheAssociativity_num = (1 << cacheAssociativity_exp);

  //determine the line size based on the associativity, block size and cache size
  lines_exp = ((cacheSize_exp) - (cacheAssociativity_exp + blockSize_exp));
  lines_num = (1 << lines_exp);
  lines_mask = (lines_num - 1);

  //determine the tag size
  tag_exp = (address_size - blockSize_exp - lines_exp);
  tag_num = (1 << tag_exp);
  tag_mask = (tag_num - 1);

  //initialize cache
  cache[lines_num][cacheAssociativity_num];

  uint32_t *address;
  FILE* fp = fopen(argv[2], "rb");
  while(fread(address,4,1,fp)) {
    struct element entry;
    entry.tag = ((*address) >> (blockSize_exp+lines_exp)) & tag_mask;
    entry.line = ((*address) >> blockSize_exp) & lines_mask;
    entry.valid = 1;

    printf("%x: %x, %x\n",*address, entry.tag, entry.line);
  }
  fclose(fp);
  printf("Hello World\n" );

  return 0;
}


void printResults(){
//  printf("Name of File read: %s\n", fileName);
//  printf("Hit Ratio: %d\n", hitRatio);
  return;
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
      //check to see if all blocks have been checked
      else if(i == cacheAssociativity_num-1){
        bump(entry);
        break;
      }
    }
    //place the element in the invalid space
    else{
      cache[entry.line][i] = entry;
      break;
    }
  }
  return 0;
}

//replace element in the cache with current element passed through as an argument
//currently set up for random replacement
void bump(struct element entry){
  int i = rand() % cacheAssociativity_num;
  cache[entry.line][i] = entry;
}
