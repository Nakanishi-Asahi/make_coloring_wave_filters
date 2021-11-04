set term png size 960, 720
set logscale x
set mytics 5
set grid mxtics mytics
set grid xtics ytics
set output "fft.png"
plot [5 : 2000] [-20 : 5] "blue_fft.txt" w lp, "f_db_blue.txt" w lp, "f_db_orange.txt" w lp, "f_db_white.txt" w lp
