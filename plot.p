set terminal wxt
set view equal xyz
set datafile separator ","
set style line 1 \
linecolor rgb '#007fff' \
linetype 1 linewidth 1 \
pointtype 7 pointsize 1

set key off
splot 'positions.csv' using 1:2:3 with points linestyle 1

