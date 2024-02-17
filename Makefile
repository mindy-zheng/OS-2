CC	= gcc -g3 
CFLAGS	= -g3
TARGET1	= user
TARGET2	= oss 

OBJ1	= user.o
OBJ2	= oss.o 

all:	$(TARGET1) $(TARGET2) 

$(TARGET1):	$(OBJ1)
	$(CC) -o $(TARGET1) $(OBJ1) 

$(TARGET2):	$(OBJ2)
	$(CC) -o $(TARGET2) $(OBJ2)

user.o:	user.c
	$(CC) $(CFLAGS) -c user.c

oss.o:	oss.c
	$(CC) $(CFLAGS) -c oss.c

clean: 
	/bin/rm -f *.o $(TARGET1) $(TARGET2)
