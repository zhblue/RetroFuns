#!/bin/bash
# Run this script within a directory full of .nes files on Retropie, it will looply demo them for each 120 seconds.
# 本脚本用于在Retropie循环演示运行全目录的.nes文件, 默认每个文件演示120秒。

export PATH=$PATH:/opt/retropie/emulators/retroarch/bin/
EMU=retroarch
PARAM="  -L /opt/retropie/libretrocores/lr-quicknes/quicknes_libretro.so --config /opt/retropie/configs/nes/retroarch.cfg  "
###---clockwork GameShell using next line
#PARAM="  -L /home/cpi/apps/emulators/nestopia_libretro.so "

while true
do
        for GAME in *.nes
        do
                ${EMU} ${PARAM} "${GAME}" &
                sleep 3s;
                if ps -C ${EMU};then sleep 120s ;fi      
                pkill -9 ${EMU}
        done
done
