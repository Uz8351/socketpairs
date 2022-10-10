CC          = gcc
CFLAGS		= -c -Wall -Werror
LDFLAGS		= 
SOURCES		= Socket_Pair.c volcado.c
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.c=.o)
TARGET		= Socket_Pair

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@  

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
