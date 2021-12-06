CC = g++
LD = g++
FLAGS = -std=c++11 -Wall

OBJS = matriz_simetrica_bits.o	\
		vetor_de_bits.o			\
		grafo_matriz.o			

TESTS = teste_vetor_de_bits.exe 	\
		teste_matriz_simetrica.exe	\
		teste_grafo_matriz.exe		

EXECS = 

all:	$(OBJS) $(TESTS)

%.exe:	%.o $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o $@

%.o:	source/%.cpp
	$(LD) $(FLAGS) $< -c

%.o:	tests/%.cpp
	$(LD) $(FLAGS) $< -c

clean:
	rm *.o $(TESTS)