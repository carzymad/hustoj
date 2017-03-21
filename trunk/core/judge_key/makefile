judge_key:judge_key.o
	g++ -o judge_key judge_key.o -L/usr/lib/mysql -lmysqlclient
judge_key.o:judge_key.cc
	g++ -c judge_key.cc -I/usr/include/mysql
clean:
	rm judge_key judge_key.o
