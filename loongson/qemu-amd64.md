How to install amd64 .debs on mipse64el
--
```
apt-get install debootstrap qemu-user-static
debootstrap --arch=amd64 --foreign --verbose bookworm amd64 http://mirrors.163.com/debian/
chroot amd64 /debootstrap/debootstrap --second-stage
cp /etc/passwd /etc/shells amd64/etc
cp /etc/apt/sources.list amd/etc/apt
mount -o bind /dev amd64/dev
mount -o bind /proc amd64/proc
chroot amd64
apt-get install file
file bin/ls
```
