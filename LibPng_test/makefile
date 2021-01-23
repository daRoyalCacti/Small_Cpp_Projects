HOST_COMPILER  = g++

# select one of these for Debug vs. Release
#NVCC_DBG       = -g -G
NVCC_DBG       =

NVCCFLAGS      = -std=c++17 -lpng

#Generate: Generate.o
#	$(NVCC) $(NVCCFLAGS) $(GENCODE_FLAGS) -o Generate Generate.o

#Generate.o: ./main.cu
#	$(NVCC) $(NVCCFLAGS) -o Generate.o -c ./main.cu

Generate: ./main.cpp
	$(HOST_COMPILER) `libpng-config --cflags --ldflags` $(NVCCFLAGS) $(GENCODE_FLAGS) -o Generate ./main.cpp -I.

profile_basic: Generate
	nvprof ./Generate

# use nvprof --query-metrics
profile_metrics: Generate
	nvprof --metrics achieved_occupancy,inst_executed,inst_fp_32,inst_fp_64,inst_integer ./Generate

clean:
	rm -f Generate Generate.o
