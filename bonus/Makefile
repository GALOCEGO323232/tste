# ============================================================================ #
#                                   COLORS                                     #
# ============================================================================ #

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

# ============================================================================ #
#                                   CONFIG                                     #
# ============================================================================ #

NAME		= cub3D
NAME_BONUS	= cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -rf

# ============================================================================ #
#                                 DIRECTORIES                                  #
# ============================================================================ #

SRC_DIR			= src
SRC_BONUS_DIR	= src_bonus
OBJ_DIR			= obj
OBJ_BONUS_DIR	= obj_bonus
INC_DIR			= includes
LIBFT_DIR		= libft
MLX_DIR			= minilibx

# ============================================================================ #
#                                  LIBRARIES                                   #
# ============================================================================ #

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a

LIBS		= -L$(LIBFT_DIR) -lft \
			  -L$(MLX_DIR) -lmlx_Linux \
			  -lXext -lX11 -lm

INCLUDES	= -I$(INC_DIR) \
			  -I$(LIBFT_DIR)/include \
			  -I$(MLX_DIR)

# ============================================================================ #
#                                SOURCE FILES                                  #
# ============================================================================ #

# Arquivos MANDATORY
SRC_FILES	= core/main.c \
			  core/error.c \
			  init/init.c \
			  parsing/parser.c \
			  parsing/args.c \
			  parsing/elements.c \
			  parsing/rgb.c \
			  parsing/map.c \
			  parsing/map_convert.c \
			  parsing/validation.c \
			  parsing/validation_utils.c \
			  parsing/validation_walls.c \
			  parsing/validation_walls_utils.c \
			  raycasting/raycast.c \
			  raycasting/dda.c \
			  raycasting/draw.c \
			  raycasting/player.c \
			  rendering/textures.c \
			  rendering/render.c \
			  rendering/pixel.c \
			  input/events.c \
			  input/movement.c \
			  input/rotation.c \
			  cleanup/cleanup.c \
			  cleanup/cleanup_helper.c

# Arquivos BONUS
SRC_BONUS_FILES	= core/main_bonus.c \
				  core/error_bonus.c \
				  init/init_bonus.c \
				  parsing/parser_bonus.c \
				  parsing/args_bonus.c \
				  parsing/elements_bonus.c \
				  parsing/rgb_bonus.c \
				  parsing/map_bonus.c \
				  parsing/map_convert_bonus.c \
				  parsing/validation_bonus.c \
				  parsing/validation_utils_bonus.c \
				  parsing/validation_walls_bonus.c \
				  parsing/validation_walls_utils_bonus.c \
				  parsing/door_parser_bonus.c \
				  parsing/sprite_parser_bonus.c \
				  raycasting/raycast_bonus.c \
				  raycasting/dda_bonus.c \
				  raycasting/draw_bonus.c \
				  raycasting/player_bonus.c \
				  raycasting/sprite_bonus.c \
				  raycasting/sprite_draw_bonus.c \
				  raycasting/sprite_sort_bonus.c \
				  rendering/textures_bonus.c \
				  rendering/render_bonus.c \
				  rendering/pixel_bonus.c \
				  rendering/minimap_bonus.c \
				  rendering/door_bonus.c \
				  input/events_bonus.c \
				  input/movement_bonus.c \
				  input/rotation_bonus.c \
				  input/mouse_bonus.c \
				  cleanup/cleanup_bonus.c \
				  cleanup/cleanup_helper_bonus.c \
				  cleanup/cleanup_free_bonus.c \
				  bonus/collision_bonus.c \
				  bonus/animation_bonus.c \
				  bonus/door_system_bonus.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

SRCS_BONUS	= $(addprefix $(SRC_BONUS_DIR)/, $(SRC_BONUS_FILES))
OBJS_BONUS	= $(patsubst $(SRC_BONUS_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(SRCS_BONUS))

HEADERS		= $(INC_DIR)/cub3d.h \
			  $(INC_DIR)/structs.h \
			  $(LIBFT_DIR)/include/libft.h \
			  $(MLX_DIR)/mlx.h

HEADERS_BONUS = $(INC_DIR)/cub3d_bonus.h \
				$(INC_DIR)/structs_bonus.h \
				$(LIBFT_DIR)/include/libft.h \
				$(MLX_DIR)/mlx.h

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJS_BONUS)
	@echo "$(CYAN)Linking $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "$(GREEN)✓ $(NAME_BONUS) compiled successfully!$(RESET)"

# Compilação dos objetos MANDATORY
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilação dos objetos BONUS
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilar libft
$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft ready$(RESET)"

# Compilar minilibx
$(MLX):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)✓ minilibx ready$(RESET)"

# Limpar objetos
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✓ Clean complete$(RESET)"

# Limpar tudo
fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Full clean complete$(RESET)"

# Recompilar tudo
re: fclean all

# ============================================================================ #
#                                  PHONY                                       #
# ============================================================================ #

.PHONY: all bonus clean fclean re
