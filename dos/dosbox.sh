#!/bin/bash
mkdir dosbox
cd dosbox
wget https://vieju.net/pcdosmini/download/PCDosMini_v1.zip
unzip PCDosMini_v1.zip
apt-get install dosbox
cat >> ~/.dosbox/*.conf << EOF
mount c: ~/dosbox/PCDosMini/fs
c:
dir /w
EOF
