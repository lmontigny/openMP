/*
Way in which parallel loop iterations are distributed among the threads
Depends upon whether each loop iteration yields the same amount of work
Schedule clause  schedule(type[, chunk_size])
Static schedule - each thread is assigned a fixed number of chunks (default)
Chunks are groups of iterations (in contiguous order) that are assigned to threads
Dynamic schedule - each thread grabs "chunk" iterations until all iterations are done
Faster threads are assigned more iterations
Interleaved is when chunks are assigned to the processors in a round-robin manner
Guided is a variant of dynamic scheduling where successive chunks get smaller
Runtime is determined at runtime and set by a environment variable
export OMP_SCHEDULE="dynamic, 100"
*/


#pragma omp parallel for schedule(dynamic) private(tmp, i, j, k)  
	for (i=0; i<Ndim; i++){
		for (j=0; j<Mdim; j++){ 
                        tmp = 0.0;
			for(k=0;k<Pdim;k++){
				tmp += *(A+(i*Ndim+k)) *  *(B+(k*Pdim+j));
			}
			*(C+(i*Ndim+j)) = tmp;
		}
	}
