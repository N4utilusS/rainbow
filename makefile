projet : FindReduction.o Dictionary.o HashReduc.o RainbowTable.o CrackerRainbow.o main.o g++ -o projet FindReduction.o Dictionary.o HashReduc.o RainbowTable.o CrackerRainbow.o main.o

main.o : main.cpp CrackerRainbow.h g++ -O2 main.cpp -L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o main.o

CrackerRainbow.o : CrackerRainbow.cpp CrackerRainbow.h g++ -O2 CrackerRainbow.cpp -L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o CrackerRainbow.o

RainbowTable.o : RainbowTable.cpp RainbowTable.h g++ -O2 RainbowTable.cpp -L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o RainbowTable.o

HashReduc.o : HashReduc.cpp HashReduc.h g++ -O2 HashReduc.cpp -L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o HashReduc.o

Dictionary.o : Dictionary.cpp Dictionary.h g++ -O2 Dictionary.cpp -L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o Dictionary.o

FindReduction.o : FindReduction.cpp g++ -O2 FindReduction.cpp --L/Users/Alexis/Desktop/crypto++/ -lcryptopp - o FindReduction.o
