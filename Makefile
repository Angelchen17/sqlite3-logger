CXX=g++
CFLAGS=-O -I.
LIBS=-lsqlite3
SRC=generator.cpp logger.cpp logMessage.cpp
OBJ=$(subst .cpp,.o,$(SRC))
SRC1=dumper.cpp logger.cpp logMessage.cpp
OBJ1=$(subst .cpp,.o,$(SRC1))
all: generator dumper run run2

generator:$(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

dumper :$(OBJ1)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

run:
	./generator "test message." "test2 message." "test3 message." "test4 message."
run2:
	./dumper generator

clean:
	rm -f *o generator dumper
