NAME        := cub3D
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3

# Directories
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := inc
LIBFT_DIR   := libft
MLX_DIR     := minilibx

# Libraries
LIBFT       := $(LIBFT_DIR)/libft.a
MLX         := $(MLX_DIR)/libmlx_Linux.a
LIBS        := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# Includes
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)

# Source Files
SRC_FILES   := main.c \
               parsing/parsing.c \
               parsing/check_args.c \
               parsing/elements.c \
               parsing/map_parsing.c \
               parsing/validation.c \
               raycasting/raycasting.c \
               raycasting/init_player.c \
               rendering/rendering.c \
               utils/utils.c \
               input/input.c

SRCS        := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR) || [ -f $(MLX) ]

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
