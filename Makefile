CC = g++
CFLAGS  = -Wall -Werror
TARGET = MSH
SRC_DIR = src
SRCS = main.cc file.cc sys.cc
OBJS = $(SRCS:%.cc=%.o)

all: MSH run

%.o: ${SRC_DIR}/%.cc
	@${CC} -c ${CFLAGS} $<

${TARGET}: ${OBJS}
	@${CC} -o $@ ${OBJS}

 run: 
	@./MSH

clean:
	@${RM} *.o ${TARGET}


