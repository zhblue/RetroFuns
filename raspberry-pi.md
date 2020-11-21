Tips on raspberry pi
----


raspberry pi make chroot for amd64
--
```
apt-get update
apt-get upgrade
 apt-get install qemu qemu-user qemu-user-static binfmt-support debootstrap binutils
 mkdir /amd64/
 debootstrap --foreign --arch amd64 stretch amd64/ http://mirrors.aliyun.com/debian/
 mount -t sysfs sys amd64/sys/
 mount -t proc proc amd64/proc/
 mount -o bind /dev amd64/dev/
 mount -o bind /dev/pts amd64/dev/pts/
 mount -o bind /dev/shm amd64/dev/shm/
cp /usr/bin/qemu-x86_64-static amd64/usr/bin/
cp /etc/passwd amd64/etc
cp /etc/hosts amd64/etc
cp /etc/resolv.conf amd64/etc
cp /etc/locale.gen amd64/etc
chroot amd64/ /debootstrap/debootstrap --second-stage
chroot amd64/ /bin/su -l root
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:0" >> .bashrc
source ~/.bashrc
apt update
adduser -uid 1000 pi
apt install leafpad
exit
chroot amd64/ /bin/su -l pi
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:01" >> .bashrc
source ~/.bashrc
exit
chroot amd64/ /bin/su -l root
apt-get update
apt-get install locales
locale-gen
apt-get install apt-utils
apt install wine
dpkg --add
exit
 chroot /amd64/ /bin/su -l pi
winecfg


```
