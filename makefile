# Define directories.
SRCDIR  := src
OBJDIR  := obj
INCLDIR := include
PROGDIR := 

CC     := gcc
LIB    := -LSDL2/lib
INCL   := -I$(INCLDIR) -ISDL2/include
MAIN   := CLogo

# Define flags
$(MAIN): CFLAGS := -Wall -Wextra -O2 -s -flto -pedantic -std=c11
debug:   CFLAGS := -Wall -Wextra -DDEBUG -g

LFLAGS := -Wl,--no-warn-search-mismatch
LIBS   := -lSDL2main -lSDL2 -lSDL2_image -lm

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(patsubst %, $(OBJDIR)/%, $(notdir $(SRC:%.c=%.o)))
DEP := $(wildcard $(INCLDIR)/*.h)

# Add Windows-specific options.
ifeq ($(OS), Windows_NT)

LIBS := -lmingw32 $(LIBS)
RES := $(wildcard res/*.res)

endif

$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(INCL) $(LIB) $(RES) -o $(PROGDIR)$(MAIN) $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) $(INCL) $(LIB) -c $< -o $@

debug: $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(INCL) $(LIB) $(RES) -o $(PROGDIR)$(MAIN) $^ $(LIBS)