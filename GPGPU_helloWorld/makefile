CC = g++

ODIR = compiler_objects
OBJ = $(ODIR)/main.o

CFLAGS = -std=c++17 -lOpenCL

EXE=Generate.exe




$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: test clean

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
