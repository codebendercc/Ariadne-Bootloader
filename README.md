# [Ariadne Bootloader for Arduino][1]
[1]: http://codebendercc.github.com/Ariadne-Bootloader/

[![PayPayl donate button](http://img.shields.io/paypal/donate.png?color=yellow)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6RBAQPJ77X9BG "Donate once-off to Ariadne bootloader developer using Paypal")

## Bootloader for Arduino with Ethernet
This is a beta stage bootloader for Arduino Ethernet board and the regular Arduino with Ethernet Shield.
It is based on previous unfinished work by the Arduino developers. The bootloader implements a TFTP
server on the Arduino board and flashing works using any regular TFTP client.


## The Files and Folders in this Repository
The structure of this repository is made to follow the standarts of the Arduino IDE. This way you can
simply copy the folders in your sketchbook and be ready

* hardware: This is where the bootloader resides.
* java-client: Demo client for the bootloader. Inherited by the initial project. Untested and probably non-functional
* libraries: Helper libraries to support functions of the bootloader
* utilities: Various stuff used for development and debugging


## Downloading and Installing Files
First of all, you need to clone or download the repository. To clone the repository you need to have
git installed, then you can run `git clone https://github.com/codebendercc/Ariadne-Bootloader.git` in a
directory. This way you can later update your local repository by running `git pull` inside the
__Ariadne-Bootloader__ directory.

In case you want to avoid this hassle, you can use the __ZIP__ button at the top of the page to download
the latest snapshot of the repository in a zip archive and extract it.

After that you have to copy the __hardware__ and __libraries__ folders inside your sketchbook folder.
Take extra care during coping not to overwrite any other files. Restart the Arduino IDE to load the new
boards and libraries.


## Installing the Bootloader
To burn the bootloader, you will need an ISP(in-system programmer) like [AVR-ISP][2], [USBtinyISP][3]
or you can build a [ParallelProgrammer][4] or an [ArduinoISP][5]. The first three programmers should
be connected to the ICSP pins (the 2 by 3 pin header) and make sure you plug it in the right way. The
board must be powered by an external power supply or the USB port. In the case of _ArduinoISP_ you
should consult the above link for further instructions on how to build and use.
[2]: http://www.atmel.com/dyn/products/tools_card.asp?tool_id=2726
[3]: http://www.ladyada.net/make/usbtinyisp/
[4]: http://arduino.cc/en/Hacking/ParallelProgrammer
[5]: http://arduino.cc/en/Tutorial/ArduinoISP

After you have connected the Arduino board and the programmer to your computer launch the Arduino IDE.
Navigate to the __Tools__ > __Board__ menu and select `Arduino Duemilanove/Uno(ATmega328) w/ Ariadne Bootloader`
if you have an Arduino Duemilanove or Uno with an Ethernet Shield or `Arduino Ethernet w/ Ariadne Bootloader`
for Arduino Ethernet. Then go to __Tools__ > __Programmer__ and select the programmer you are using.
In case you are using _ArduinoISP_, make sure that the selected port in the __Tools__ > __Serial Port__
menu refers to the _ArduinoISP_ and not the board that you want to burn the bootloader on. Now, just
launch the __Tools__ > __Burn Bootloader__ command and wait for about 15 seconds for the operation
to complete.

In the case of _Arduino Mega_ the previous ISPs do not reliably work because of design differences. To
install the bootloader in these boards you will need one of the more expensive models,
like [Atmel's AVRISP mkII][6], [Olimex's AVR-ISP-MK2][7] or another similar programmer. If you don't
have any compatible programmer but more than one Arduinos available, you can use Nick Gammon's
excellent [guide][8] on how to use one to program the other. This method has been reported to work
for flashing __Ariadne__ on _Arduino Mega_.
[6]: http://www.atmel.com/tools/AVRISPMKII.aspx
[7]: https://www.olimex.com/Products/AVR/Programmers/AVR-ISP-MK2/
[8]: http://www.gammon.com.au/forum/?id=11635


## Serial Flashing
Ariadne bootloader supports flashing through serial like any other regular bootloader. This way of uploading
is built upon the default bootloaders so it should be pretty straight forward to use. Just plug in the
USB cable and select the serial port and the appropriate board from the __Tools__ > __Board__ menu. After
that you must press the reset button and the indication LED on __pin 13__ or __pin 9__, in case of Arduino
Ethernet, will start blinking rapidly. This means that the bootloader is running and the Arduino is ready
to be programmed. If there is a __valid__ program already flashed on the Arduino, you have to reprogram
the device in the next __5 seconds__. If you don't, the bootloader will initiate the program that is
already in the Arduino. In case there is no program flashed or the program has been marked as __invalid__,
the bootloader will never time out and you can reprogram it at any time.

After a succesful flashing,

* _Arduino Duemilanove_ will automatically start the user's application.
* _Arduino Uno_ will do a reset cycle and start the program after the bootloader times out.
* _Arduino Mega_ will behave in a similar way as _Arduino Uno_

This happens because _Uno_ has the autoreset feature that resets the board after a serial connection.

Due to the fact that "autoreset" for remote tftp programming is implemented using a watchdog timer timeout,
the bootloader will do a full cycle after every reset, physical or software. For those who miss the _Adaboot
No-Wait Mod_-like functionality, we have been testing some options on how to circumvent these limitations,
but they still need refinement.


## Default Network Settings
The default built-in network settings of the bootloader are listed below.

`
* IP Address:  192.168.1.128
* Subnet Mask: 255.255.255.0
* Gateway:     192.168.1.1
* MAC Address: 0xDE.0xAD.0xBE.0xEF.0xFE.0xED

* TFTP Negotiation Port: 69
* TFTP Data Port: 46969
`

___NOTE:___ The Arduino Ethernet that were sent as Indiegogo Perks were flashed with different network
settings. Their bootloader still defaults to the previous settings __but__ the current values are on
the accompaning leaflet.


## Configuring Network Settings
These can be changed using our __NetEEPROM__ library. The library is going to have it's own documentation
on how it can be used but for the purpose of changing and reading the network settings you can use the
included examples. To load them navigate to __File__ > __Examples__ > __NetEEPROM__ and select one of
the examples. You can write the network settings using the __WriteNetworkSettings__ sketch or print them
to the serial using the __ReadNetworkSettings__.

Note that the settings array in the __WriteNetworkSettings__ sketch hasn't got the settings in the usual
order but rather in the order that __Wiznet chips__ read them, so make sure you have put the correct values.
If you set the network settings you also have to set the TFTP data transfer port. The default is good
enough but you may need to change it for the reasons that are listed below in the
[Configuring your Router for Remote Flashing][9] section. There is also documentation on how use
these sketches in the form of comments so be sure to read them.
[9]: https://github.com/codebendercc/Ariadne-Bootloader#configuring-your-router-for-remote-flashing

## TFTP Flashing
Now for the real reason we made this bootloader and why you should use it. First of all you can watch
__Ariadne__ in action in this how-to video for remote flashing using TFTP [here][10]. In the video you
may notice that the board is being reset by hand. In the next couple of weeks we are going to release
the library that will allow remote resetting through a simple web server with some security measures.
More on that as the library progresses.
[10]: http://youtu.be/KCHqhV6xPMg

### Converting your sketch to the right format
Unlike serial flashing that uses __HEX__ files to flash the Arduino, the TFTP server implemented in the
bootloader works with binary files. This means that you have to manually convert your programs to the
right format. To do that, first build your sketch inside _Arduino IDE_ using the __Verify__ button. After
that, without exiting the _Arduino IDE_ you need to navigate to the temporary directory where your project
was built. On all platforms, you can find out the temporary build folder by checking
`Show verbose output during compilation` in _Arduino IDE_'s preferences dialog and the path for the
compiled `.hex` file will be printed in the last line of the compilation output.

#### Windows
On Windows, the temporary directory can be

```
C:\Documents and Settings\Administrator\Local Settings\Temp\build5571819468326525374.tmp\Blink.cpp.hex
```

```
"C:\Program Files\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -I ihex
"C:\Documents and Settings\Administrator\Local Settings\Temp\build5571819468326525374.tmp\Blink.cpp.hex"
-O binary Blink.cpp.bin
```
#### Linux

#### OS X
That is `C:\Users\owner\AppData\Local\Temp\` on *Windows*, `/tmp` on *Linux*. On *MacOS* you'll need
to go to Arduino's preferences, and check the "Show verbose output during compilation" checkbox. After
that, when you compile, you will see the path for the compiled .hex file in the last line of the compilation
output.. There you will find a folder named something like `build2429295348207572157.tmp`. That is where
the Arduino temporary build files reside. Enter the directory and make sure that there is a `.elf` or
a `.hex` file with the same name as your sketch. That is the file you need to convert. To achieve that
you have to run one of the following commands in a terminal.

* `avr-objcopy -I ihex [sketch].hex -O binary [sketch].bin`

In Windows and MacOS you can find the `avr-objcopy` program in your Arduino IDE installation folder under
`hardware/tools/avr/bin/`. Or,if you have scons installed, you can use the modified `SConstruct` script
you can find in `Ariadne-Bootloader/utilities`. This being based on the *arscons* script, it can be used
in two ways. If you used the previous process to generate the _HEX_ file you can just copy the `SConstruct`
file inside the temporary *Arduino IDE* build directory (as mentioned above) and run `scons` in a terminal
inside that directory.

The other way to use it is to copy the `SConstruct` script inside the sketch's directory and, as above,
run `scons` in a terminal inside that directory. This way you will build your project outside *Arduino
IDE* creating the `.bin` file in the process. Note that this way the sketch's folder will be polluted
with Arduino's build files, much like the temporary directory *Arduino IDE* uses.

For testing purposes you can find a __blink__ sketch in binary form inside the
`Ariadne-Bootloader/utilities/tests/blink` folder. The __fade__ sketch in the `tests/fade` folder
will also give you a view of what a failed upload looks like. This sketch fails because it is written
in plain __C__ and not in __Arduino__. That way it lacks some "signatures" the bootloader uses to
validate _Arduino_ sketches. The third sketch in `tests/led_display` is an easter egg for which you
need to find out how we had our led matrices connected on _Arduino Uno_. Or we might release the
schematics at some point. Who knows.

### Using a tftp client to upload the sketch
Now that the binary is ready, you have to upload it. First you have to connect to your Arduino using
any tftp client you may have on your computer. All three major operating systems have their own clients
that you can use through the command line.

#### Windows
```
Microsoft Windows XP [Version 5.1.2600]
(C) Copyright 1985-2001 Microsoft Corp.

C:\Documents and Settings\Administrator>tftp

Transfers files to and from a remote computer running the TFTP service.

TFTP [-i] host [GET | PUT] source [destination]

  -i              Specifies binary image transfer mode (also called
                  octet). In binary image mode the file is moved
                  literally, byte by byte. Use this mode when
                  transferring binary files.
  host            Specifies the local or remote host.
  GET             Transfers the file destination on the remote host to
                  the file source on the local host.
  PUT             Transfers the file source on the local host to
                  the file destination on the remote host.
  source          Specifies the file to transfer.
  destination     Specifies where to transfer the file.


C:\Documents and Settings\Administrator>tftp -i 192.168.1.128 PUT sketch.bin
tftp: can't read from local file 'sketch.bin'

C:\Documents and Settings\Administrator>tftp -i 192.168.1.128 PUT sketch.bin
```

#### Linux
On some __Linux__ distributions, like __Fedora/RedHat__, before you use `tftp`, you should load the `ip_conntrack_tftp`
module or the tftp client won't be able to acknowledge(__ACK__) the incoming packets. That is needed
because TFTP is insecure and it is not enabled by default. Other distributions like __Arch__, don't need
this step. To do that, open a terminal and run
```
modprobe ip_conntrack_tftp
```
as __root__ using `su` or `sudo`.

After that open a terminal as a regular user and type
```
tftp [ip] [port]
```

For the default bootloader settings that would be:
```
tftp 192.168.1.128 69
```
In this case it could just be `tftp 192.168.1.128` as __69__ is the default tftp port and the client
would automatically connect to it. For any other port you have to explicitly set it.

Now you should have been greeted by the
```
tftp>
```
prompt.

First you have to enter this command:
```
tftp> mode octet
```
This way you tell the __TFTP__ client to send binary data. This is absolutely needed as if your client
is in netascii mode, uploading will fail. After this, it is advised to use the two following commands
to make the process more informative so you can have a better view of what is happening, but they are
not needed.
```
tftp> trace
tftp> verbose
```
Now to actually upload the binary file all you have to do is __reset__ the board and in the next __5
seconds__ run the following command.
```
tftp> put [sketch].bin
```
The __5 second__ time frame is in case you already have a valid program uploaded on the Arduino. In case
you don't have a program loaded or it has been marked invalid, you don't have any time constraints.

Now you should see your tftp client sending packets and the indication LED on __pin 13__ or __pin 9__
blinking in a random way, almost like having a hiccup. A correct output sample of the TFTP client uploading
the *blink* sketch is below:
```
tftp> mode octet
tftp> trace
Trace mode on.
tftp> verbose
Verbose mode on.
tftp> put blink.bin
sent WRQ <file: blink.bin, mode: octet <>>
received ACK <block: 0>
sent DATA <block: 1, size: 512>
received ACK <block: 1>
sent DATA <block: 2, size: 512>
received ACK <block: 2>
sent DATA <block: 3, size: 512>
received ACK <block: 3>
sent DATA <block: 4, size: 512>
received ACK <block: 4>
sent DATA <block: 5, size: 42>
received ACK <block: 5>
tftp>
```
After a successful upload the bootloader will start the uploaded application instantly.

In case that for some reason the upload fails, first of all stop your TFTP client from sending any more
packets. After that you should wait for the upload process on the bootloader to timeout. That takes about
__5 seconds__ too. For this period you should witness the indication led doing some random blinking.
After the timeout and since there is no valid program in the memory, the TFTP server should restart itself
and wait for a new upload.


## Configuring your Router for Remote Flashing
If you are having trouble flashing your Arduino at home from the road, you probably need to enable [port
forwarding][11]. You need to forward ports __69__ and __46969__ to your Arduino in your router's configuration.
In case you have changed the incoming data port from __46969__ to another port i.e. __50232__, you have
to forward __50232__ port instead of __46969__. This is particularly useful when you have more than one
Arduinos, that you want to flash, behind your router. In addition to this you are going to have to translate
an external port of your choice on the router to the internal port and ip of the Arduino in the local
network.
[11]: http://en.wikipedia.org/wiki/Port_forwarding

An example is that you have 2 devices, one at *192.168.1.128* and one at *192.168.1.129*. They both listen
to port __69__ for the initial connection. In this case you can translate external port __6969__(any
random port will do) on your router to `192.168.1.128:`__69__ and external port __6970__ to
`192.168.1.129:`__69__ and specify these in the tftp client you are using.

Port Forward has [excellent guides][12] on how to enable port forwarding for a vast number of routers.
[12]: http://portforward.com/english/routers/port_forwarding/

## Codebender
One of the best and easiest ways to use this bootloader is along with [codebender.cc][13]. Just register,
enter your Arduino's IP (external IP for those in corporate or home networks behind NAT) and flash.
[13]: http://codebender.cc

## Helper Libraries
* [NewEEPROM][14] (Patched EEPROM library to protect the memory space used by the bootloader)
* [NetEEPROM][15] (Library to manipulate the network settings of the bootloader)
* [ResetServer][16] (Library used to create an HTTP server on the Arduino to enable remote resetting
of the microcontroller)
[14]: https://github.com/codebendercc/Ariadne-Bootloader/tree/master/libraries/NewEEPROM
[15]: https://github.com/codebendercc/Ariadne-Bootloader/tree/master/libraries/NetEEPROM
[16]: https://github.com/codebendercc/Ariadne-Bootloader/tree/master/libraries/EthernetReset

## Supported Boards
Supported MCUs:

* __ATmega328__
* __ATmega2560__
* __ATmega1284__

Supported ethernet controllers:

* __WizNet W5100__
* __WizNet W5200__
* __WizNet W5200__

Tested Arduino Boards:

* [Arduino Ethernet][17]
* [Arduino Uno][18]
* [Arduino Duemilanove w/ ATmega328][19]
* [Arduino Mega 2560][20]
[17]: www.arduino.cc/en/Main/ArduinoBoardEthernet
[18]: http://www.arduino.cc/en/Main/ArduinoBoardUno
[19]: http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove
[20]: http://arduino.cc/en/Main/arduinoBoardMega2560

## Other Tested Boards
These boards have been also tested and found to be working with Ariadne Bootloader. I don't have any
of these so a big ___thank you___ goes to the people that took their time to test them.

* [ITead Studio IBoard][21]
* [Sparkfun Ethernet Pro][22]
[21]: http://imall.iteadstudio.com/im120410001.html
[22]: https://www.sparkfun.com/products/10536

## Contributors

## Donators [![PayPayl donate button](http://img.shields.io/paypal/donate.png?color=yellow)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6RBAQPJ77X9BG "Donate once-off to Ariadne bootloader developer using Paypal")
[Hachi Manzur](hemanzur@gmail.com) (AVRISP mkII programmer, testing)

If you feel that you should be in this list, please contact me via email.

## Acknoledgements
__Ariadne__ bootloader is built upon some great open source projects.

* [TFTP-Bootloader][23] (The base of this project)
* [Optiboot][24] (Serial flashing for __ATmega328__)
* [Arduino-stk500v2-bootloader][25] (Serial flashing for __ATmega2560__)
[23]: https://github.com/arduino/TFTP-Bootloader
[24]: https://code.google.com/p/optiboot/
[25]: https://github.com/msproul/Arduino-stk500v2-bootloader

Credit should also go to [mharizanov](https://github.com/mharizanov) for commenting some of the initial
*Arduino* code, making it easy for me to start and [follower](https://github.com/follower) who's sketches
served as a starting point for the included __NetEEPROM__ and __EthernetReset__ libraries.


## License
This is free software and it is released under the [GPLv2, GNU General Public License][99]
[99]: https://www.gnu.org/licenses/gpl-2.0.html
