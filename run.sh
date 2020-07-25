for bench in stencil
do
	for entry in "./inputoutput/ris_per_iter_ref"/${bench}/*
	do
		name=${entry#./inputoutput/ris_per_iter_ref/${bench}/}
		name=${name%.txt}
		echo $name
    		./bin/symRiSymthesiser ./inputoutput/ris_per_iter_ref/${bench}/$name.txt > ./synResult/${bench}/${name}_result.txt
	done
done
