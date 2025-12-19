# ============================================================================
# SEZIONE VARIABILI E CONFIGURAZIONE
# ============================================================================
# Definizione delle variabili che contengono i percorsi delle dipendenze
# esterne e la configurazione dei directory di lavoro. 
# Queste variabili vengono utilizzate per rendere il Makefile più modulare
# e facilmente modificabile. Utilizzando variabili invece di path hardcoded
# si facilita la manutenzione e la portabilità del progetto.
# MLX = Path completo alla libreria MLX compilata
# LIBFT = Path completo alla libreria libft compilata
# SRCDIR = Directory contenente i file sorgente (.c)
# OBJDIR = Directory dove verranno salvati i file oggetto (.o)
# Vengono richiamati con la sintassi $(NOME_VARIABILE)


# ============================================================================
# GESTIONE FILE SORGENTE E OGGETTO
# ============================================================================
# SRCS = Lista esplicita di tutti i file sorgente del progetto.
# Ogni file .c deve essere elencato manualmente con il path completo.
# La variabile OBJS utilizza la sostituzione di pattern per convertire
# automaticamente ogni file .c in src/ nel corrispondente file .o in obj/
# Sintassi: $(VAR:pattern=replacement) sostituisce pattern con replacement
# % è una wildcard che rappresenta qualsiasi stringa


# ============================================================================
# CONFIGURAZIONE COMPILATORE E FLAGS
# ============================================================================
# Definizione del nome dell'eseguibile finale e della configurazione
# del compilatore con i relativi flag di compilazione e linking.
# CFLAGS = Flag di compilazione per 42 School standard + inclusione header
# MLX_FLAGS = Flag specifici per il linking con MLX e le dipendenze X11
# -Werror: tratta warning come errori
# -Iinc: include directory inc/ per header
# -I: path header MLX
# -L: path librerie MLX
# -l: linka librerie specifiche
# mlx: libreria grafica principale
# Xext, X11: librerie X Window System
# La funzione wildcard trova automaticamente tutti i file .c nella directory src/
# Questo elimina la necessità di elencare manualmente ogni file sorgente
# e rende il Makefile più flessibile quando si aggiungono nuovi file


NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../inc -g
MLX_FLAGS = -Iminilibx -Lminilibx -lmlx -lXext -lX11 -lm

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = inc

# Dependencies
MLX = minilibx/libmlx.a
LIBFT = libft/libft.a

# Automatic source file discovery
SRCS = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/strarr/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output colors
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
RESET = \033[0m


# ============================================================================
# TARGET PRINCIPALE E GESTIONE DIPENDENZE
# ============================================================================
# Il target 'all' è il default e costruisce tutto il necessario nell'ordine
# corretto: prima le dipendenze esterne (MLX e LIBFT), poi l'eseguibile.
# Questo garantisce che le librerie siano sempre aggiornate prima del linking.
# Target per creare l'eseguibile finale
# Dipende da tutti i file oggetto (OBJS) che devono essere compilati prima
# Il comando linka tutti gli oggetti con le librerie necessarie


# ============================================================================
# REGOLE PATTERN E GESTIONE DIRECTORY
# ============================================================================
# Regola pattern che definisce come compilare qualsiasi file .c in un .o
# La sintassi % è un wildcard che matcha qualsiasi stringa
# La pipe | indica una "order-only prerequisite": $(OBJDIR) deve esistere
# ma se cambia timestamp non ricompila gli oggetti
# $< rappresenta il primo prerequisito (file .c)
# $@ rappresenta il target (file .o)
# Target per creare la directory degli oggetti se non esiste
# L'opzione -p crea directory parent se necessario, senza errori se esiste già


# ============================================================================
# GESTIONE DIPENDENZE ESTERNE
# ============================================================================
# Target per compilare la libreria libft in modo ricorsivo
# L'opzione -C cambia directory prima di eseguire make
# --no-print-directory evita che make stampi "Entering/Leaving directory"

# Target per gestire la libreria MLX con auto-download se necessaria
# Il simbolo @ sopprime l'output del comando (silent execution)
# La struttura if/fi è sintassi shell per condizioni
# Il backslash \ permette di continuare il comando sulla riga successiva
# Se la directory minilibx non esiste, clona il repository ufficiale
# [ ! -d "minilibx" ] testa se la directory NON esiste (!= NOT operatore)
# git clone scarica automaticamente la versione corretta della libreria MLX


# TARGET PRINCIPALE

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Linking executable...$(RESET)\n"
	@$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)✓ Successfully built $(NAME)$(RESET)\n"


# REGOLE DI COMPILAZIONE

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(CYAN)Compiling: $(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[K$(GREEN)✓ Compiled: $<$(RESET)\n"


# GESTIONE DIPENDENZE

$(LIBFT):
	@printf "$(YELLOW)Building libft...$(RESET)\n"
	@$(MAKE) -C libft --no-print-directory
	@printf "$(GREEN)✓ Successfully built libft$(RESET)\n"

$(MLX):
	@if [ ! -d "minilibx" ]; then \
		printf "$(YELLOW)Downloading MLX library...$(RESET)\n"; \
		git clone https://github.com/42Paris/minilibx-linux.git minilibx; \
	fi
	@printf "$(YELLOW)Building MLX...$(RESET)\n"
	@$(MAKE) -C minilibx --no-print-directory
	@printf "$(GREEN)✓ Successfully built MLX$(RESET)\n"


# ============================================================================
# TARGET DI PULIZIA E RICOSTRUZIONE
# ============================================================================
# 	clean: = Target per pulire file temporanei e oggetti compilati
# Il trattino - prima di un comando fa ignorare gli errori di quel comando
# (utile se minilibx non ha un target clean o non esiste)
# 2>/dev/null redirige stderr a /dev/null per sopprimere messaggi di errore
# 	fclean: clean = Full clean: rimuove anche l'eseguibile finale e le librerie compilate
# Dipende da clean, quindi esegue prima la pulizia parziale
# fclean in libft rimuove anche la libreria compilata libft.a
# -f con rm evita errori se il file non esiste (force remove)
# 	re: fclean all = Target per ricostruire tutto da zero: prima pulisce completamente, poi ricompila
# Equivale a: make fclean && make all
# Utile quando si vuole essere sicuri di ripartire da zero (es. dopo modifiche al Makefile)
# 	deps: Target per forzare la ricostruzione delle dipendenze esterne
# Utile quando le librerie libft o MLX hanno problemi o sono corrotte
# Esegue una pulizia completa delle dipendenze e le ricompila da zero
# || true assicura che il comando non fallisca se le directory non esistono


clean:
	@printf "$(RED)Cleaning...$(RESET)\n"
	@$(MAKE) clean -C libft --no-print-directory 2>/dev/null || true
	@$(MAKE) clean -C minilibx --no-print-directory 2>/dev/null || true
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)✓ Clean completed$(RESET)\n"

fclean: clean
	@$(MAKE) fclean -C libft --no-print-directory 2>/dev/null || true
	@rm -f $(NAME)
	@printf "$(GREEN)✓ Full clean completed$(RESET)\n"

re: fclean all

info:
	@printf "$(BLUE)Project: $(NAME)$(RESET)\n"
	@printf "$(BLUE)Sources found:$(RESET)\n"
	@printf "$(CYAN)$(SRCS)$(RESET)\n"
	@printf "$(BLUE)Objects to build:$(RESET)\n"
	@printf "$(CYAN)$(OBJS)$(RESET)\n"

deps: 
	@$(MAKE) fclean -C libft --no-print-directory 2>/dev/null || true
	@$(MAKE) clean -C minilibx --no-print-directory 2>/dev/null || true
	@$(MAKE) $(MLX) $(LIBFT)


# ============================================================================
# DICHIARAZIONE TARGET PHONY
# ============================================================================
# I target phony non corrispondono a file reali, sono solo nomi di azioni
# Questo evita conflitti se esistessero file con questi nomi nella directory
# e garantisce che vengano sempre eseguiti quando richiesti

.PHONY: all clean fclean re info deps
