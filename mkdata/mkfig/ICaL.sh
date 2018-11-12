#!/bin/sh
# PL-gnu.sh

cat ./ical.out | awk '{print ($1-16000)/1000,$2}' > cal5.dat
cat ./ical.out | awk '{print ($1-18000)/1000,$2}' > cal4.dat
cat ./ical.out | awk '{print ($1-20000)/1000,$2}' > cal3.dat
cat ./ical.out | awk '{print ($1-28000)/1000,$2}' > cal1.dat
cat ./ical.out | awk '{print ($1-32000)/1000,$2}' > cal2.dat

gnuplot << EOM
#set term postscript eps color "Arial" 25
set term postscript eps enhanced "Arial" 25 color
set output "ICaL_with.eps"

set key right top

set lmargin 10
set bmargin 5
set rmargin 10
set tmargin 5

#set size square

#set title "APs"

set style data lines
set style line 1 lt 2 linecolor 1 lw 2
set style line 2 lt 2 linecolor 2 lw 2
set style line 3 lt 2 linecolor 3 lw 2
set style line 4 lt 2 linecolor 5 lw 2
set style line 5 lt 2 linecolor 4 lw 2
set style line 6 lt 2 linecolor 1 lw 2
set style line 7 lt 2 linecolor 3 lw 2
set style line 8 lt 7 lw 3
set style line 9 pt 8 ps 3

set xrange [-0.1:1.7]
#set yrange [-1.05:0.05]
set yrange [-0.6:0.02]
set tics out scale 2.5
set xtics 0,1
set mxtics 1
set ytics -0.6,0.2
#set mytics 2

set border 3
set xtics nomirror
set ytics nomirror

#set size 1.2,1.0 
set size 1.0,1.0 
set origin 0.0,0.0
set xzeroaxis

set xlabel "Time (s)"
set ylabel "ICaL (mA/mF)"

plot \
	"cal5.dat" using 1:2 title "" linestyle 5,\
	"cal4.dat" using 1:2 title "" linestyle 4,\
	"cal3.dat" using 1:2 title "" linestyle 3,\
	"cal1.dat" using 1:2 title "" linestyle 1,\
	"cal2.dat" using 1:2 title "" linestyle 2

quit
EOM
#test -f PL.$$ && rm PL.$$ 
if test "$DISPLAY" != ""
then i=`ps -U $USER | grep gv | egrep -v grep | awk '{print $1}' -`
 if test "$i" != ""
 then kill -1 $i
 else gv -scale=1 ICaL_with.eps &
 fi
fi
