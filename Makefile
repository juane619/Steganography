.PHONY: clean mrproper all

AR = ar
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g -I$(INC)
LDFLAGS = -L$(LIB)
LDLIBS = -lcodificar
INC = include
SRC = src
OBJ = obj
LIB = lib
BIN = bin

# ************ Compilación de módulos ************
all: $(BIN)/ocultar $(BIN)/revelar

$(BIN)/ocultar : $(OBJ)/ocultar.o $(LIB)/libcodificar.a
	$(CXX) -o $(BIN)/ocultar $(OBJ)/ocultar.o $(LDFLAGS) $(LDLIBS)

$(BIN)/revelar : $(OBJ)/revelar.o $(LIB)/libcodificar.a
	$(CXX) -o $(BIN)/revelar $(OBJ)/revelar.o $(LDFLAGS) $(LDLIBS)

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

$(OBJ)/ocultar.o : $(INC)/codificar.h $(SRC)/ocultar.cpp 
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/ocultar.o $(SRC)/ocultar.cpp 

$(OBJ)/revelar.o : $(INC)/codificar.h $(SRC)/revelar.cpp 
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/revelar.o $(SRC)/revelar.cpp 

$(OBJ)/codificar.o : $(INC)/codificar.h $(SRC)/codificar.cpp 
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/codificar.o $(SRC)/codificar.cpp

$(LIB)/libcodificar.a : $(OBJ)/codificar.o $(OBJ)/imagenES.o
	$(AR) rvs $(LIB)/libcodificar.a $(OBJ)/codificar.o $(OBJ)/imagenES.o

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
