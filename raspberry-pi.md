raspberry pi make chroot for x86

```
apt-get install qemu qemu-user-static binfmt-support
mkdir x86
debootstrap --arch=i386 buster x86/ http://mirrors.aliyun.com/debian/ 

```
