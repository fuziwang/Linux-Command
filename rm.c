#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include "rm.h"

int main(int argc , char * argv[]) { 
  int rt;
  if(argc != 2){
    exit(2);
  }else{ 
    if((rt = unlink(argv[1])) !=  0){
        fprintf(stderr,"error.");
        exit(3);
    }
  }
  return 0;
}
