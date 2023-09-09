How to install amd64 .debs on mipse64el
--
```
ARCH=amd64
apt-get install debootstrap qemu-user-static
debootstrap --arch=$ARCH --foreign --verbose bookworm $ARCH http://mirrors.163.com/debian/
cp /usr/bin/qemu-$ARCH-static $ARCH/usr/bin
chroot $ARCH /debootstrap/debootstrap --second-stage
cp /etc/passwd /etc/shells $ARCH/etc
cp /etc/apt/sources.list $ARCH/etc/apt
mount -o bind /dev $ARCH/dev
mount -o bind /proc $ARCH/proc
chroot $ARCH
apt-get install file
file bin/ls
```
also check out /usr/bin/qemu-debootstrap
