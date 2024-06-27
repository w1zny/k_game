CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion
LDLIBS=
OUTPUT=main
CPPCHECK=cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c

all:$(OUTPUT)

$(OUTPUT): main.o k.o hof.o ui.o
	$(CPPCHECK)
	$(CC) $(CFLAGS) main.o k.o hof.o ui.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS)
	
k.o: k.c k.h
	$(CC) $(CFLAGS) -c $^ $(LDLIBS)

hof.o: hof.c hof.h
	$(CC) $(CFLAGS) -c $^ $(LDLIBS)

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c $^ $(LDLIBS)

clean:
	rm -rf $(OUTPUT) *.o
