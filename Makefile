parser:	main.c parser.c parser.h
	gcc main.c parser.c -o parser $(CFLAGS)
	ctags -R
clean:
	rm parser
