 #
 # Universidade Federal do Rio de Janeiro
 # Trabalho da disciplina Circuitos Elétricos 2
 # 2013/1
 # Por Ian Esteves do Nascimento e Igor Vital
 #

EXE = circuitSimulator.exe
OBJ = main.o circuitSimulator.o netList.o myUti.o

all: $(EXE)

circuitSimulator.exe: $(OBJ)
	g++ -o $@ $^

main.o: circuitSimulator.h netList.h myUti.h
circuitSimulator.o: circuitSimulator.h netList.h myUti.h
netList.o: netList.h myUti.h
myUti.o: myUti.h

%.o: %.cpp
	g++ -c $<

clean:
	del /q *.exe *.o