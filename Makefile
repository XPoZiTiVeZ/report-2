.PHONY: all clean prepare

CC = gcc
ASM = nasm
LATEX = pdflatex

CFLAGS = -m32 -Wall -g -no-pie
ASMFLAGS = -f elf32

all: program report

prepare:
	sudo apt update
	sudo apt install gcc gcc-multilib nasm texlive-latex-base texlive-lang-cyrillic texlive-pictures texlive-latex-recommended -y

program: functions.o methods.o main.o
	$(CC) $(CFLAGS) -o program functions.o methods.o main.o -lm

functions.o: functions.asm functions.h
	$(ASM) $(ASMFLAGS) functions.asm -o functions.o

methods.o: methods.c methods.h functions.h
	$(CC) $(CFLAGS) -c methods.c -o methods.o

main.o: main.c methods.h functions.h
	$(CC) $(CFLAGS) -c main.c -o main.o

report: report.tex
	$(LATEX) report.tex
	$(LATEX) report.tex # Для сборки оглавления

clean:
	rm -f *.o program
	rm -f *.aux *.log *.toc *.out