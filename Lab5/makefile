clean:
	-rm bin_sem rd_wr
rd_wr:
	gcc -lpthread rd_wr.c -o rd_wr
bin_sem:
	gcc -lpthread bin_sem.c -o bin_sem
run_rd_wr:
	./rd_wr
run_bin_sem:
	./bin_sem
