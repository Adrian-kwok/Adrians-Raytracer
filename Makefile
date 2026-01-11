CC		= g++
CFLAGS	:= -Wall
SRC_DIR := src
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)
EXEC = raytrace

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
