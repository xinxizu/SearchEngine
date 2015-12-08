#Makefile

include= -I ../include
warn= -Wall -Werror

a.out:main.c hashTable.o merge.o
	gcc -O2 -g main.c  merge.o hashTable.o ${warn}  ${include}

merge.o:merge.c
	gcc -c merge.c ${warn}  ${include}

hashTable.o:hashTable.c
	gcc -c hashTable.c  ${warn} ${include}

clean:
	rm -rf *.o
