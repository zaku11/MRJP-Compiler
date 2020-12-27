CC=g++ -std=c++17

FLEX=flex

BISON=bison --warnings=none

OBJS=Absyn.o Lexer.o Parser.o FrontEnd.o Printer.o LLVM.o

.PHONY: clean distclean

all: TestLatte

clean:
	rm -f *.o TestLatte Latte.aux Latte.log Latte.pdf Latte.dvi Latte.ps Latte

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H FrontEnd.cpp FrontEnd.H Makefile Latte.l Latte.y Latte.tex 

TestLatte: ${OBJS} Test.o
	${CC} ${OBJS} Test.o -o latc

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

Test.o: Test.C Parser.H FrontEnd.H Absyn.H Printer.H LLVM.H
	${CC} -c Test.C
