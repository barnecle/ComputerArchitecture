clean:
	-rm rand_chars counting_sem prodcons_q
rand_chars:
	gcc rand_chars.c -o rand_chars
counting_sem:
	gcc -lpthread counting_sem.c -o counting_sem
prodcons_q:
	gcc -lpthread prodcons_q.c -o prodcons_q
run_rand_chars:
	./rand_chars
run_counting_sem:
	./counting_sem
run_prodcons_q:
	./prodcons_q
