lex Parser.l
g++ -g -c lex.yy.c -o lex.yy.o
g++ -g -c Equations.c -o Equations.o
g++ -g -c Alternate_a_b.c -o Alternate_a_b.o
g++ -g -c SqlSelectParserCFG.c -o SqlSelectParserCFG.o
g++ -g -c MathExpParser.c -o MathExpParser.o
g++ -g -c EnumConvertor.cpp -o EnumConvertor.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c Operators.cpp -o operators.o
g++ -g -c Dtypes.cpp -o Dtypes.o

g++ -g Equations.o lex.yy.o Alternate_a_b.o SqlSelectParserCFG.o MathExpParser.o EnumConvertor.o MexprTree.o operators.o Dtypes.o -o exe -lfl

