for entry in "./inputoutput"/*
do
	name=${entry#./inputoutput/}
	name=${name%.txt}
	echo $name
    ./bin/symRiSymthesiser ./inputoutput/$name.txt > ./synResult/${name}_result.txt
done
