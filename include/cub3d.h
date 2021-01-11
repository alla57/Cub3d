#ifndef CUB3D_H

# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
//#include "../minilibx-linux/mlx.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include "../minilibx-mac-osx/mlx.h"
//#include "get_next_line.h"
#include "../Libft/libft.h"

int		get_next_line(int fd, char **line);

typedef struct
{
	void    *mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_ptrnew;//////////// a supprimer plus tard
	void	*img_ptrnew2; //// a supprimer
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*sprite_path;
	char	**map;
	int		res_x;
	int		res_y;
	int		f_color;
	int		c_color;
	int		width; // a supprimer
	int		height; //a supprimer
	char	*title;
	int		keyup;
	int		keyleft;
	int		keydown;
	int		keyright;
	double	speed;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	time;
	double	oldtime;
	int		pos_player[2];
	double	dir;
	int pos_x; //a supprimer
	int pos_y; //a supprimer
	char *addr;
	char *addr2; //a supprimer
	int bits_per_pixel;
	int bits_per_pixel2; //a supprimer
	int line_length;
	int line_length2; //a supprimer
	int endian;
	int endian2; //a supprimer
	int max_y;
	int case_len;
}tools;

void	struct_init(tools *tool);
void	ft_error(int a);
int		check_path_format(char *path);
int		get_north_texture(char **no_texture, tools *tool);
int		get_south_texture(char **so_texture, tools *tool);
int		get_east_texture(char **ea_texture, tools *tool);
int		get_west_texture(char **we_texture, tools *tool);
int		get_sprite(char **sprite, tools *tool);
int		get_rgb(char *colors);
int		get_ground_color(char **ground, tools *tool);
int		get_top_color(char **top, tools *tool);
int		get_res(char **res, tools *tool);
int		param_check(char **params, tools *tool);
int		is_player(char c, tools *tool);
int		is_column(char **map, int max, tools *tool);
int		is_line(char *str, tools *tool);
char	*ft_strcpy_vtwo(char *dest, char *src);
char	*realloc_extended_map(char **str, int max);
int		map_check_line(char *str, tools *tool);
int		empty_line(char *str);
int		realloc_map(tools *tool);
int		check_player(tools *tool, int max_y);
int		map_master_two(int j, int max_x, tools *tool);
int		skip_empty_lines(int fd, char **line);
int		map_master(int fd, tools *tool);
int		get_map_param(char *path, tools *tool);


#endif