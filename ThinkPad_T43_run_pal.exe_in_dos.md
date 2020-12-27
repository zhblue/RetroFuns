在T43/T4x笔记本上运行仙剑奇侠传1，dos版，需要的小技巧
--
1、使用dos6.22的himem.sys，使得可用XMS限制到64M

2、用noems加载emm386.exe，为OPL2LPT的adlipt提供基础

3、加载ramdrive.sys /e 32000 消耗掉32m内存，避免pal.exe检测xms时报负数。

4、用ndos.com做shell，降低常规内存占用

config.sys
----

```
[menu]
menuitem=px3,Planet X3
menuitem=ems,DOS with EMS
menuitem=xms,DOS with XMS
menuitem=oldxms,DOS with limit XMS/EMS
menuitem=cdrom,DOS with EMS and CDROM
menuitem=xdrom,DOS with XMS and CDROM

menucolor=14,1
menudefault=oldxms,5
[common]

rem device=c:\windows\ramdrive.sys /e 10240
dos=high,umb
stackshigh=8,128
files=20
[ems]
device=c:\windows\himem.sys
device=c:\windows\emm386.exe I=C400-D800
[xms]
device=c:\windows\himem.sys

[oldxms]
device=c:\dos\himem.sys /testmem:off
devicehigh=c:\dos\emm386.exe
devicehigh=c:\windows\ramdrive.sys /e 32000 128
dos=high,umb
stacks=8,128
files=10
shell=c:\nu8\ndos.com
[px3]
device=c:\windows\himem.sys
[cdrom]
device=c:\windows\himem.sys
device=c:\windows\emm386.exe I=C400-D800
devicehigh=c:\tools\oakcdrom.sys /d:zhblue
[xdrom]
device=c:\windows\himem.sys
devicehigh=c:\tools\oakcdrom.sys /d:zhblue

```
autoexec.bat
----

```

path C:\WINDOWS;C:\WINDOWS\COMMAND;c:\tools;c:\dos
set BLASTER=A220 I7 D1 P330 T6
lh adlipt blaster
goto %config%
:px3

cd game\planetx3
rem temu /l1
px3
cd ..
goto end

:ndos
goto end

:xms
:oldxms
goto end

:ems
cd game\rad
play
goto end

:cdrom
lh mscdex /d:zhblue
goto end

:xdrom
lh mscdex /d:zhblue       

:oldxms

:end
       
       
SET PATH=%PATH%;C:\PROGRA~1\ATITEC~1\ATICON~1
mem


```
