CXX = g++
CXXFLAGS =  -Wall -pedantic-errors -g -w -lpthread

SRCS_SEQ =  rainfall.cpp computeLowestNeighbor.cpp updateTricle.cpp
OBJS_SEQ = ${SRCS_SEQ:.cpp=.o}
SRCS_PT =  rainfall_pt.cpp computeLowestNeighbor.cpp updateTricle.cpp
OBJS_PT = ${SRCS_PT:.cpp=.o}
HEADERS = computeLowestNeighbor.h updateTricle.h

MAIN_SEQ = rainfall_seq
MAIN_PT = rainfall_pt

all: ${MAIN_SEQ} ${MAIN_PT}
	@echo	Simple compilter named rainfall_seq has been compiled
	@echo	Simple compilter named rainfall_pt has been compiled

${MAIN_SEQ}: ${OBJS_SEQ}
	${CXX} ${CXXFLAGS} ${OBJS_SEQ} -o ${MAIN_SEQ}
${MAIN_PT}: ${OBJS_PT}
	${CXX} ${CXXFLAGS} ${OBJS_PT} -o ${MAIN_PT}

.cpp.o: 
	${CXX} ${CXXFLAGS} -c $< -o $@

clean: 
	${RM} ${PROGS} ${OBJS_SEQ} *.o *~.
	${RM} ${PROGS} ${OBJS_PT} *.o *~.
