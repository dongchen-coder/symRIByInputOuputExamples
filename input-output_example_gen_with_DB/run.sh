docker build -t mysql_image .

docker run -v ${PWD}/src:/src -v ${PWD}/../inputoutput/raw_ris_per_size_ELM:/raw_ris_per_size_ELM -it mysql_image
