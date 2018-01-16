AUTHOR := hmartzol
NAME := ../checker
MAIN := main.c
CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address
PINC := ../libft/inc libftx2/inc inc
CLIB := ../libft libftx2
LCLIB := libftx2/minilibx_X11
MCLIB := libftx2/minilibx_macos_sierra
LIB := ../libft/libft.a libftx2/libftx2.a
LLIB := libftx2/minilibx_X11/mlx.a
MLIB := libftx2/minilibx_macos_sierra/libmlx.a
LLARGS := -lXext -lX11
MLARGS := -framework OpenGL -framework AppKit
include ../Makefiles/Makefile.gen
