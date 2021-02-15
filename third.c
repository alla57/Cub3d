//#include "./minilibx-linux/mlx.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include "include/cub3d.h"
#include "Libft/libft.h"

void init_param(tools *tool)
{
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
	tool->title = "Cub3d";
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
}

void get_img(tools *tool, int x, int *y, double height, double hit_x)
{
	calcul c;

	c.width = height;
	c.fx = tool->width/(double)height;
	c.fy = tool->height/(double)height;
    c.a = (int)hit_x;
    c.y_dest = 0;
	c.x_dest = (hit_x - (double)c.a)  * (float)c.width;
    c.x_src = c.x_dest * c.fx;
	if (height > tool->res_y)
		c.y_dest = (height - tool->res_y) / 2;
    while (c.y_dest < height && *y < tool->res_y)
    {
        c.y_src = c.y_dest * c.fy;
        c.color = get_pixel(tool, c.x_src, c.y_src);
        my_mlx_pixel_put(tool, x, *y, c.color);
        ++c.y_dest;
		++*y;
    }
    ++c.x_dest;
}
/*
void get_img(tools *tool, int x, int *y, double height, double hit_x)
{
	int x_src;
	int y_src;
	int x_dest;
	int y_dest;
	int color;
	double fx;
	double fy;
	int width;
    int a;

	width = height;
	fx = 64/(double)width;
	fy = 64/(double)height;
    a = (int)hit_x;
	x_dest = (hit_x - (double)a)  * (float)width;
    x_src = x_dest * fx;
    y_dest = 0;
	if (height > tool->res_y)
		y_dest = (height - tool->res_y) / 2;
    while (y_dest < height && *y < tool->res_y)
    {
        y_src = y_dest * fy;
        color = get_pixel(tool, x_src, y_src);
        my_mlx_pixel_put(tool, x, *y, color);
        ++y_dest;
		++*y;
    }
    ++x_dest;
}*/

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
	while (++i < (tool->res_y - height) / 2)
	{
		my_mlx_pixel_put(tool, x, y++, tool->c_color);
	}
    get_img(tool, x, &y, height, hit_x);
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
	x -= tool->posx;
	y -= tool->posy;
	x = x * x;
	y = y * y;
	return (sqrt(x + y));
}

double hit_column(tools *tool, int column, double *hit_y)
{
	double t;
	double y;
	int i;
	int j;

	i = -5;
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

double hit_row(tools *tool, int row, double *hit_x)
{
	double t;
	double x;
	int i;
	int j;

	i = -5;
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

void get_texture(tools *tool, int hit)
{
	int column;
	int row;

	column = 0;
	row = 1;
	if (hit == column)
	{
		if (cos(tool->dir) > 0)
			tool->texture = tool->img_ptr_ea;
		else
			tool->texture = tool->img_ptr_we; //we_path
	}
	else if (hit == row)
	{
		if (sin(tool->dir) > 0)
			tool->texture = tool->img_ptr_no;
		else
			tool->texture = tool->img_ptr_so;
	}
	return ;
}

double get_dist(tools *tool, double *hit_x, double hit_y)
{
	double dist;
	double dist_2;
	int column;
	int row;

	column = (int)tool->posx;
	row = (int)tool->posy;
	dist = -1;
	dist_2 = -1;
	if (ft_round(cos(tool->dir)) != 0)
		dist = hit_column(tool, column, &hit_y);
	if (ft_round(sin(tool->dir)) != 0)
		dist_2 = hit_row(tool, row, hit_x);
	if ((dist < dist_2 && dist != -1) || dist_2 == -1)
	{
		*hit_x = hit_y;
		get_texture(tool, 0);
	}
	else
	{
		dist = dist_2;
		get_texture(tool, 1);
	}
	return (dist);
}

void new_calcul(tools *tool, int col)
{
	double dist;
	double height;
	double hit_x;
    double hit_y;

	dist = get_dist(tool, &hit_x, hit_y);
	dist = dist * cos(fabs(tool->ray_dir));
	height = (tool->res_y * (tool->res_x / tool->res_y)) / dist;
	draw_column(height, col, hit_x, tool);
}

void raycasting(tools *tool) //display_angle
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
		new_calcul(tool, column);
		tool->dir -= one_ray;
		tool->ray_dir -= one_ray;
		++column;
	}
	tool->dir = temp;
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
	{
		move_forward(tool);
	}
	if (tool->keyleft && !hit_left(tool))
	{
		move_left(tool);
	}
	if (tool->keydown && !hit_down(tool))
	{
		move_backward(tool);
	}
	if (tool->keyright && !hit_right(tool))
	{
		move_right(tool);
	}
	if (tool->rotate_left)
	{
		rotate_left(tool);
	}
	if (tool->rotate_right)
	{
		rotate_right(tool);
	}
	if (tool->keyup || tool->keydown || tool->keyleft || tool->keyright || tool->rotate_left || tool->rotate_right)
	{
		raycasting(tool);
		//get_img(tool);
		mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptrnew, 0, 0);
		//printf("x = %f y = %f\n", tool->posx, tool->posy);
	}
}

int 	press(int keycode, tools *tool) //old
{
	if (keycode == 13) //13 122
		tool->keyup = 1;
	if (keycode == 0) //0 113
		tool->keyleft = 1;
	if (keycode == 1) //1 115
		tool->keydown = 1;
	if (keycode == 2) //2 100
		tool->keyright = 1;
	if (keycode == 123) //123 65361
		tool->rotate_left = 1;
	if (keycode == 124) //124 65363
		tool->rotate_right = 1;
	move_player(tool);
	//printf("je suis dans press et le keycode est %d\n", keycode);
	return 1;
}

int		release(int keycode, tools *tool) //old
{
	if (keycode == 13) //13 122
		tool->keyup = 0;
	if (keycode == 0) //0 113
		tool->keyleft = 0;
	if (keycode == 1) //1 115
		tool->keydown = 0;
	if (keycode == 2) //2 100
		tool->keyright = 0;
	if (keycode == 123) //123 65361
		tool->rotate_left = 0;
	if (keycode == 124) //124 65363
		tool->rotate_right = 0;
	printf("keyrelease\n");
	return 1;
}

int main(int ac, char *av[])
{
	int position[2];
	int mapWidth = 24;
	int mapHeight = 25;
	
	tools tool;

	(void)(ac);
	if (get_map_param(av[1], &tool))
	{
		printf("tous les parametres sont bons\n");
	}
	else
		printf("error\n");

	init_param(&tool);
	init_window(&tool);
	create_img_addr(&tool);
	init_player_pos(&tool);
	mlx_put_image_to_window(tool.mlx_ptr, tool.win_ptr, tool.img_ptrnew, 0, 0);
	mlx_hook(tool.win_ptr, 2, 1L<<0, press, &tool);
	mlx_hook(tool.win_ptr, 3, 1L<<1, release, &tool);
	//////mlx_hook(tool->win_ptr, 25, 1L<<18, resize, tool);
	//////mlx_loop_hook(tool->mlx_ptr, apply, tool);
	mlx_loop(tool.mlx_ptr);
	return 0;
}