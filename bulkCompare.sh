#!/bin/bash

typeset -A numstates
relPath="../../temporalPaths-lincombo"
relPathOurs="../../temporalPaths-lincombo"
relPathHiml="../../himmelBentertTempGraph/implementation"
#numstates[dtst1bc]=100
#numstates[dtstdef]=200
#for dtst in dtst1bc dtstdef
#do
#	echo ${numstates["$dtst"]}
#done

numstates[ca-cit-H_wu-fmst1-hp2-wt1]=28093
numstates[elec_wu-fmst1-hp2-wt1]=7118
numstates[epin_wu-fmst1-hp2-wt1]=131828
numstates[e_wu-fmst1-hp2-wt1]=87273
numstates[facebook-wosn-l_wu-fmst1-hp2-wt1]=63731
numstates[munmun_digg_r_wu-fmst1-hp2-wt1]=30398
numstates[slashdot-thr_wu-fmst1-hp2-wt1]=51083
numstates[wikiconf_wu-fmst1-hp2-wt1]=116836
numstates[wikipedia-gr_wu-fmst1-hp2-wt1]=1870709
numstates[youtube-u-gr_wu-fmst1-hp2-wt1]=3223585


for name in ca-cit-H_wu-fmst1-hp2-wt1 elec_wu-fmst1-hp2-wt1 epin_wu-fmst1-hp2-wt1 e_wu-fmst1-hp2-wt1 facebook-wosn-l_wu-fmst1-hp2-wt1 munmun_digg_r_wu-fmst1-hp2-wt1 slashdot-thr_wu-fmst1-hp2-wt1 wikiconf_wu-fmst1-hp2-wt1 wikipedia-gr_wu-fmst1-hp2-wt1 youtube-u-gr_wu-fmst1-hp2-wt1
do
	for resfile in "${relPath}/${name}/results_"*
	do
		echo "$name"
		echo $(basename "$resfile") ${numstates["$name"]}
		#echo "${relPathOurs}"/"${name}"/"$(basename "$resfile")"
		#echo "${relPathHiml}"/"${name}"/"$(basename "$resfile")"
		./compareResults ${numstates["$name"]} "${relPathOurs}"/"${name}"/"$(basename "$resfile")" "${relPathHiml}"/"${name}"/"$(basename "$resfile")" 
	done
done


