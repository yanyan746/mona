MYSQL_CONCPP_DIR= ...
CPPFLAGS = -L $/home/yanyan/Dev/mona/src/mysql-connector-c++-1.1.11/lib
LDLIBS = -lmysqlcppconn
CXXFLAGS = -std=c++11

ifneq ($(JSON11_ENABLE_DR1467_CANARY),)
CANARY_ARGS = -DJSON11_ENABLE_DR1467_CANARY=$(JSON11_ENABLE_DR1467_CANARY)
endif

main : main.o user.o json11/json11.o
	g++ -Wall $(CXXFLAGS) $(CPPFLAGS) main.o user.o json11/json11.o $(LDLIBS) -o main -lcurl

main.o : main.cpp
	g++ -c $(CXXFLAGS) main.cpp

user.o : user/user.cpp
	g++ -c $(CXXFLAGS) user/user.cpp


.PHONY: clean
clean:
	rm -f main main.o user.o
