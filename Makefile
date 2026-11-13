# Compilatore e flag richiesti dalle specifiche
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g

# Trova in automatico tutti i file .c nella cartella src/
SRC = $(wildcard src/*.c)
# Crea i nomi dei file oggetto (.o) corrispondenti
OBJ = $(SRC:.c=.o)

# Nome dell'eseguibile
TARGET = sopravvivenza.out

# Regola di default quando scrivi solo "make"
all: $(TARGET)

# Collega i file oggetto per creare l'eseguibile finale
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per pulire il progetto dai file compilati
clean:
	rm -f src/*.o $(TARGET)

# Regola per generare la documentazione
doc:
	doxygen Doxyfile

# Indica che queste parole non sono nomi di file
.PHONY: all clean doc