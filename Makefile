keylogger: main.o keylog.o network.o
	gcc main.o keylog.o network.o -o sharingan

network.o: network.c
	gcc -c network.c

keylog.o: keylog.c
	gcc -c keylog.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o sharingan
	rm ./keylog
