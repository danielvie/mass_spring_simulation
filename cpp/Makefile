# CONFIGURANDO FLAGS COMPILADOR
CXX           = g++
CC            = gcc

INCLUDE       = -Isrc -Imodel
DECLARE       = 

CFLAGS       = -O0 -g -Wall ${INCLUDE} ${DECLARE}
CXXFLAGS     = -O0 -std=c++17 -g -Wall ${INCLUDE} ${DECLARE}
LDFLAGS      = 

# DEFININDO NOME LIB 'python' E 'exe'
app           = main.exe

# BREAKLINE CONSTANT
ifeq (${OS},Windows_NT)
break_line = \\\\\\n
else
break_line = \\\\n
endif

# LENDO ARQUIVOS
src           = $(wildcard src/*.c*)
model         = $(wildcard model/*.c*)

# AJUSTANDO 'src' E 'obj'
obj           = $(addsuffix .o,$(basename $(src:src/%=obj/%)))
obj          += $(addsuffix .o,$(basename $(model:model/%=obj/%)))

# LEIS DE COMPILACAO
all: r

r: run

# COMPILACAO 'app {exe}'
${app}: ${obj}
	$(CXX) -o ${app} ${obj}

# ESCREVENDO '*.o' EM 'obj'
obj/%.o : src/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

obj/%.o : model/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

# MONITORANDO ALTERACOES '.h' IMPORTANTES
# obj/teste.o : src/teste.h

# INICIALIZANDO PASTAS
init: create_folders
init: create_main
init: create_readme

i: init

f: create_folders

m: create_main

re: create_readme

res: reset

.SILENT: create_folders
create_folders:
	mkdir obj src include lib

.SILENT: create_main
create_main:
	printf "#include <iostream>\n\n" > src/main.cpp
	printf "int main(int argc, char const *argv[])\n" >> src/main.cpp
	printf "{\n" >> src/main.cpp
	printf "	std::cout << \"-----------------------------------------${break_line}\";\n" >> src/main.cpp
	printf "	std::cout << \"hello${break_line}\";\n" >> src/main.cpp
	printf "	return 0;\n" >> src/main.cpp
	printf "}" >> src/main.cpp

.SILENT: create_readme
create_readme:
	printf "\n### REF\n" > README.md

# EXECURANDO 'exe'
run: ${app}
	./${app}
# run: plot
	
p: plot

plot:
	python plot.py

# LIMPANDO OBJETOS
clean: 
	rm obj/*
	rm states.log

reset:
	rm -rf *