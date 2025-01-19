CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

SRC = main.c reminder.c linked_list.c interact.c
OBJ = $(SRC:.c=.o)
EXEC = gcal

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)

