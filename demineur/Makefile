srcdir=./src/
bindir=./bin/
docdir=./doc/
savedir=./save/

ZIP=demineur
CC=gcc
RM=rm
SRC=$(wildcard $(srcdir)*.c) #fichiers sources
HEAD=$(wildcard $(srcdir)*.h) #fichiers d'entetes
OBJ=$(subst $(srcdir), $(bindir), $(SRC:.c=.o)) #fichiers objets
PROG=demineur.exe


all: $(PROG)

$(PROG): $(OBJ)
	@echo "Compilation de l'executable..."
	@$(CC) $^ -o $(PROG)
	@echo "Compilation de l'executable terminé"

$(bindir)%.o: $(srcdir)%.c
	@echo "Compilation du fichier $^..."
	@$(CC) -c $^ -o $@

.PHONY: clean, save, doc

doc:
	@echo "Création des fichiers latex et html..."
	@doxygen $(docdir)Doxyfile
	@echo "Création des fichiers latex et html terminé."

save:
	@echo "Sauvegarde des fichiers sources en cours..."
	@cp $(SRC) $(savedir)
	@cp $(HEAD) $(savedir)
	@echo "Sauvegarde terminée."

restore:
	@echo "Copie de la sauvegarde des fichiers sauvergardés..."
	@cp $(savedir)*.c $(srcdir)
	@cp $(savedir)*.h $(srcdir)	
	@echo "Copie terminée."

give:
	@echo "Compression du projet..."
	@zip -r $(ZIP) *
	@echo "Compression terminée."

clean:
	@echo "Supression des fichiers objets..."
	@$(RM) $(bindir)*.o 2>/dev/null
	@echo "Suppression de l'executable"
	@$(RM) $(PROG)
	@echo "Suppression terminée."
