# ledOS-vscode-PIO

run [ledOS](https://github.com/hpwit/ledOS.git) in vscode with the pio plugin using [I2SClocklessLedDriver](https://github.com/hpwit/I2SClocklessLedDriver) and [ASMParser](https://github.com/hpwit/ASMParser.git)

code by [hpwit](https://github.com/hpwit)

Clone this repo to your harddrive

Flash the code to esp32
- setup filesysystem: go to arduino ide and run Examples->SPIFFS->SPIFFS_test to initailize correctly the spiff.
- connect the esp32 with usb to your computer
- in vscode with pio press upload
- uplpad the example sc files (in the data folder) to the esp32: in vscode press the alien icon and then Build FileSystem Image and then Upload FileSystem image (do this any time you make changes to these files)

<img width="231" alt="image" src="https://github.com/user-attachments/assets/063ae119-2126-4ab5-94a7-12a06e832901">

Run LedOS (On Mac)
- Open a terminal
- type ```screen /dev/cu.usbserial-0001 115200``` (cu.usbserial-0001 the usb port you see in vscode)
- type help:

  ![image](https://github.com/user-attachments/assets/92063a4d-f6a7-48e9-b8f6-88f09642b373)

- type ```ls```
- load the file you want to run
- press ```ctrl-r``` to run it

  <img width="740" alt="image" src="https://github.com/user-attachments/assets/21ae73f7-f78d-4bf0-8a7f-ba06f4b84feb">

- press ```ctrl-e``` to edit it, press again ctrl-e and then type save
- run it again using ```ctrl-r```
- to exit ledOS press ```ctrl-a\```, then press y (to upload files you need to exit first)
- if for some reason vscode/pio cannot upload to esp32 check if no screen process running by ```ps -ef |grep screen``` and ```kill it by kill -9 pid```

