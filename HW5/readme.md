
#multiThreads.c

	#time:
		real	0m2.039s
		user	0m2.820s
		sys	0m0.319s
	
	Sys time is not changed, but real time for multiThreads is less, which is to
	be expected.


#singleThreads.c

	#time:
		real	0m2.940s
		user	0m2.618s
		sys	0m0.319s

	For an unkown reason, multiThreads returns the correct number for "football", 
	but singleThread returns 3 less than the correct amount. 