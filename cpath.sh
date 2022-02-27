SAVEIFS=$IFS
IFS=$(echo -en "\n\b")
for p in $*
do
    mkdir $p
done
for i in `find -name "*.vgz"`
do
	bname=`basename -s .vgz $i`
	echo "$bname"
	mv "$i" "$bname.vgm.gz"
      	gzip -d "$bname.vgm.gz"
      	last=$1
      	mv $bname.vgm $last
      	for p in $*
	do
		if [ "$p" != "$1" ] ; then
			vgm-conv -f $last -t $p -i "$last/$bname.vgm" -o "$p/${bname}.vgm"
		fi
		last=$p
	done
done

IFS=$SAVEIFS
