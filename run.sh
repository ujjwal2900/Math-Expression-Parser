lex Parser.l
g++ -g -c lex.yy.c -o lex.yy.o
g++ -g -c Equations.c -o Equations.o
g++ -g Equations.o lex.yy.o -o exe -lfl

