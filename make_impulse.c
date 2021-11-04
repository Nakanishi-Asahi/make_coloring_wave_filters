#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("Usage : ./make_impulse impulse.raw\n");
    exit(-1);
  }
  FILE *f1;
  if((f1 = fopen(argv[1], "wb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }
  double fs = 44100.0;
  int len = fs * 1;
  for(int i = 0; i < len; i++){
    double value;
    if(i == 0){
      value = 1.0;
    }
    else{
      value = 0.0;
    }
    fwrite(&value, sizeof(double), 1, f1);
  }
  return 0;
}
