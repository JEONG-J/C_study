CC = gcc
TARGET = main
OBJECTS = main.c

all = $(TARGET)

$(TARGET) : $(OBJECTS)
			  $(CC) $^ -o $@	

clean :
	rm *.o test_file
