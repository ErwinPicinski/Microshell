microshell: microshell.c
	gcc -Wall -ansi -o microshell microshell.c

clean:
	rm -f *.o microshell
