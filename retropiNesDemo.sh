#!/bin/bash
export PATH=$PATH:/opt/retropie/emulators/retroarch/bin/
EMU=retroarch
PARAM="  -L /opt/retropie/libretrocores/lr-quicknes/quicknes_libretro.so --config /opt/retropie/configs/nes/retroarch.cfg  "
while true
do
        for GAME in *.nes
        do
                ${EMU} ${PARAM} "${GAME}" &
                sleep 3s;
                if ps -C ${EMU};then sleep 120s;fi
                pkill -9 ${EMU}
        done
done
