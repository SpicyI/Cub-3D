CC = cc
CFLAGS =  -Wall -Werror -Wextra #-fsanitize=address -g3
MLX_FLAGS= -lmlx -framework OpenGL -framework AppKit -pthread 

NAME = cub3D
EXT = .c
SRCDIR = ./SRC
MLXLIB = mlx/libmlx.a
OBJDIR = obj
OBJ_DIR= mkdir -p obj

SRC = $(wildcard $(SRCDIR)/*$(EXT)) $(wildcard $(SRCDIR)/tools/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm -rf
DELOBJ = $(OBJ)

all: $(NAME)


$(NAME): $(OBJ)
	make -C mlx
	$(CC) $(OBJ) -o $(NAME) $(MLXLIB) $(CFLAGS) $(MLX_FLAGS) -I mlx/mlx.h

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) 
	$(OBJ_DIR)
	$(CC) $(CFLAGS)   -o $@ -c $<

.PHONY: clean
clean: 
	$(RM) $(DELOBJ) $(OBJDIR)
.PHONY: fclean
fclean: clean
	make clean -C mlx
	$(RM) $(NAME)
.PHONY: re
re: fclean all