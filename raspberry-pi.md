Tips on raspberry pi
----


raspberry pi make chroot for x86
--
```
apt-get install qemu qemu-user-static binfmt-support
mkdir x86
debootstrap --arch=i386 buster x86/ http://mirrors.aliyun.com/debian/ 
cp /etc/passwd x86/etc
cp /etc/hosts x86/etc
cp /etc/resolv.conf x86/etc
cp /etc/locale.gen x86/etc
mount -o bind /dev/pts x86/pts
mount -o bind /proc x86/proc
mount -o bind /dev x86/dev
chroot x86
apt-get update
apt-get install locales
locale-gen
apt-get install apt-utils

```
