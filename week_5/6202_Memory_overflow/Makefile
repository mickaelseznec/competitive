EXE = memory generator
CPPFLAGS = -W -Wall -g -pg -lm -lcrypt -pipe -O2 -std=c++11
.PHONY = all execute

all: $(EXE) $(ALT_EXE) execute

execute:
	./$(EXE) < inputs
