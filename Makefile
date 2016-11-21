thread:thread.o
	gcc -o thread thread.o -lpthread
thread.o:thread.c
	gcc -c thread.c
clean:
	rm *.o thread
