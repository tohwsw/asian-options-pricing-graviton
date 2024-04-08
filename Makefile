CC = /usr/bin/g++
CFLAGS = -std=c++11 
# -I /opt/homebrew/Cellar/asio/1.28.1/include 

pricing: main.o asian.o payoff.o
	$(CC) $(CFLAGS) -o pricing main.o asian.o payoff.o

main.o : main.cpp payoff.h path_generate.h asian.h
	$(CC) $(CFLAGS) -c main.cpp

asian.o: asian.cpp payoff.h
	$(CC) $(CFLAGS) -c asian.cpp

payoff.o: payoff.cpp payoff.h
	$(CC) $(CFLAGS) -c payoff.cpp

