PSX controllers on a PC (parallel port)

[Source](https://www.raphnet.net/electronique/psx_adaptor/psx_adaptor_en.php)

The idea
Schematic
Hooking a second controller
Build
Software
Help
Disclaimer
The idea
The Playstation controllers are very well designed, are comfortable and they work very well. That's why it's interesting to use a real playstation controller on a PC (intead of using a cheap imitation). There are many adapters on the market to do this. However, if you like electronic or want to save a little money, it is possible to build one yourself.

I have done this for the first time when I bought the PC version of Final Fantasy 7. I wanted to play the game with the original controller.


*I do not* have any schematics or information on how to build a usb version of this adapter. Dont send me mail asking for this, I wont answer.


Schematic
The Direct Pad Pro project provides a schematic to connect the controller to the PC Parallel port. Here is a copy of it:
schema de l'adaptateur
Comments and more details about the schematic:
![image](https://github.com/zhblue/RetroFuns/assets/3926566/b5490ac3-c60d-4c84-976e-759944a60dd5)

The diodes used are the common 1n4148 or 1n914. It is possible that 1n400x diodes would also work(and many other types), but I have not tried. Also, if you have a dual shock controller and want to use it, you will need to provide an external 9 volt power source.


Hooking a second controller
Here are instructions to use two controllers on one port. (Copy-Paste from DirectPadPro readme.txt file):

To hook up the second controller duplicate all connections except DB25-10 and DB25-12. For pad 2, replace the DB25-10 connection with a connection to DB25-13, and the DB25-12 with DB25-15. Note that the parallel port may not be able to supply enough power to run a second controller, and you may only be able to run one at a time without using an external power supply.


Build
Here are pictures of an adapter I built. For detailed instructions, you can use the Snes to parallel port adapter instructions as a base.





Warning: Do NOT rely on the wire colors shown in the above pictures. The relationship between pin numbers and wire color varies according to the cable manufacturer, and sometimes even between batches. You must find out the color code used by your cables using a continuity tester. Blindly following the colors seen here may (although very unlikely) damage your parallel port or controller.

If you are looking for a ready-made adapter, you can buy one from my online store.


Software
Windows 95/98
For Direct X games, you will need Direct Pad Pro. You can download it here: dpadpr50.zip. This is the file I downloaded from www.ziplabel.com when Direct Pad Pro was still available on this site.

Windows NT/2000/XP
As far as I know, there are 2 drivers able to make this adapter work with Win2k and XP.
Psxpad. http://www.psxpad.com/index_e.php
NTpad. http://www.ntpad.com.ar/

Please not that since I dont use WinNT/2000 or XP, I have not been able to test any of these drivers.
Linux
The Linux kernel supports this adapter without any supplemental patch. If you know how to use Linux, I think you should be able to discover how to make this adapter work yourself. However, I will give more information(I'm not the type to just say RTFM).

If the gamecon kernel module is already compiled and available, simple type this:
# modprobe gamecon gc=0,7,0,0,0,0
If you have a rescent kernel, try this instead:
# modprobe gamecon map=0,7,0,0,0,0
If the module does not exist, you will have to compile it yourself. When you configure your kernel, select the following options:
say Y at Input Core Support > Joystick support
say M at Character Devices > Joysticks > Multisystem, NES, SNES, N64, PSX joysticks and gamepags
Next, compile and install your new kernel and modules. You should now be able to modprobe gamecon correctly.
One detail: The documentation says you must plug the controller *before* loading the module, because the controller is detected at load time.
The file Documentation/input/joystick-parport.txt that comes with the kernel source should be useful you if you need more help.

Others
If you wish to write your own software or driver for a particular platform, here is a file containing a lot of the information you will need.
Playstation.txt

The is also a C library that allows one to use memory cards and controllers with this interface(or others). This library is open source, so you should be able to port it to another platform quite easily. Here is the site where you will find it:
PSX Peripheral Bus Library


Help
Sometimes, even if built correctly, this adapter may not work. The cause of this varies.

A common problem is that the parallel port is not able to give enough power to the controller. That's because the pc parallel port has not been designed to give power to peripherals connected to it. This adapter uses a trick to do so: 5 bits are set to a logic 1 level(5 volts) by the driver, and they are combined with the diodes to give power to the controler. If the controller consumes too much current, the voltage decrease and become too low. If this happens, you must find another source for the 5 volt. Using the game port pins 1 and 4 (+5volt and GND) works well. Of course, there are many other places were you can obtain 5 volts inside a computer...


If you have a laptop(or a modern computer(2004)), the parallel port maybe using 3.3 volts instead of 5 volts. In this case, you will need to power the controller from another source of 5 volts, and maybe you will need to convert logic levels with additional circuitry.

Also, if you use a cheap clone of the PSX controllers, it is possible that it is simply not supported, but it has not occured to me nor to anybody I know.


Disclaimer
I cannot be held responsible for any damages that could occur to you or your equipment while following the procedures present on this page. Also, I GIVE ABSOLUTELY NO WARRANTY on the correctness and usability of the informations on this page. Please note, however, that the procedures above have worked in my case without any damages or problems.

Now you cannot say that I did not warn you :)
