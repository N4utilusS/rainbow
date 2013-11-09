projet: main.o Dictionary.o HashReduc.o RainbowTable.o CrackerRainbow.o
	g++ -O2 main.o Dictionary.o HashReduc.o RainbowTable.o CrackerRainbow.o -L./crypto++ -lcryptopp -o Project

main.o: main.cpp CrackerRainbow.h 
	g++ -Wall -c main.cpp

CrackerRainbow.o: CrackerRainbow.cpp CrackerRainbow.h RainbowTable.h Dictionary.h
	g++ -Wall -c CrackerRainbow.cpp

RainbowTable.o: RainbowTable.cpp RainbowTable.h Dictionary.h HashReduc.h
	g++ -Wall -c RainbowTable.cpp

HashReduc.o: HashReduc.cpp HashReduc.h
	g++ -Wall -c HashReduc.cpp

Dictionary.o: Dictionary.cpp Dictionary.h 
	g++ -Wall -c Dictionary.cpp

