/*-------------------------------------------------------------
* Project 1: Cache Simulation
* Authors: Chris Porras, Brad Gibbons, Evan Bissell
* Version: V 1.0
* Date: April 13th, 2017
* Description: Simulates a cache by reading in addresses from a file and placing them
* in an array
*/--------------------------------------------------------------

int main(char[][] args){

  return 0;
}

boolean place(struct element){
  for(int i = 0; i < associativity; i++){
    if(cache[element.linenum][i].valid){
      if(element.tag == cache[element.linenum][i].tag){
        return 1;
      }
      else if(i == associativity-1){
        bump(element);
        break;
      }
    }
    else{
      cache[element.linenum][i] = element;
      break;
    }
    else if (i == associativity-1){
      bump(element);
    }
  }
  return 0; 
}
