CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = help.h
OBJ = ll.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

ll: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

