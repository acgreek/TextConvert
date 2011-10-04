CFLAGS = -g -Wall
all: main

main: text_convert.o  main.c


test: main
	./main

gcov:main_cov
	lcov --directory . --zerocounters
	./main_cov
	lcov --directory . --capture --output-file app.info
	genhtml app.info -o html

main_cov: text_convert_cov.o main_cov.o
	$(CC) -fprofile-arcs -ftest-coverage text_convert_cov.o main_cov.o -o $@


text_convert_cov.o: text_convert.c
	$(CC) $(CFLAGS) -c -fprofile-arcs -ftest-coverage  -o $@ $<

main_cov.o: main.c
	$(CC) $(CFLAGS) -c -fprofile-arcs -ftest-coverage -o $@  $<
