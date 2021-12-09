CC = g++
LD = g++
FLAGS = -std=c++11 -Wall

# Ao criar uma nova biblioteca "sua_lib.cpp", inclua "sua_lib.o" abaixo  
# para compilar e incluir o objeto nas linkedições
OBJS = matriz_simetrica_bits.o	\
		vetor_de_bits.o			\
		grafo_matriz.o			\
		grafo_lista.o

# Ao criar um novo programa para testes em geral, "teste_qualquer.exe", inclua-o
# abaixo para que seja compilado ao comando "make"
TESTS = teste_vetor_de_bits.exe 	\
		teste_matriz_simetrica.exe	\
		teste_grafo_matriz.exe		\
		teste_grafo_lista.exe

# O(s) programa(s) oficial futuramente será definido aqui abaixo
EXECS = 

%.exe:	%.o $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o $@

%.o:	source/%.cpp
	$(LD) $(FLAGS) $< -c

%.o:	tests/%.cpp
	$(LD) $(FLAGS) $< -c

all:	$(OBJS) $(TESTS)

clean-objs:
	rm *.o 

clean: 
	rm *.o $(TESTS) $(EXECS)