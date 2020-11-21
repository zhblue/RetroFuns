Tips on raspberry pi
----


raspberry pi make chroot for x86
--
```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get update && sudo apt-get install qemu qemu-user qemu-user-static binfmt-support debootstrap binutils
sudo mkdir /x86/
sudo debootstrap --foreign --arch i386 buster x86/ http://mirrors.aliyun.com/debian/ 
sudo mount -t sysfs sys /x86/sys/
sudo mount -t proc proc /x86/proc/
sudo mount --bind /dev /x86/dev/
sudo mount --bind /dev/pts /x86/dev/pts/
sudo mount --bind /dev/shm /x86/dev/shm/
sudo cp /usr/bin/qemu-i386-static /x86/usr/bin/
cp /etc/passwd x86/etc
cp /etc/hosts x86/etc
cp /etc/resolv.conf x86/etc
cp /etc/locale.gen x86/etc
sudo chroot /x86/ /debootstrap/debootstrap --second-stage
sudo chroot /x86/ /bin/su -l root
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:0" >> .bashrc
source ~/.bashrc
apt update
adduser -uid 1000 pi
apt install leafpad
exit
sudo chroot /x86/ /bin/su -l pi
echo "export LANGUAGE='C'" >> .bashrc
echo "export LC_ALL='C'" >> .bashrc
echo "export DISPLAY=:01" >> .bashrc
source ~/.bashrc
exit
sudo chroot /x86/ /bin/su -l root
apt-get update
apt-get install locales
locale-gen
apt-get install apt-utils
apt install wine
exit
sudo chroot /x86/ /bin/su -l pi
winecfg

```
