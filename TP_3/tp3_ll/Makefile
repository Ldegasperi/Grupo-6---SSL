all:
	bison -yd bisonBasico.y
	flex flexBasico.l
	gcc lex.yy.c y.tab.c -o salida.exe
	