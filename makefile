CFLAGS=-g
LDFLAGS=

####

SOURCES=parser.c lexer.c pwn.c node.c
OBJS=$(SOURCES:.c=.o)

pwn: $(OBJS)
	@echo LD $(OBJS)
	@cc -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS)

.c.o:
	@echo CC $<
	@$(CC) -o $@ -c $< $(CFLAGS)

lexer.c:
	flex -o lexer.c lexer.l

parser.c:
	bison -o parser.c -d parser.y

clean:
	rm *.o lexer.c parser.c parser.h
