CC = g++
CFLAGS = -Wall
LDFLAGS =
OBJFILES = main.o BST.o
TARGET = myAppStore

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~