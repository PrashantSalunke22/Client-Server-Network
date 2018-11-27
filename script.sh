rfkill unblock wifi
sudo ifconfig wlp3s0 down
sudo iwconfig wlp3s0 mode ad-hoc
sudo iwconfig wlp3s0 channel 1 essid NW mode ad-hoc
sudo ifconfig wlp3s0 up
sudo ifconfig wlp3s0 192.168.1.140 netmask 255.255.255.0
