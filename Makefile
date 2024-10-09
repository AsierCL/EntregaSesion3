CC = gcc
TARGET = programa
MAINDIR = .
SRCDIR = src

# Wildcard expande un patrón, es decir,
# busca en el directorio SRCDIR todos los
# archivos que cumplan la condición de
# terminar en .c
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:.c=.o)

MAIN_SOURCES := $(wildcard $(MAINDIR)/*.c)
MAIN_OBJECTS := $(MAIN_SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(MAIN_OBJECTS)
	$(CC) $^ -o $@ -Wall

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ -Wall

$(MAINDIR)/%.o: $(MAINDIR)/%.c
	$(CC) -c $< -o $@ -Wall

clean:
	rm -f $(OBJECTS) $(MAIN_OBJECTS)

cleanall: clean
	rm -f  $(TARGET)
