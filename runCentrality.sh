#!/bin/bash

set -x

    InputType=(Hydjet502MC)
	InputHiForest=("/mnt/hadoop/cms/store/user/luck/L1Emulator/HydjetMB_502TeV_740pre8_MCHI2_74_V3_HiForestAndEmulator_v5.root")
	g++ centralityCalibration.C $(root-config --cflags --libs) -Werror -Wall -Wextra -O2 -o centralityCalibration.exe || exit 1
	g++ plotCentrality.C $(root-config --cflags --libs) -Werror -Wall -Wextra -O2 -o plotCentrality.exe || exit 1


	for cases in 0
	do
	    OutputFile="${InputType[cases]}_CentralityCalibration.root"
	  ./centralityCalibration.exe "${InputHiForest[cases]}" "$OutputFile" || exit 1
	  ./plotCentrality.exe "${InputType[cases]}"|| exit 1
	done
