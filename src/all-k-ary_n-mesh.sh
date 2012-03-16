#!/bin/sh

#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Uniform -r 0..319
#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c BitReversal -r 0..319
#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c BitComplement -r 0..319
#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Transpose -r 0..319
#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Tornado -r 0..319
#opp_runall   -j8 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Neighbour -r 0..319

opp_runall   -j10 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c BitReversal -r 0..9
opp_runall   -j10 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c BitComplement -r 0..9
opp_runall   -j10 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Transpose -r 0..9
opp_runall   -j10 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Tornado -r 0..9
opp_runall   -j10 n_radix_switch.exe -u Cmdenv -f k-ary_n-mesh.ini -c Neighbour -r 0..9
