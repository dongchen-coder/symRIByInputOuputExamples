NPROC=0
#durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov trisolv stencil cholesky
#trangle adi atax bicg convolution_2d correlation covariance deriche gramschmidt jacobi_1d jacobi_2d seidel_2d symm syr2d syrk trmm heat_3d
for bench in cholesky durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov stencil trisolv #stencil
do

	mkdir ./synResult/${bench}
	for entry in "./inputoutput/ris_per_iter_refsrc"/${bench}/*
	do
		name=${entry#./inputoutput/ris_per_iter_refsrc/${bench}/}
		name=${name%.txt}
		echo $name
        
        ./bin/symRiSymthesiser -FILE ./inputoutput/ris_per_iter_refsrc/${bench}/${name}.txt -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80 > ./synResult/${bench}/${name}_src_result.txt &

		NPROC=$(($NPROC+1))
		if [ "$NPROC" -ge 60 ]; then
			wait
			NPROC=0
		fi
	done
    '''
	for entry in "./inputoutput/ris_per_iter_refsrcsnk"/${bench}/*
    do
        name=${entry#./inputoutput/ris_per_iter_refsrcsnk/${bench}/}
		name=${name%.txt}
		echo $name
		
        ./bin/symRiSymthesiser -FILE ./inputoutput/ris_per_iter_refsrcsnk/${bench}/${name}.txt -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcSnk -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 4000 > ./synResult/${bench}/${name}_srcsnk_result.txt &

		NPROC=$(($NPROC+1))
		if [ "$NPROC" -ge 60 ]; then
			wait
			NPROC=0
		fi
    done
    '''
done
