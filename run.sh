NPROC=0
#durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov trisolv stencil cholesky
#trangle adi atax bicg convolution_2d correlation covariance deriche gramschmidt jacobi_1d jacobi_2d seidel_2d symm syr2d syrk trmm heat_3d
#for bench in cholesky durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov stencil trisolv stencil
#2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle
for bench in 2mm 3mm adi atax bicg cholesky correlation covariance deriche durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d
do

    rm -r -f ./synResult/${bench}
	mkdir -p ./synResult/${bench}
    for dir in "ris_refsrc_Isrc_Psrc" "ris_refsrc_Isrc_Psrc_refsnk" "ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk" "ris_Ibound"
    do
        for entry in "./inputoutput/"${dir}/${bench}/*
	    do
		    name=${entry#./inputoutput/${dir}/${bench}/}
		    echo $name
             
            if [ ${dir} == "ris_refsrc_Isrc_Psrc" ]; then
                echo "SrcOnly"
                ./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 -RULESTOAPPLY SrcOnly > ./synResult/${bench}/${name}.${dir} &
            elif [ ${dir} == "ris_refsrc_Isrc_Psrc_refsnk" ]; then
                ./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 -RULESTOAPPLY SrcEnhanced > ./synResult/${bench}/${name}.${dir} &
            #elif [ ${dir} == "ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk" ]; then   
                #./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 -RULESTOAPPLY SrcSnk > ./synResult/${bench}/${name}.${dir} &
            elif [ ${dir} == "ris_Ibound" ]; then
                ./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 -RULESTOAPPLY SrcOnly > ./synResult/${bench}/${name}.${dir} &
            else
                echo "INV"
            fi

            #./bin/symRiSymthesiser -FILE ${entry} -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 80 -SEARCHTIMEFORPREDSINSECONDS 80 > ./synResult/${bench}/${name}.${dir} &

		    NPROC=$(($NPROC+1))
		    if [ "$NPROC" -ge 60 ]; then
			    wait
			    NPROC=0
		    fi
	    done
    done
done
