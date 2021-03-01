/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:25:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 16:52:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"

typedef struct
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr_no;
	void	*img_ptr_so;
	void	*img_ptr_ea;
	void	*img_ptr_we;
	void	*img_ptr_sp;
	void	*texture;
	void	*img_ptrnew;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*sprite_path;
	int		sprite_col;
	int		sprite_row;
	char	**map;
	int		res_x;
	int		res_y;
	int		f_color;
	int		c_color;
	int		width;
	int		height;
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
	char	*addr;
	char	*addr_texture;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		bits_per_pixel_2;
	int		line_length_2;
	int		endian_2;
	int		max_y;
	int		case_len;
	int		rotate_left;
	int		rotate_right;
	double	ray_dir;
	double	hit[3];
}			t_tools;

typedef struct
{
	int		x_src;
	int		y_src;
	int		x_dest;
	int		y_dest;
	int		color;
	double	fx;
	double	fy;
	int		width;
	int		a;
}			t_calcul;

int				get_next_line(int fd, char **line);
void			ft_header(tools *tool, int fd);
void			save_screen(tools *tool, char *option);
int				quit(tools *tool);
void			free_params(char **params);
int				check_path_format(char *path);
double			get_dist_sprite(tools *tool, double *hit_x, double hit_y);
double			hit_row_sprite(tools *tool, int row, double *hit_x);
void			hit_row_sprite_2(tools *tool, int i, int j, double *hit_x);
double			hit_column_sprite(tools *tool, int column, double *hit_y);
void			hit_column_sprite_2(tools *tool, int i, int j, double *hit_y);
void			hit_sprite(tools *tool, int i, int j);
void			rotate_sprite(tools *tool, int i, int j);
void			rotate_right(tools *tool);
void			rotate_left(tools *tool);
void			check_sprite(tools *tool);
void			raycasting(tools *tool, int sprite);
void			new_calcul(tools *tool, int col, int sprite);
double			hit_row(tools *tool, int row, double *hit_x);
double			hit_column(tools *tool, int column, double *hit_y);
void			get_texture(tools *tool, int hit, int sprite);
void			draw_column(double height, int col, double hit_x, tools *tool);
void			get_img(tools *tool, int x, int *y, double height);
unsigned int	get_pixel(tools *tool, int x, int y);
void			my_mlx_pixel_put(tools *tool, int x, int y, int color);
void			move_right(tools *tool);
void			move_left(tools *tool);
void			move_backward(tools *tool);
void			move_forward(tools *tool);
int				main(int ac, char *av[]);
int				release(int keycode, tools *tool);
int				press(int keycode, tools *tool);
void			move_player(tools *tool);
void			init_player_pos(tools *tool);
void			create_img_addr(tools *tool);
void			init_window(tools *tool);
void			init_param(tools *tool);
int				hit_right(tools *tool);
int				hit_left(tools *tool);
int				hit_down(tools *tool);
int				hit_up(tools *tool);
int				hit_west(tools *tool);
int				hit_east(tools *tool);
int				hit_south(tools *tool);
int				hit_north(tools *tool);
double			get_dist(tools *tool, double *hit_x, double hit_y);
double			dist(tools *tool, double x, double y);
double			ft_round(double n);
int				ft_pair(double n);
void			struct_init(tools *tool);
void			ft_error(int a);
int				check_path_format(char *path);
int				get_north_texture(char **no_texture, tools *tool);
int				get_south_texture(char **so_texture, tools *tool);
int				get_east_texture(char **ea_texture, tools *tool);
int				get_west_texture(char **we_texture, tools *tool);
int				get_sprite(char **sprite, tools *tool);
int				get_rgb(char *colors);
int				get_ground_color(char **ground, tools *tool);
int				get_top_color(char **top, tools *tool);
int				get_res(char **res, tools *tool);
int				param_check(char **params, tools *tool);
int				is_player(char c, tools *tool);
int				is_column(char **map, int max, tools *tool);
int				is_line(char *str, tools *tool);
char			*ft_strcpy_vtwo(char *dest, char *src);
char			*realloc_extended_map(char **str, int max);
int				map_check_line(char *str, tools *tool);
int				empty_line(char *str);
int				realloc_map(tools *tool);
int				check_player(tools *tool, int max_y);
int				map_master_two(int j, int max_x, tools *tool);
int				skip_empty_lines(int fd, char **line);
int				map_master(int fd, tools *tool);
int				get_map_param(char *path, tools *tool);

#endif
