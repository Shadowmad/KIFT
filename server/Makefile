HTTPSERV = httpServer
AUDISERV = audioServer

CC = gcc
CFLAGS =
DEBUG = -g

SRC_PATH = ./src/
EXE_PATH = ./bin/
INCLUDE_PATH = ./include/
LIBFT_PATH = ./libft/
OBJ_PATH = ./obj/

BREW = $(HOME)/.brew
BREW_INCLUDE = $(BREW)/include
POCKETSPHINX = $(BREW_INCLUDE)/pocketsphinx
SPHINXBASE = $(BREW_INCLUDE)/sphinxbase
POCKETSPHINX_FLAGS = `pkg-config --cflags --libs pocketsphinx sphinxbase`
MODELDIR = \"./models\"
OPENSSL = $(BREW)/opt/openssl/include/

SRC_NAME = httpServer.c helper.c

SRC = $(patsubst %, $(SRC_PATH)%, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(patsubst %, $(OBJ_PATH)%, $(OBJ_NAME))
# pocketsphinx_connection.c
ASRC_NAME = audioServer.c config.c

ASRC = $(patsubst %, $(SRC_PATH)%, $(ASRC_NAME))
AOBJ_NAME = $(ASRC_NAME:.c=.o)
AOBJ = $(patsubst %, $(OBJ_PATH)%, $(AOBJ_NAME))

all: $(HTTPSERV) $(AUDISERV)

$(HTTPSERV): $(OBJ)
	$(CC) -o $@ $(POCKETSPHINX_FLAGS) -lwebsockets $(DEBUG) $^ -I $(INCLUDE_PATH) 
	@mkdir -p $(EXE_PATH)
	@cp $(HTTPSERV) $(EXE_PATH)
	@echo "HTTPSERV is built"

$(AUDISERV): $(AOBJ)
	$(CC) $(POCKETSPHINX_FLAGS) -DMODELDIR=$(MODELDIR) -lwebsockets -o $@ $(DEBUG) $^ -I $(INCLUDE_PATH)
	@mkdir -p $(EXE_PATH)
	@cp $(AUDISERV) $(EXE_PATH)
	@echo "AUDISERV is built"

# $(AOBJ): $(ASRC)
# 	$(CC) -c $(POCKETSPHINX_FLAGS) -DMODELDIR=$(MODELDIR) -I $(OPENSSL) -I $(INCLUDE_PATH) -lwebsockets $< -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) -o $@ $(POCKETSPHINX_FLAGS) -DMODELDIR=$(MODELDIR) -lwebsockets $(DEBUG) -c $< -I $(INCLUDE_PATH) -I $(BREW_INCLUDE) -I $(OPENSSL)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(HTTPSERV) $(AUDISERV)
	@rm -rf $(EXE_PATH)

re: fclean all

.PHONY: clean fclean
