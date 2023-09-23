#!/bin/bash
apt-get update
for PKG in mame dosbox prboom-plus doom-wad-shareware trigger-rally fceux
do
        apt-get -y install $PKG

done
