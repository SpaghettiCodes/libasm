asmfile = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

asmBonus = ./bonus/ft_atoi_base.s ./bonus/ft_list_push_front.s ./bonus/ft_list_remove_if.s ./bonus/ft_list_size.s ./bonus/ft_list_sort.s

asmout = $(patsubst %.s,%.o,$(asmfile))

asmBonusOut = $(patsubst %.s,%.o,$(asmBonus))

libasm = libasm.a

cfile = test.c

cBonusFile = ./bonus/main.c

cout = $(patsubst %.c,%.o,$(cfile))

cBonusOut = $(patsubst %.c,%.o,$(cBonusFile))

outfile = out

NASM = nasm

NASM_FLAGS = -f elf64

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -L. -lasm

all: program

bonus: $(libasm) program_bonus

program: $(libasm) $(cout)
	$(CC) $(cout) $(CC_FLAGS) -o $(outfile)

program_bonus: LIBASM_BONUS $(cBonusOut)
	$(CC) $(cBonusOut) $(CC_FLAGS) -o $(outfile)

%.o: %.s
	$(NASM) $(NASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

$(libasm): $(asmout)
	ar rcs $@ $(asmout)

LIBASM_BONUS: $(asmBonusOut)
	ar rcs $(libasm) $(asmBonusOut)

re: fclean all

re_bonus: fclean bonus

clean:
	rm -f $(asmout) $(asmBonusOut) $(cout) $(cBonusOut)

fclean: clean
	rm -f $(outfile) $(libasm)