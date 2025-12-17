CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

LEX = flex
YACC = bison

TARGET = compiler

LEX_SRC = lexer.l
YACC_SRC = parser.ypp

LEX_GEN = lex.yy.c
YACC_GEN = parser.tab.cpp
YACC_HDR = parser.tab.hpp

SRC = \
	main.cpp \
	symbol_table.cpp \
	codegen.cpp \
	procedure_table.cpp \
	$(LEX_GEN) \
	$(YACC_GEN)
	
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LEX_GEN): $(LEX_SRC) $(YACC_HDR)
	$(LEX) $(LEX_SRC)

$(YACC_GEN) $(YACC_HDR): $(YACC_SRC)
	$(YACC) -d $(YACC_SRC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o $(LEX_GEN) $(YACC_GEN) $(YACC_HDR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
