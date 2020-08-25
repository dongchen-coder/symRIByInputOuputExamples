from multiprocessing import Pool
import os

def processFile(f):
	print f
	name = f[1].replace(".txt","")
	os.system("./bin/symRiSymthesiser -FILE ./inputoutput/ris_per_iter_refsrc/" + f[0] +  "/" + f[1] + " -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80 > ./synResult/" + f[0] + "/" + name + "_src_result.txt")
	return

if __name__ == '__main__':

	benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]
	
	for bench in benches:
		os.system("rm -r -f ./inputoutput/ris_per_iter_refsrc/" + bench)
		os.system("mkdir -p ./inputoutput/ris_per_iter_refsrc/" + bench)

	files = []
	for bench in benches:
		filesForBench = os.listdir("./inputoutput/ris_per_iter_refsrc/" + bench)
		files += [[bench, f] for f in filesForBench]

	p = Pool(2)
	p.map(processFile, files)
	
