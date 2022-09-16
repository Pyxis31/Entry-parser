############################
# Définition des variables #
############################

# Chemins d'installation :

# Des bibliothèques standard de MinGW(32) (version MSYS2)
DIR_MGW = "C:/msys32/mingw32/i686-w64-mingw32"

# Répertoires dans lesquels se trouvent les fichiers headers (.h)
# -I : ajoute un répertoire de recherche de fichiers
INCLUDES = 	-I $(DIR_MGW)/include \



########################################
# Définition des règles de compilation #
########################################

# Commande de suppression de fichier
RM = del

# Nom de la librairie
DLL=fsjslib.dll

# Nom du fichier source (fichier avec l'extension .dll remplacée par .c)
SRC=$(DLL:.dll=.c)

# Nom du fichier objet (fichier avec l'extension .dll remplacée par .o)
OBJ=$(DLL:.dll=.o)

# Nom de la librairie d'importation (fichier avec l'extension .dll remplacée par .lib)
IMP_LIB=$(DLL:.dll=.lib)

########################################
#   Compilation --> Edition de lien    #
########################################

# II) Edition de lien : construction de la DLL et de la librairie d'importation à partir du fichier objet
$(DLL): $(OBJ)
		gcc -shared -o $(DLL) $(OBJ) -Wl,--out-implib,$(IMP_LIB)

# I) Compilation : génération du fichier objets ".o" à partir du fichier source ".c" :
$(OBJ): $(SRC)		
		gcc -c -D BUILDING_DLL $(SRC) $(INCLUDES) 

# Nettoyage
clean:
		$(RM) *.o *.exe *~
				
