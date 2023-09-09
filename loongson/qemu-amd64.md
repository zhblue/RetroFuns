How to install amd64 .debs on mipse64el
--
```
apt-get install debootstrap qemu-user-static
debootstrap --arch=amd64 --foreign --verbose bookworm amd64 http://mirrors.163.com/debian/
cp /etc/passwd amd64/etc
cp /etc/apt/sources.list amd/etc/apt
chroot amd64
apt-get install file
file bin/ls
```
