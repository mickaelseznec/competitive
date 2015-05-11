EXE = multiple_morse_match
ALT_EXE = dico_generate
CPPFLAGS = -W -Wall -g -pg -lm -lcrypt -pipe -O2 -std=c++11
.PHONY = all execute

all: $(EXE) $(ALT_EXE) execute

execute:
	./$(EXE) < inputs
