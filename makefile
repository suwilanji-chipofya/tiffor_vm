CC=gcc

tiffor: main.o
    $(CC) main.o -o tiffor
main.o: src/main.c
    $(CC) -c src/main.c -o main.o
clean:
    rm ./*.o
