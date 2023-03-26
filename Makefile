CC = cc
CFLAGS =  -Wall -Werror -Wextra -fsanitize=address -g
MLX_FLAGS= -lmlx -framework OpenGL -framework AppKit

NAME = Cub3D
EXT = .c
SRCDIR = ./SRC
HEADERS = $(wildcard ../*.h);
OBJDIR = obj
OBJ_DIR= mkdir -p obj

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm -rf
DELOBJ = $(OBJ)

all: $(NAME)


$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) $(HEADERS)
	$(OBJ_DIR)
	$(CC) $(CFLAGS)  -I .. -o $@ -c $<


.PHONY: clean
clean: 
	$(RM) $(DELOBJ) $(OBJDIR)
.PHONY: fclean
fclean: clean 
	$(RM) $(NAME)
.PHONY: re
re: fclean all