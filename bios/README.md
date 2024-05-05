BIOS interrupt tester
--
BIOS.exe can take a argument of input filename instead of default bios.txt

It will call the BIOS interrupt functions accoding the input file.

```book8088.txt for example
#put B : call 10h interrupt with function 02 to set cursor, and then call 10h with function 09 to put char 42h with color 02h
10 ah 02 bh 00 dh 0a dl 20
10 ah 09 bh 00 cx 01 al 42 bl 02
#put O
10 ah 02 bh 00 dh 0a dl 21
10 ah 09 bh 00 cx 01 al 4f bl 06
#put O
10 ah 02 bh 00 dh 0a dl 22
10 ah 09 bh 00 cx 01 al 4f bl 05
#put K
10 ah 02 bh 00 dh 0a dl 23
10 ah 09 bh 00 cx 01 al 4b bl 04
#put 8
10 ah 02 bh 00 dh 0a dl 24
10 ah 09 bh 00 cx 01 al 38 bl 03
#put 0
10 ah 02 bh 00 dh 0a dl 25
10 ah 09 bh 00 cx 01 al 30 bl 0a
#put 8
10 ah 02 bh 00 dh 0a dl 26
10 ah 09 bh 00 cx 01 al 38 bl 09
#put 8
10 ah 02 bh 00 dh 0a dl 27
10 ah 09 bh 00 cx 01 al 38 bl 0b
```
