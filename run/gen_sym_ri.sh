NPROC=0
#2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle

SYM_RI_PATH="./data/sym_ri/"

SYN_CONF="-CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 5 -SEARCHTIMEFORPREDSINSECONDS 5"

for bench in stencil #stencil_tiled
do
    rm -rf ${SYM_RI_PATH}${bench}
    mkdir -p ${SYM_RI_PATH}${bench}
    for dir in "src_only" "src_enhanced" "src_snk" "ibound"
    do
        for entry in "./data/input-output_examples/"${bench}/${dir}/*
        do

            name=${entry#./data/input-output_examples/${bench}/${dir}/}
            echo $name
            if [ ${dir} == "src_only" ] 
            then
                echo "src_only"
                ../synthesizer/bin/symRiSymthesiser -FILE ${entry} ${SYN_CONF} -RULESTOAPPLY SrcOnly > ./data/sym_ri/${bench}/${name}.${dir} &
            elif [ ${dir} == "src_enhanced" ] 
            then
                echo "src_enhanced"
                ../synthesizer/bin/symRiSymthesiser -FILE ${entry} ${SYN_CONF} -RULESTOAPPLY SrcEnhanced > ./data/sym_ri/${bench}/${name}.${dir} &
            elif [ ${dir} == "src_snk" ] 
            then
                echo "src_snk"
                ../synthesizer/bin/symRiSymthesiser -FILE ${entry} ${SYN_CONF} -RULESTOAPPLY SrcSnk > ./data/sym_ri/${bench}/${name}.${dir} &
            elif [ ${dir} == "ibound" ] 
            then
                echo "ibound"
                ../synthesizer/bin/symRiSymthesiser -FILE ${entry} ${SYN_CONF} -RULESTOAPPLY SrcOnly > ./data/sym_ri/${bench}/${name}.${dir} &
            fi 

            NPROC=$(($NPROC+1))
            if [ "$NPROC" -ge 60 ]
            then
                wait
                NPROC=0
            fi

        done
    done
done


