NPROC=0
#durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov trisolv stencil cholesky
#trangle adi atax bicg convolution_2d correlation covariance deriche gramschmidt jacobi_1d jacobi_2d seidel_2d symm syr2d syrk trmm heat_3d
#for bench in cholesky durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov stencil trisolv stencil
for bench in stencil #2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle
do

    rm -r -f ./synResult/${bench}
	mkdir -p ./synResult/${bench}
    for dir in "ris_refsrc_Isrc_Psrc" "ris_refsrc_Isrc_Psrc_refsnk" "ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk"
    do
        for entry in "./inputoutput/"${dir}/${bench}/*
	    do
		    name=${entry#./inputoutput/${dir}/${bench}/}
		    #name=${name%.txt}
		    echo $name
        
            ./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 > ./synResult/${bench}/${name}.${dir} &

		    NPROC=$(($NPROC+1))
		    if [ "$NPROC" -ge 60 ]; then
			    wait
			    NPROC=0
		    fi
	    done
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
