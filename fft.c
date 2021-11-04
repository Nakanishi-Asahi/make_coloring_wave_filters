#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

int main(int argc, char** argv){
  if(argc != 3){
    printf("Usage : ./fft input.raw fft.txt\n");
    exit(-1);
  }
  FILE *f1, *f2;
  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }
  if((f2 = fopen(argv[2], "w")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }
  double fs = 44100.0;
  int len = fs * 1;
  int fft_num = 16384;
  double invnum = 1.0 / (double)fft_num;
  double* nums = (double*)malloc(sizeof(double) * fft_num);
  int count = 0;
  for(int i = 0; i < len; i++){
    double value;
    fread(&value, sizeof(double), 1, f1);
    nums[count] = value;
    count++;
    if(fft_num <= count){
      fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fft_num);
      fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fft_num);
      for(int j = 0; j < fft_num; j++){
        in[j][0] = nums[j];
        in[j][1] = 0.0;
      }
      fftw_plan fwd = fftw_plan_dft_1d(fft_num, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
      fftw_execute(fwd);
      fftw_destroy_plan(fwd);
      for(int j = 0; j < fft_num; j++){
        double re = out[j][0];
        double im = out[j][1];
        /*
        if(j != 0 || j != fft_num / 2){
          re *= invnum * 2;
          im *= invnum * 2;
        }
        */
        double freq = fs / fft_num * j;
        double amp2 = re * re + im * im;
        double db = 10.0 * log10(amp2);
        fprintf(f2, "%f %f\n", freq, db);
      }
      free(in);
      free(out);
      count = 0;
    }
  }
  fclose(f1);
  fclose(f2);
  return 0;
}
