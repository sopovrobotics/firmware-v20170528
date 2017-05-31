# firmware-v20170528 (ForKeva)

Simple robot based on OrangePi Zero


## Installation system:

Used Ubuntu Server from here: https://www.armbian.com/orange-pi-zero/

Login/password: root/1234
Login/password: sopovrobotics/SopovRobotics


### Write img to sdcard by MacOS

	$ diskutil list
	$ diskutil unmountDisk /dev/diskN
	$ sudo dd if=dietpi.img of=/dev/distN bs=1m
	$ diskutil eject /dev/diskN

## Find devices in the local network (connected cable or connected by wifi)

$ nmap -sn 192.168.1.1/24

## Hardware

1. Motor-reducer Gekko MR12-100 (2 pieces)
2. Track Pololu 30T
3. Pololu 5v Step-Up/Step-Down Voltage Regulator S7V7F5
4. DRV8833 Dual Motor Driver Carrier
5. OprangePi Zero
6. Case for accumulator 18650
7. Accumulator 18650
8. Switcher

### Schema

![pic](https://raw.githubusercontent.com/sopovrobotics/firmware-v20170528/master/images/schema_v20170528.png)

## Building firmware

### Clone repository with firmaware


	# apt install git-core
	# cd ~
	# git clone https://github.com/sopovrobotics/firmware-v20170528.git firmware-v20170528

### Install dependencies
 
	# apt install g++ make qtchooser qt5-default libqt5script5 qtscript5-dev libqt5websockets5 libqt5websockets5-dev
	# cd ~/firmware-v20170528
	# qmake && make
	# ln -s `pwd`/etc/sopovrobotics /etc/sopovrobotics
	# ln -s `pwd`/etc/init.d/sopovrobotics /etc/init.d/sopovrobotics
	# ln -s `pwd`/sopovrobotics /usr/bin/sopovrobotics
	# update-rc.d -f sopovrobotics remove
	# update-rc.d sopovrobotics defaults
	# nano /etc/sopovrobotics/conf.ini
