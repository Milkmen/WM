sudo apt install xorg libx11-dev libxft-dev libxrender-dev libxinerama-dev libxrandr-dev x11-apps -y
make -C ..
cp .xinitrc ~
startx
