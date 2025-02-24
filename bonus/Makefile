asmfile = ft_list_push_front.s ft_list_size.s ft_list_remove_if.s function_runner.s

asmout = $(patsubst %.s,%.o,$(asmfile))

cfile = main.c

cout = $(patsubst %.c,%.o,$(cfile))

outfile = out

NASM = nasm

NASM_FLAGS = -f elf64 

CC = gcc

CC_FLAGS =

all: program

program: $(cout) $(asmout)
	$(CC) $(CC_FLAGS) $(cout) $(asmout) -o $(outfile)

%.o: %.s
	$(NASM) $(NASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

re: fclean all

clean:
	rm -f $(asmout) $(cout)

fclean: clean
	rm -f $(outfile)