CC = g++
LD = g++
FLAGS = -std=c++11 -Wall

OBJS = matriz_simetrica_bits.o	\
		vetor_de_bits.o

EXECS = teste_vetor_de_bits.exec

all:	$(EXECS) $(OBJS)

%.exec:	%.o $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o $@

clean:
	rm *.o $(EXECS)

%.o:	%.cpp
	$(LD) $(FLAGS) $< -c
