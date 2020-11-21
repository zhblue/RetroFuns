Tips on raspberry pi
----


raspberry pi make chroot for x86
--
```
 apt-get update
 apt-get upgrade
 apt-get update &&  apt-get install qemu qemu-user qemu-user-static binfmt-support debootstrap binutils
 mkdir /x86/
 debootstrap --foreign --arch x86_64 buster x86/ http://mirrors.aliyun.com/debian/ 
 mount -t sysfs sys /x86/sys/
 mount -t proc proc /x86/proc/
 mount --bind /dev /x86/dev/
 mount --bind /dev/pts /x86/dev/pts/
 mount --bind /dev/shm /x86/dev/shm/
 cp /usr/bin/qemu-x86_64-static /x86/usr/bin/
cp /etc/passwd x86/etc
cp /etc/hosts x86/etc
cp /etc/resolv.conf x86/etc
cp /etc/locale.gen x86/etc
 chroot /x86/ /debootstrap/debootstrap --second-stage
 chroot /x86/ /bin/su -l root
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:0" >> .bashrc
source ~/.bashrc
apt update
adduser -uid 1000 pi
apt install leafpad
exit
 chroot /x86/ /bin/su -l pi
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:01" >> .bashrc
source ~/.bashrc
exit
 chroot /x86/ /bin/su -l root
apt-get update
apt-get install locales
locale-gen
apt-get install apt-utils
apt install wine
exit
 chroot /x86/ /bin/su -l pi
winecfg


```
