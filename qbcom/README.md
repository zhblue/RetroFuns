QBcom
--
What is QBcom ?
----
Let's suggest we have a retro pc A , which has limited MSDOS installed, but without interlnk.exe or intersvr.exe.
but it has QBasic.com installed.

How can we transfer a intersvr.exe to it, from another pc B, with QBasic ?
----
Let's type a limited version of [COM1 file reciever](recv2.bas) by keyboard.
run it to get the file through COM1 with a serial link cable.

on the other computer , run  [COM1 file sender](send2.bas) to send the intersvr.exe.

after that ,you can run intersvr.exe on A, and run interlnk.exe on the B, and copy all the rest files you need.
