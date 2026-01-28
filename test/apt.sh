sudo apt install xorg libx11-dev libxft-dev libxrender-dev libxinerama-dev libxrandr-dev xorg-apps -y
make
cp .xinitrc ~
startx
