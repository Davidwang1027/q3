CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS= main.o cell.o grid.o textdisplay.o 
DEPENDS=${OBJECTS:.o=.d} 
EXEC=main
${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
