QBcom
--

What is QBcom ?
----
Let's suggest we have a retro pc A , which has limited MSDOS installed, but without interlnk.exe or intersvr.exe.
but it has QBasic.com installed.
假设有一台机器，上面有少量的dos文件，但是没有串口传输用的interlnk/intersvr，不过有qbasic.com这个文件。
虽然它有软驱，可是我们手头没有软盘。
虽然它有光驱，可是我们没有dos下的光驱驱动，比如oakcdrom.sys。
虽然它有硬盘，可是我们没有USB-IDE转换器来复制文件。

How can we transfer a intersvr.exe to it, from another pc B, with QBasic ? 
如何利用现有条件把intersvr.exe给传进去呢？
----
Let's type a limited version of [COM1 file reciever](recv2.bas) by keyboard.
run it to get the file through COM1 with a serial link cable.

on the other computer , run  [COM1 file sender](send2.bas) to send the intersvr.exe.

after that ,you can run intersvr.exe on A, and run interlnk.exe on the B, and copy all the rest files you need.


Pin Connections for a Serial Cable [source](http://www.manmrk.net/tutorials/DOS/help/interlnk.htm)
----
This section describes the wiring specifications for serial Interlnk
cables.

Make a serial cable with either a 9-pin or a 25-pin female connector on both
ends. Three wires are required for data transmission: Ground-Ground,
Transmit-Receive, and Receive- Transmit. Seven wires are required if you
want to use the remote copy feature. Wire the cable as follows:
```
9 pin           25 pin              25 pin          9 pin
=====           ======              ======          =====
pin 5           pin 7   <------>    pin 7           pin 5
(Ground-Ground)
pin 3           pin 2   <------>    pin 3           pin 2
(Transmit-Receive)
pin 7           pin 4   <------>    pin 5           pin 8
(RTS - CTS)
pin 6           pin 6   <------>    pin 20          pin 4
(DSR - DTR)
pin 2           pin 3   <------>    pin 2           pin 3
(Receive-Transmit)
pin 8           pin 5   <------>    pin 4           pin 7
(CTS - RTS)
pin 4           pin 20  <------>    pin 6           pin 6
(DTR - DSR)
```
