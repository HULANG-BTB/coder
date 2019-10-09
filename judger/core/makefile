all: JudgeClient.cpp JudgeServer.cpp
	g++ -Wall -c -I/usr/local/mysql/include/mysql -I/usr/include/mysql JudgeClient.cpp
	g++ -Wall -o JudgeClient JudgeClient.o -L/usr/local/mysql/lib/mysql -L/usr/lib/mysql  -L/usr/lib64/mysql  -lmysqlclient
	g++ -Wall -c -I/usr/local/mysql/include/mysql -I/usr/include/mysql JudgeServer.cpp
	g++ -Wall -o JudgeServer JudgeServer.o -L/usr/local/mysql/lib/mysql -L/usr/lib/mysql  -L/usr/lib64/mysql  -lmysqlclient
