/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:47:34 by alboumed          #+#    #+#             */
/*   Updated: 2021/02/26 15:33:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
//#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include "include/cub3d.h"
#include "Libft/libft.h"

void init_param(tools *tool)
{
	tool->sprite_col = 0;
	tool->sprite_row = 0;
	tool->keyup = 0;
	tool->keyleft = 0;
	tool->keydown = 0;
	tool->keyright = 0;
	tool->rotate_right = 0;
	tool->rotate_left = 0;
	tool->speed = 0.1;
	//tool->img_ptr = mlx_xpm_file_to_image(tool->mlx_ptr, "eagle.xpm", &tool->width, &tool->height);
}

void init_window(tools *tool)
{
	tool->title = "cub3d";
	tool->mlx_ptr = mlx_init();
	tool->win_ptr = mlx_new_window(tool->mlx_ptr, tool->res_x, tool->res_y, tool->title);
}

void my_mlx_pixel_put(tools *tool, int x, int y, int color)
{
	char *dst;

	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel/8));
	*(unsigned int*)dst = color;
}

unsigned int get_pixel(tools *tool, int x, int y)
{
	char *dst;

	tool->addr_texture = mlx_get_data_addr(tool->texture, &tool->bits_per_pixel_2, &tool->line_length_2, &tool->endian_2);
	dst = tool->addr_texture + (y * tool->line_length_2 + x * (tool->bits_per_pixel_2/8));
	return (*(unsigned int*)dst);
}

void create_img_addr(tools *tool)
{
	tool->img_ptrnew = mlx_new_image(tool->mlx_ptr, tool->res_x, tool->res_y);
	tool->addr = mlx_get_data_addr(tool->img_ptrnew, &tool->bits_per_pixel, &tool->line_length, &tool->endian);
	tool->img_ptr_no = mlx_xpm_file_to_image(tool->mlx_ptr, tool->no_path, &tool->width, &tool->height); //rename height to img_height
	tool->img_ptr_so = mlx_xpm_file_to_image(tool->mlx_ptr, tool->so_path, &tool->width, &tool->height); //rename height to img_height
	tool->img_ptr_ea = mlx_xpm_file_to_image(tool->mlx_ptr, tool->ea_path, &tool->width, &tool->height); //rename height to img_height
	tool->img_ptr_we = mlx_xpm_file_to_image(tool->mlx_ptr, tool->we_path, &tool->width, &tool->height); //rename height to img_height
	tool->img_ptr_sp = mlx_xpm_file_to_image(tool->mlx_ptr, tool->sprite_path, &tool->width, &tool->height); //rename height to img_height
}

void get_img(tools *tool, int x, int *y, double height)
{
	calcul c;

	c.width = height;
	c.fx = tool->width/(double)height;
	c.fy = tool->height/(double)height;
    c.a = (int)tool->hit[2];
    c.y_dest = 0;
	c.x_dest = (tool->hit[2] - (double)c.a)  * (float)c.width;
    c.x_src = c.x_dest * c.fx;
	if (height > tool->res_y)
		c.y_dest = (height - tool->res_y) / 2;
    while (c.y_dest < height && *y < tool->res_y)
    {
        c.y_src = c.y_dest * c.fy;
        c.color = get_pixel(tool, c.x_src, c.y_src);
		if (!(tool->texture == tool->img_ptr_sp && c.color == 0x00000000))
        	my_mlx_pixel_put(tool, x, *y, c.color);
        ++c.y_dest;
		++*y;
    }
    ++c.x_dest;
}

void init_player_pos(tools *tool)
{
	tool->posy = tool->pos_player[0] + 0.5;
	tool->posx = tool->pos_player[1] + 0.5;
}

void draw_column(double height, int column, double hit_x, tools *tool)
{
	int x;
	int y;
	int i;

	i = -1;
	x = column;
	y = 0;
	tool->hit[2] = hit_x;
	while (++i < (tool->res_y - height) / 2)
	{
		my_mlx_pixel_put(tool, x, y++, tool->c_color);
	}
    get_img(tool, x, &y, height);
	while (y < tool->res_y)
	{
		my_mlx_pixel_put(tool, x, y++, tool->f_color);
	}
}

int ft_pair(double n)
{
	if (((int)n % 2) == 0)
		return (1);
	return (0);
}

double ft_round(double n)
{
	n = round(n * 1000);
	n = n/ 1000;
	return (n);
}

double dist(tools *tool, double x, double y)
{
	int a;
	int b;

	a = (int)x;
	b = (int)y;
	if ((tool->sprite_col && (double)a == x) || (tool->sprite_row && (double)b == y))
	{
		x = tool->hit[0];
		y = tool->hit[1];
	}
	x -= tool->posx;
	y -= tool->posy;
	x = x * x;
	y = y * y;
	return (sqrt(x + y));
}

void rotate_sprite(tools *tool, int i, int j)
{
	double x;
	double y;
	double t;

	x = (double)i + 0.5;
	y = (double)j + 0.5;
	t = (x - (double)i) / sin(tool->dir);
	x = x - sin(tool->dir) * t;
	y = y - cos(tool->dir) * t;
	if ((int)x == i && (int)y == (j))
	{
		tool->hit[2] = tool->hit[0];
	}
	else
	{
		tool->hit[2] = tool->hit[1];
	}
}

void hit_sprite(tools *tool, int i, int j)
{
	double x;
	double y;
	double t;

	x = (double)i + 0.5;
	y = (double)j + 0.5;
	t = (cos(tool->dir) * tool->posy - sin(tool->dir) * x + sin(tool->dir) * tool->posx - cos(tool->dir) * y) / (-1 * (cos(tool->dir) * cos(tool->dir) + sin(tool->dir) * sin(tool->dir)));
	x = x - sin(tool->dir) * t;
	y = y - cos(tool->dir) * t;
	if (x < (double)i)
	{
		tool->sprite_col = 0;
		tool->sprite_row = 0;
		return ;
	}
	tool->hit[0] = x;
	tool->hit[1] = y;
	rotate_sprite(tool, i, j);
}

void hit_column_sprite_2(tools *tool, int i, int j, double *hit_y)
{
	if ((cos(tool->dir) < 0 && tool->map[j][i - 1] == '2') || (cos(tool->dir) > 0 && tool->map[j][i] == '2'))
	{
		(cos(tool->dir) < 0 && tool->map[j][i - 1] == '2') ? --i : 1;
		tool->sprite_col = 1;
		hit_sprite(tool, i, j);
		*hit_y = tool->hit[2];
	}
}

double hit_column_sprite(tools *tool, int column, double *hit_y)
{
	double t;
	double y;
	int i;
	int j;

	i = -5;
	tool->sprite_col = 0;
	cos(tool->dir) > 0 ? column : column++;
	while (i == -5 || !((cos(tool->dir) < 0 && (tool->map[j][i - 1] == '1' || tool->map[j][i - 1] == ' ' || tool->map[j][i - 1] == '2')) || (cos(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ' || tool->map[j][i] == '2'))))
	{
		cos(tool->dir) > 0 ? column++ : column--;
		t = (column - tool->posx) / cos(tool->dir);
		y = tool->posy - sin(tool->dir) * t;
		if (y > tool->max_y || y < 0)
			return (-1);
		i = column;
		j = (int)y;
	}
	hit_column_sprite_2(tool, i, j, hit_y);
	return (dist(tool, column, y));
}

double hit_column(tools *tool, int column, double *hit_y)
{
	double t;
	double y;
	int i;
	int j;

	i = -5;
	tool->sprite_col = 0;
	cos(tool->dir) > 0 ? column : column++;
	while (i == -5 || !((cos(tool->dir) < 0 && (tool->map[j][i - 1] == '1' || tool->map[j][i - 1] == ' ')) || (cos(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' '))))
	{
		cos(tool->dir) > 0 ? column++ : column--;
		t = (column - tool->posx) / cos(tool->dir);
		y = tool->posy - sin(tool->dir) * t;
		if (y > tool->max_y || y < 0)
			return (-1);
		i = column;
		j = (int)y;
	}
	*hit_y = y;
	return (dist(tool, column, y));
}

void hit_row_sprite_2(tools *tool, int i, int j, double *hit_x)
{
	if ((sin(tool->dir) > 0 && tool->map[j - 1][i] == '2') || (sin(tool->dir) < 0 && tool->map[j][i] == '2'))
	{
		(sin(tool->dir) > 0 && tool->map[j - 1][i] == '2') ? --j : 1;
		tool->sprite_row = 1;
		hit_sprite(tool, i, j);
		*hit_x = tool->hit[2];
	}
}

double hit_row_sprite(tools *tool, int row, double *hit_x)
{
	double t;
	double x;
	int i;
	int j;

	i = -5;
	tool->sprite_row = 0;
	sin(tool->dir) > 0 ? row++ : row;
	while (i == -5 || !((sin(tool->dir) > 0 && (tool->map[j - 1][i] == '1' || tool->map[j - 1][i] == ' ' || tool->map[j - 1][i] == '2')) || (sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ' || tool->map[j][i] == '2'))))
	{
		sin(tool->dir) > 0 ? row-- : row++;
		t = (row - tool->posy) / (-1 * sin(tool->dir));
		x = tool->posx + cos(tool->dir) * t;
		if (x > ft_strlen(tool->map[0]) || x < 0)
			return (-1);
		i = (int)x;
		j = row;
	}
	hit_row_sprite_2(tool, i, j, hit_x);
	return (dist(tool, x, row));
}

double hit_row(tools *tool, int row, double *hit_x)
{
	double t;
	double x;
	int i;
	int j;

	i = -5;
	tool->sprite_row = 0;
	sin(tool->dir) > 0 ? row++ : row;
	while (i == -5 || !((sin(tool->dir) > 0 && (tool->map[j - 1][i] == '1' || tool->map[j - 1][i] == ' ')) || (sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' '))))
	{
		sin(tool->dir) > 0 ? row-- : row++;
		t = (row - tool->posy) / (-1 * sin(tool->dir));
		x = tool->posx + cos(tool->dir) * t;
		if (x > ft_strlen(tool->map[0]) || x < 0)
			return (-1);
		i = (int)x;
		j = row;
	}
	*hit_x = x;
	return (dist(tool, x, row));
}

void get_texture(tools *tool, int hit, int sprite)
{
	int column;
	int row;

	column = 0;
	row = 1;
	if (hit == column && !sprite)
	{
		if (cos(tool->dir) > 0)
			tool->texture = tool->img_ptr_ea;
		else
			tool->texture = tool->img_ptr_we; //we_path
	}
	else if (hit == row && !sprite)
	{
		if (sin(tool->dir) > 0)
			tool->texture = tool->img_ptr_no;
		else
			tool->texture = tool->img_ptr_so;
	}
	else if (sprite)
		tool->texture = tool->img_ptr_sp;
}

double get_dist_sprite(tools *tool, double *hit_x, double hit_y)
{
	double dist;
	double dist_2;

	dist = -1;
	dist_2 = -1;
	if (ft_round(cos(tool->dir)) != 0)
		dist = hit_column_sprite(tool, (int)tool->posx, &hit_y);
	if (ft_round(sin(tool->dir)) != 0)
		dist_2 = hit_row_sprite(tool, (int)tool->posy, hit_x);
	if (dist != -1 && (dist < dist_2 || dist_2 == -1) && tool->sprite_col)
	{
		*hit_x = hit_y;
		get_texture(tool, 0, tool->sprite_col);
	}
	else if (dist_2 != -1 && (dist_2 < dist || dist == -1) && tool->sprite_row)
	{
		dist = dist_2;
		get_texture(tool, 1, tool->sprite_row);
	}
	else
		dist = -1;
	return (dist);
}

double get_dist(tools *tool, double *hit_x, double hit_y)
{
	double dist;
	double dist_2;

	dist = -1;
	dist_2 = -1;
	if (ft_round(cos(tool->dir)) != 0)
		dist = hit_column(tool, (int)tool->posx, &hit_y);
	if (ft_round(sin(tool->dir)) != 0)
		dist_2 = hit_row(tool, (int)tool->posy, hit_x);
	if ((dist < dist_2 && dist != -1) || dist_2 == -1)
	{
		*hit_x = hit_y;
		get_texture(tool, 0, 0);
	}
	else
	{
		dist = dist_2;
		get_texture(tool, 1, 0);
	}
	return (dist);
}

void new_calcul(tools *tool, int col, int sprite)
{
	double dist;
	double height;
	double hit_x;
    double hit_y;

	hit_y = 0;
	if (!sprite)
	{
		dist = get_dist(tool, &hit_x, hit_y);
		dist = dist * cos(fabs(tool->ray_dir));
	}
	else
	{
		dist = get_dist_sprite(tool, &hit_x, hit_y);
	}
	if (dist == -1)
		return ;
	height = (tool->res_y * (tool->res_x / tool->res_y)) / dist;
	draw_column(height, col, hit_x, tool);
}

void raycasting(tools *tool, int sprite) //display_angle
{
	double one_ray;
	double temp;
	int column;

	column = 0;
	temp = tool->dir;
	tool->dir += 0.5;
	one_ray = 1.0 / tool->res_x;
	tool->ray_dir = 0.5;
	while (column < tool->res_x)
	{
		new_calcul(tool, column, sprite);
		tool->dir -= one_ray;
		tool->ray_dir -= one_ray;
		++column;
	}
	tool->dir = temp;
}

void check_sprite(tools *tool)
{
	int sprite;

	sprite = 1;
	raycasting(tool, sprite);
}

void move_forward(tools *tool)
{
	//printf("tool->posy = %f sin(tool->dir) = %f tool->speed = %f\n", tool->posy, sin(tool->dir), tool->speed);
	tool->posy -= (sin(tool->dir) * tool->speed);
	tool->posx += (cos(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void move_backward(tools *tool)
{
	tool->posy += (sin(tool->dir) * tool->speed);
	tool->posx -= (cos(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void move_left(tools *tool)
{
	tool->posy -= (cos(tool->dir) * tool->speed);
	tool->posx -= (sin(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void move_right(tools *tool)
{
	tool->posy += (cos(tool->dir) * tool->speed);
	tool->posx += (sin(tool->dir) * tool->speed);
	tool->pos_player[0] = (int)tool->posx;
	tool->pos_player[1] = (int)tool->posy;
}

void rotate_left(tools *tool)
{
	tool->dir += tool->speed;
}

void rotate_right(tools *tool)
{
	tool->dir -= tool->speed;
}

int hit_north(tools *tool)
{
	int x;
	int y;

	y = (int)tool->posy;
	x = (int)tool->posx;

	if (tool->map[y - 1][x] == '1')
	{
		if ((tool->posy - tool->speed) <= (y))
			return (1);
	}
	return (0);
}

int hit_south(tools *tool)
{
	int x;
	int y;

	y = (int)tool->posy;
	x = (int)tool->posx;
	if (tool->map[y + 1][x] == '1')
	{
		if ((tool->posy + tool->speed) >= (y + 1))
			return (1);
	}
	return (0);
}

int hit_east(tools *tool)
{
	int x;
	int y;

	y = (int)tool->posy;
	x = (int)tool->posx;
	if (tool->map[y][x + 1] == '1')
	{
		if ((tool->posx + tool->speed) >= (x + 1))
			return (1);
	}
	return (0);
}

int hit_west(tools *tool)
{
	int x;
	int y;

	y = (int)tool->posy;
	x = (int)tool->posx;
	if (tool->map[y][x - 1] == '1')
	{
		if ((tool->posx - tool->speed) <= (x))
			return (1);
	}
	return (0);
}

int hit_up(tools *tool)
{
	int i;

	i = 0;
	if (sin(tool->dir) > 0)
		i = hit_north(tool);
	else if (sin(tool->dir) < 0)
		i = hit_south(tool);
	if (cos(tool->dir) > 0)
		i = i | hit_east(tool);
	else if (cos(tool->dir) < 0)
		i = i | hit_west(tool);
	return (i);
}

int hit_down(tools *tool)
{
	int i;

	i = 0;
	if (sin(tool->dir) < 0)
		i = hit_north(tool);
	else if (sin(tool->dir) > 0)
		i = hit_south(tool);
	if (cos(tool->dir) < 0)
		i = i | hit_east(tool);
	else if (cos(tool->dir) > 0)
		i = i | hit_west(tool);
	return (i);
}

int hit_left(tools *tool)
{
	int i;

	i = 0;
	if (cos(tool->dir) > 0)
		i = hit_north(tool);
	else if (cos(tool->dir) < 0)
		i = hit_south(tool);
	if (sin(tool->dir) < 0)
		i = i | hit_east(tool);
	else if (sin(tool->dir) > 0)
		i = i | hit_west(tool);
	return (i);
}

int hit_right(tools *tool)
{
	int i;

	i = 0;
	if (cos(tool->dir) < 0)
		i = hit_north(tool);
	else if (cos(tool->dir) > 0)
		i = hit_south(tool);
	if (sin(tool->dir) > 0)
		i = i | hit_east(tool);
	else if (sin(tool->dir) < 0)
		i = i | hit_west(tool);
	return (i);
}

void move_player(tools *tool)
{
	if (tool->keyup && !hit_up(tool))
		move_forward(tool);
	if (tool->keyleft && !hit_left(tool))
		move_left(tool);
	if (tool->keydown && !hit_down(tool))
		move_backward(tool);
	if (tool->keyright && !hit_right(tool))
		move_right(tool);
	if (tool->rotate_left)
		rotate_left(tool);
	if (tool->rotate_right)
		rotate_right(tool);
	if (tool->keyup || tool->keydown || tool->keyleft || tool->keyright || tool->rotate_left || tool->rotate_right)
	{
		raycasting(tool, 0);
		check_sprite(tool);
		mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptrnew, 0, 0);
		//printf("x = %f y = %f\n", tool->posx, tool->posy);
	}
}

int 	press(int keycode, tools *tool) //old
{
	if (keycode == 65307)
		quit(tool);
	if (keycode == 122) //13 122
		tool->keyup = 1;
	if (keycode == 113) //0 113
		tool->keyleft = 1;
	if (keycode == 115) //1 115
		tool->keydown = 1;
	if (keycode == 100) //2 100
		tool->keyright = 1;
	if (keycode == 65361) //123 65361
		tool->rotate_left = 1;
	if (keycode == 65363) //124 65363
		tool->rotate_right = 1;
	move_player(tool);
	//printf("je suis dans press et le keycode est %d\n", keycode);
	return 1;
}

int		release(int keycode, tools *tool) //old
{
	if (keycode == 122) //13 122
		tool->keyup = 0;
	if (keycode == 113) //0 113
		tool->keyleft = 0;
	if (keycode == 115) //1 115
		tool->keydown = 0;
	if (keycode == 100) //2 100
		tool->keyright = 0;
	if (keycode == 65361) //123 65361
		tool->rotate_left = 0;
	if (keycode == 65363) //124 65363
		tool->rotate_right = 0;
	printf("keyrelease %d\n", keycode);
	return 1;
}

int quit(tools *tool)
{
	int i;

	i = -1;
	while(++i <= tool->max_y)
	{
		free(tool->map[i]);
	}
	free(tool->map);
	free(tool->no_path);
	free(tool->so_path);
	free(tool->we_path);
	free(tool->ea_path);
	free(tool->sprite_path);
	// while (1)
	// 	;
	exit(0);
	return (0);
}
void	ft_header(tools *tool, int fd)
{
  int	tmp;

  write(fd, "BM", 2);
  tmp = 14 + 40 + 4 * tool->res_x * tool->res_y;
  write(fd, &tmp, 4);
  tmp = 0;
  write(fd, &tmp, 2); 
  write(fd, &tmp, 2); 
  tmp = 54;
  write(fd, &tmp, 4);
  tmp = 40;
  write(fd, &tmp, 4);
  write(fd, &tool->res_x, 4);
  write(fd, &tool->res_y, 4);
  tmp = 1;
  write(fd, &tmp, 2);
  write(fd, &tool->bits_per_pixel, 2);
  tmp = 0;
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
}
void save_screen(tools *tool, char *option)
{
	int fd;
	int x;
	int y;

	x = -1;
	y = -1;
	if (ft_strcmp(option, "--save"))
		return ;
	if ((fd = open("capture.bmp", O_CREAT | O_RDWR)) == -1)
		return ;
	ft_header(tool, fd);
	// while (++x < tool->res_x)
	// {
	// 	y = -1;
	// 	while (++y < tool->res_y)
	// 	{
	// 		write(fd, tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel/8)), 4);
	// 	}
	// }
	write(fd, tool->addr, ((tool->res_y - 1) * tool->line_length + (tool->res_x - 1) * (tool->bits_per_pixel/8)));
	close(fd);
	system("chmod 777 capture.bmp");
}

int main(int ac, char *av[])
{
	tools tool;

	(void)(ac);
	if (get_map_param(av[1], &tool))
	{
		printf("tous les parametres sont bons\n");
	}
	else
	{
		printf("error\nparameters error");
		return (0);
	}

	init_param(&tool);
	init_window(&tool);
	create_img_addr(&tool);
	init_player_pos(&tool);
	raycasting(&tool, 0);
	check_sprite(&tool);
	if (av[2])
		save_screen(&tool, av[2]);
	// mlx_hook(tool.win_ptr, 17, 0L, quit, &tool);
	mlx_put_image_to_window(tool.mlx_ptr, tool.win_ptr, tool.img_ptrnew, 0, 0);
	mlx_hook(tool.win_ptr, 33, 1L << 17, quit, &tool);
	mlx_hook(tool.win_ptr, 2, 1L<<0, press, &tool);
	mlx_hook(tool.win_ptr, 3, 1L<<1, release, &tool);
	mlx_loop(tool.mlx_ptr);
	return 0;
}