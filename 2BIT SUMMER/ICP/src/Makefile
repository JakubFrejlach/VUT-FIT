CC = g++
CFLAGS = -std=c++14 -Wall -Wextra -pedantic -g -pthread

all: program clean

program:
	$(CC) $(CFLAGS) -c board.cpp
	$(CC) $(CFLAGS) -c chess.cpp
	$(CC) $(CFLAGS) -c piece.cpp
	$(CC) $(CFLAGS) -c move.cpp
	$(CC) $(CFLAGS) -c bishop.cpp
	$(CC) $(CFLAGS) -c king.cpp
	$(CC) $(CFLAGS) -c knight.cpp
	$(CC) $(CFLAGS) -c queen.cpp
	$(CC) $(CFLAGS) -c rook.cpp
	$(CC) $(CFLAGS) -c pawn.cpp
	$(CC) $(CFLAGS) -c parser.cpp
	$(CC) $(CFLAGS) -o chess board.o chess.o parser.o move.o piece.o bishop.o king.o knight.o queen.o rook.o pawn.o
clean:
	 @rm chess.o board.o piece.o bishop.o king.o knight.o queen.o rook.o pawn.o move.o parser.o
