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
	*(unsigned int*)dst = color; // essayer avec (unsigned int)(*dst) = color;
}

void create_img_addr(tools *tool)
{
	tool->img_ptrnew = mlx_new_image(tool->mlx_ptr, tool->res_x, tool->res_y);
	tool->addr = mlx_get_data_addr(tool->img_ptrnew, &tool->bits_per_pixel, &tool->line_length, &tool->endian);
}

void init_player_pos(tools *tool)
{
	tool->posy = tool->pos_player[0] + 0.5;
	tool->posx = tool->pos_player[1] + 0.5;
}

void draw_column(double height, int column, int len_column, tools *tool)
{
	int x;
	int y;
	int i;
	int color;

	i = -1;
	x = column;
	//printf("column = %d\n" , column);
	if (sin(tool->dir) > 0)
	{
		if (cos(tool->dir) > 0)
			color = 0x00C70039;
		else
			color = 0x0058D68D;
	}
	else
	{
		if (cos(tool->dir) > 0)
			color = 0x007D3C98;
		else
			color = 0x007D3C98;
	}
	
	while (x < column + len_column && x <= tool->res_x)
	{
		y = 0;
		while (++i < (tool->res_y - height) / 2)
		{
			my_mlx_pixel_put(tool, x, y++, 0x00000000);
		}
		i = -1;
		while (++i < height && i < tool->res_y)
		{
			my_mlx_pixel_put(tool, x, y++, color);
		}
		i = -1;
		while (y < tool->res_y)//tool->res_y - heigh) / 2)
		{
			my_mlx_pixel_put(tool, x, y++, 0x00000000);
		}
		++x;
	}
	y = -1;
	--x;
	while (++y < tool->res_y)
		my_mlx_pixel_put(tool, x, y, 0x00000000);
}

int calculate_height(double vec_x, double vec_y, tools *tool)
{
	double dist;
	double height;

	//printf("x = %f y = %f x + y = %f\n", vec_x, vec_y, vec_x + vec_y);
	dist = sqrt(vec_x * vec_x + vec_y * vec_y);
	printf("dist = %f raydir = %f ", dist, tool->ray_dir);
	dist = dist * cos(fabs(tool->ray_dir));
	height = (tool->res_y * 31)/ dist;
	//printf("height = %f\n", height);
	return (height);
}

int hit_column(tools *tool, int column)
{
	double t;
	double y;
	int i;
	int j;

	t = (column - tool->pos_x) / cos(tool->dir); //pour la colonne
	y = tool->pos_y - sin(tool->dir) * t;
	i = column;
	j = (int)y;
	if ((sin(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')) || (sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')))
		return (1);
	return (0);
}

int hit_row(tools *tool, int row)
{
	double t;
	double x;
	int i;
	int j;

	t = (row - tool->pos_y) / (-1 * sin(tool->dir)); // pour la row
	x = tool->pos_x + cos(tool->dir) * t;
	i = (int)x;
	j = row;
	if ((sin(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')) || (sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')))
		return (1);
	return (0);
}

void new_calcul(tools *tool)
{
	int column;
	int row;
	int hit;

	hit = 0;
	column = (int)tool->pos_x;
	row = (int)tool->pos_y;
	while (1)
	{
		if (hit_column(tool, column))
			hit = 1;
		if (cos(tool->dir) > 0)
		{
			column++;
		}
		else
		{
			column--;
		}
		if (hit_row(tool, row))
			hit = 2;
		if (sin(tool->dir) > 0)
		{
			row--;
		}
		else
		{
			row++;
		}
	}
}

void calculate_dist(int column, int len_column, tools *tool)
{
	double x;
	double y;
	int i;
	int j;
//debut du ctrl z
	x = tool->posx * 31;
	y = tool->posy * 31;
	while (1)
	{
		x = x + cos(tool->dir);
		y = y - sin(tool->dir);
		i = x / 31;
		j = y / 31;
		if ((sin(tool->dir) > 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')) || (sin(tool->dir) < 0 && (tool->map[j][i] == '1' || tool->map[j][i] == ' ')))
		{
			printf("y = %f i = %d res = %d\n", y, j, 31);
			if ((int)x - 30== i * 31)
				x = (int)x;
			if ((int)y - 30== j * 31)
				y = (int)y;
			break ;
		}
	}
	//printf("i = %d j= %d\n", i, j);
	x = x - (tool->posx * 31);
	y = y - (tool->posy * 31);
	draw_column(calculate_height(x, y, tool), column, len_column, tool);
}

void raycasting(tools *tool) //display_angle
{
	double olddir;
	int column;
	int len_column;

	olddir = tool->dir;
	tool->dir = olddir + 0.6;
	column = 0;
	len_column = tool->res_x / (1.2/0.005);
	tool->ray_dir = 0.6;
	while (tool->dir > olddir - 0.6)
	{
		calculate_dist(column, len_column, tool);
		tool->dir -= 0.005;
		tool->ray_dir -= 0.005;
		column += len_column;
	}
	tool->dir = olddir;
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
	if (keycode == 123)
		tool->rotate_left = 1;
	if (keycode == 124)
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
	if (keycode == 123)
		tool->rotate_left = 0;
	if (keycode == 124)
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