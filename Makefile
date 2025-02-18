asmfile = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s

asmout = $(patsubst %.s,%.o,$(asmfile))

cfile = main.c

cout = $(patsubst %.c,%.o,$(cfile))

outfile = out

NASM = nasm

NASM_FLAGS = -f elf64

CC = gcc

all: $(cout) $(asmout)
	$(CC) $(cout) $(asmout) -o $(outfile)

%.o: %.s
	$(NASM) $(NASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm $(asmout) $(cout)