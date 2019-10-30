sys_info:
	gcc sys_info.c -o sys_info

.PHONY: clean

clean:
	-rm -rf *.o *.c~

test1:
	./sys_info /bin/date

test2:
	./sys_info date

test3:
	-./sys_info too many

test4:
	-./sys_info

test5:
	-./sys_info notcmd

test6:
	./sys_info uname

test7:
	./sys_info ls

test8:
	./sys_info arch

test9:
	./sys_info hostname

test10:
	./sys_info cal

test: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10
