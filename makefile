CC=g++ -Wall -std=c++11

all:
	make main_c
	make main_l
	make clean
	make success

main_c:	*.cpp
	$(CC) -c *.cpp 

main_l: *.o
	$(CC) -o app *.o

clean:
	rm -f *.o

success:
	echo "\n[ Make successful! ]\n"
