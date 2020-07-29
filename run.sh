for bench in cholesky durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov trisolv #stencil
do
	mkdir ./synResult/${bench}
	for entry in "./inputoutput/ris_per_iter_ref"/${bench}/*
	do
		name=${entry#./inputoutput/ris_per_iter_ref/${bench}/}
		name=${name%.txt}
		echo $name
		./bin/symRiSymthesiser ./inputoutput/ris_per_iter_ref/${bench}/$name.txt > ./synResult/${bench}/${name}_result.txt
	done
done
