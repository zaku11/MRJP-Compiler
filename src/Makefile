CC=g++ -std=c++17

FLEX=flex

BISON=bison --warnings=none

OBJS=Absyn.o Lexer.o Parser.o FrontEnd.o Printer.o LLVM.o

.PHONY: clean distclean

all: CompilerLatte

clean:
	rm -f *.o CompilerLatte Latte.aux Latte.log Latte.pdf Latte.dvi Latte.ps Latte

distclean: clean
	rm -f Absyn.C Absyn.H Compiler.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H FrontEnd.cpp FrontEnd.H Makefile Latte.l Latte.y Latte.tex 

CompilerLatte: ${OBJS} Compiler.o
	${CC} ${OBJS} Compiler.o -o latc_llvm

Absyn.o: Absyn.C Absyn.H
	${CC} -c Absyn.C

Lexer.C: Latte.l
	${FLEX} -oLexer.C Latte.l

Parser.C: Latte.y
	${BISON} Latte.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} -c Lexer.C 

Parser.o: Parser.C Absyn.H
	${CC} -c Parser.C

FrontEnd.o: FrontEnd.cpp FrontEnd.H Absyn.H
	${CC} -c FrontEnd.cpp

LLVM.o: LLVM.cpp LLVM.H Absyn.H
	${CC} -c LLVM.cpp

Printer.o: Printer.C Printer.H Absyn.H
	${CC} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} -Wno-unused-parameter -c Skeleton.C

Compiler.o: Compiler.C Parser.H FrontEnd.H Absyn.H Printer.H LLVM.H
	${CC} -c Compiler.C
