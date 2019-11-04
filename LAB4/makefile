clean:
	-rm *.o *.c~
pthreads_sum_expanded:
	gcc -D SZ=10000 -D N_THREADS=50 pthreads_sum.c -o pthreads_sum -lpthread
pthreads_sum:
	gcc -D SZ=1000 -D N_THREADS=2 pthreads_sum.c -o pthreads_sum -lpthread
fork_sum:
	gcc fork_sum.c -o fork_sum
run_fork_sum:
	./fork_sum
run_pthreads_sum:
	./pthreads_sum
