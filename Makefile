NAME = CapchaNN
INCLUDE = ./include
CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++11 -I $(INCLUDE)
CVLIBS = `pkg-config --cflags --libs opencv`
FANNLIBS = -lfann -lm
DEBUG =
OBJECTS =
SRC = ./src


GenerateTraining: GenerateTraining.o
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) $^ -o $@
	GenerateTraining

GenerateTraining.o: $(SRC)/GenerateTraining.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) -c $<

TrainFann: TrainFann.o
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) $(FANNLIBS) $^ -o $@

TrainFann.o: $(SRC)/TrainFann.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) $(FANNLIBS) -c $<

SanityTest: SantityTest.o
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) $(FANNLIBS) $^ -o $@

SanityTest.o: $(SRC)/SanityTest.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(CVLIBS) $(FANNLIBS) -c $<

clean:
	rm -rf *.o
	rm $(NAME)
