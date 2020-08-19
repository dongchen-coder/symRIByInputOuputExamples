import os

def summerizeForBench(bench):
	print "Start to summerize " + bench
 
	if (not os.path.isdir("./" + bench)):
		return

	files = os.listdir("./" + bench)

	outputFile = open("./all/" + bench + "_src.txt", "w")
	for f in files:
		name = f
		if ("_src_" not in name):
			continue
		if ("min" in name or "max" in name):
			continue

		f = open("./"+bench+"/"+f, 'r')
		for line in f:
			if ("(^0^)" in line):
				prog = line.replace("Searched Program (^0^) :", "Prog:")
				outputFile.write(name + " " + prog)
		f.close()
	outputFile.close()

	outputFile = open("./all/" + bench + "_srcsnk.txt", "w")
	for f in files:
		name = f
		if ("_srcsnk_" not in name):
			continue
		if ("min" in name or "max" in name):
			continue

		f = open("./"+bench+"/"+f, 'r')
		for line in f:
			if ("(^0^)" in line):
				prog = line.replace("Searched Program (^0^) :", "Prog:")
				outputFile.write(name + " " + prog)
		f.close()
	outputFile.close()

	outputFile = open("./all/" + bench + "_Iminmax.txt", "w")
	for f in files:
		name = f
		if ("min" not in name and "max" not in name):
			continue
		
		f = open("./"+bench+"/"+f, 'r')
		for line in f:
			if ("(^0^)" in line):
				prog = line.replace("Searched Program (^0^) :", "Prog:")
				conf_raw = name.replace("_result.txt", "")
				conf_raw = conf_raw.replace(bench+"_", "")

				outputFile.write(conf_raw + " " + prog)
		f.close()
	outputFile.close()

	return

#benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]

benches = ["stencil"]

for bench in benches:
	summerizeForBench(bench)
