CC = gcc

fft.png : blue_fft.txt gnu.plt
	gnuplot gnu.plt

blue_fft.txt : fft blue.raw
	./fft blue.raw $@

fft : fft.c
	$(CC) $^ -o $@ -lm -lfftw3

blue.raw : blue_filter impulse.raw
	./blue_filter impulse.raw $@

blue_filter : blue_filter.c
	$(CC) iir.c butterworth.c $^ -o $@ -lm

impulse.raw : make_impulse
	./$^ $@

make_impulse : make_impulse.c
	$(CC) $^ -o $@

clean :
	$(RM) fft.png
	$(RM) blue_fft.txt
	$(RM) fft
	$(RM) blue.raw
	$(RM) blue_filter
	$(RM) impulse.raw
	$(RM) make_impulse
