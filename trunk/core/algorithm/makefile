algorithm:algorithm.o
	g++ -o algorithm algorithm.o -L/usr/lib/mysql -lmysqlclient
algorithm.o:algorithm.cc
	g++ -c algorithm.cc -I/usr/include/mysql
clean:
	rm algorithm algorithm.o
