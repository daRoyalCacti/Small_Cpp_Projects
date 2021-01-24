CC = g++


SOURCE_DIR = source
ODIR = compiler_objects
_OBJ = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ =  $(patsubst $(SOURCE_DIR)/%.cpp,$(ODIR)/%.o,$(_OBJ)) $(ODIR)/main.o

CFLAGS = -std=c++20
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wfloat-equal -Wshadow 

EXE=Generate


$(ODIR)/%.o: %.cpp 
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp 
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(WFLAGS)


.PHONY: test clean

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~

wipe:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(EXE)
