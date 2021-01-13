//#include "./minilibx-linux/mlx.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include "include/cub3d.h"
#include "Libft/libft.h"

void struct_ini(tools *tool)
{
	tool->res_x = 1920;
	tool->res_y = 1080;
	tool->pos_x = 218;
	tool->pos_y = 218;
	tool->f_color = 65280;
	tool->width = 64;
	tool->height = 64;
	tool->title = "je suis la";
	tool->keyup = 0;
	tool->keyleft = 0;
	tool->keydown = 0;
	tool->keyright = 0;
	tool->mlx_ptr = mlx_init();
	tool->win_ptr = mlx_new_window(tool->mlx_ptr, tool->res_x, tool->res_y, tool->title);
	tool->img_ptr = mlx_xpm_file_to_image(tool->mlx_ptr, "eagle.xpm", &tool->width, &tool->height);
	tool->speed = 0.1;
	tool->pos_player[0] = 11;
	tool->pos_player[1] = 9;
}
/*
int apply(tools *tool) //old
{
	if (tool->speed == 2)
		tool->speed = 0;
	if (tool->keyup && tool->pos_y > 0 && tool->speed == 1)
		--tool->pos_y;
	if (tool->keyleft && tool->pos_x > 0 && tool->speed == 1)
		--tool->pos_x;
	if (tool->keydown && tool->pos_y < 986 && tool->speed == 1)
		++tool->pos_y;
	if (tool->keyright && tool->pos_x < 1856 && tool->speed == 1)
		++tool->pos_x;
	if (tool->keyup || tool->keydown || tool->keyleft || tool->keyright)
		refresh(tool);
	++tool->speed;
	return 1;
}
*/

void my_mlx_pixel_put(tools *tool, int x, int y, int color)
{
	char *dst;

	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel/8));
	*(unsigned int*)dst = color; // essayer avec (unsigned int)(*dst) = color;
}

void create_img_addr(tools *tool)
{
	tool->img_ptrnew = mlx_new_image(tool->mlx_ptr, 1920, 1080);
	tool->addr = mlx_get_data_addr(tool->img_ptrnew, &tool->bits_per_pixel, &tool->line_length, &tool->endian);
}

void create_background(tools *tool, int color)
{
	tool->pos_x = 0;
	while (tool->pos_x < 1920)
	{
		tool->pos_y = 0;
		while (tool->pos_y < 1080)
		{
			my_mlx_pixel_put(tool, tool->pos_x, tool->pos_y, color);
			++tool->pos_y;
		}
		++tool->pos_x;
	}
}

void coloring_spaces(tools *tool, int x, int y, int case_len)
{
	int color;
	int i;
	int j;
	int x_temp;

	j = 0;
	x_temp = x;
	color = 0x000000FF; //BLUE
	while (j++ < case_len)
	{
		i = 0;
		x = x_temp;
		while (i++ < case_len && y <= tool->res_y && x <= tool->res_x)
		{
			my_mlx_pixel_put(tool, x++, y, color);
		}
		++y;
	}
}

void coloring_one(tools *tool, int x, int y, int case_len)
{
	int color;
	int i;
	int j;
	int x_temp;

	j = 0;
	x_temp = x;
	color = 0x00FF0000; //RED
	while (j++ < case_len)
	{
		i = 0;
		x = x_temp;
		while (i++ < case_len && y <= tool->res_y && x <= tool->res_x)
		{
			my_mlx_pixel_put(tool, x++, y, color);
		}
		++y;
	}
}

void coloring_zero(tools *tool, int x, int y, int case_len)
{
	int color;
	int i;
	int j;
	int x_temp;

	j = 0;
	x_temp = x;
	color = 0x0000FA00; //GREEN
	while (j++ < case_len)
	{
		i = 0;
		x = x_temp;
		while (i++ < case_len && y <= tool->res_y && x <= tool->res_x)
		{
			my_mlx_pixel_put(tool, x++, y, color);
		}
		++y;
	}
}

void coloring_cases(tools *tool, int case_len, int max_x)
{
	int x;
	int y;
	int i;
	int j;

	y = 0;
	j = 0;
	while (j < tool->max_y)
	{
		x = 0;
		i = 0;
		while (i < max_x)
		{
			//printf("i = %d j = %d |%c|\n", i, j, tool->map[j][i]);
			if (tool->map[j][i] == ' ')
			{
				coloring_spaces(tool, x, y, case_len);
			}
			else if(tool->map[j][i] == '1')
			{
				//printf("x = %d y = %d\n", x, y);
				coloring_one(tool, x, y, case_len);
			}
			else if(tool->map[j][i] == '0')
			{
				coloring_zero(tool, x, y, case_len);
			}
			x += case_len;
			i++;
		}
		y += case_len;
		j++;
	}
}

void init_player_pos(tools *tool)
{
	tool->posy = tool->pos_player[0] + 0.5;
	tool->posx = tool->pos_player[1] + 0.5;
}

void display_player(tools *tool)
{
	double x;
	double y;
	int i;
	int j;
	int color;
	int pos_len;

	color = 0x00F5F500;
	pos_len = tool->case_len / 2;
	x = tool->posx * (double)tool->case_len;
	y = tool->posy * (double)tool->case_len;
	x = x - (0.25 * tool->case_len);
	y = y - (0.25 * tool->case_len);
	i = x + (0.5 * tool->case_len);
	j = y + (0.5 * tool->case_len);
	while (y < j)
	{
		while (x < i)
			my_mlx_pixel_put(tool, x++, y, color);
		x = x - (0.5 * tool->case_len);
		++y;
	}
}

void create_grid(tools* tool)
{
	int max_x;
	int case_len;
	int x;
	int y;
	int i;
	int j;
	int thickness;

	max_x = ft_strlen(tool->map[0]) - 1;
	case_len = tool->res_x / max_x < tool->res_y / tool->max_y ? tool->res_x / max_x : tool->res_y / tool->max_y;
	tool->case_len = case_len;
	coloring_cases(tool, case_len, max_x);
	//display_player(tool);
	y = 0;
	j = 0;
	while (y < tool->res_y)
	{
		x = 0;
		if (j == case_len)
		{
			while (x <= tool->res_x)
				my_mlx_pixel_put(tool, x++, y, 0x00000000);
			j = 0;
		}
		while (x < tool->res_x)
		{
			thickness = 2;
			while (thickness-- > 0 )
				my_mlx_pixel_put(tool, x++, y, 0x00000000);
			i = 0;
			while (i++ < (case_len - 2))
				++x;
		}
		++y;
		++j;
	}
}
/*
int resize(tools *tool) //old
{
	mlx_get_screen_size(tool->mlx_ptr, &tool->res_x, &tool->res_y);
	tool->win_ptr = mlx_new_window(tool->mlx_ptr, tool->res_x, tool->res_y, tool->title);
	return (1);
}
*/

void move_forward(tools *tool)
{
	printf("tool->posy = %f sin(tool->dir) = %f tool->speed = %f\n", tool->posy, sin(tool->dir), tool->speed);
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
	printf("%f", sin(tool->dir));
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

void	refresh(tools *tool) //old
{
	//mlx_clear_window(tool->mlx_ptr, tool->win_ptr);
	mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptrnew, (tool->pos_x - 64), (tool->pos_y - 64));
	mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptr, tool->pos_x, tool->pos_y);
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
		printf("dir = %f\n", tool->dir);
		create_grid(tool);
		display_player(tool);
		mlx_put_image_to_window(tool->mlx_ptr, tool->win_ptr, tool->img_ptrnew, 0, 0);
		printf("x = %f y = %f\n", tool->posx, tool->posy);
		//refresh(tool);
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
	printf("je suis dans press et le keycode est %d\n", keycode);
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
	struct_ini(&tool);
	if (get_map_param(av[1], &tool))
	{
		printf("tous les parametres sont bons\n");
	}
	else
		printf("error\n");

	/////get_position(worldMap, mapWidth, position);
	/////printf("x = %d, y = %d\n", position[1], position[0]);

	//refresh(&tool);
	create_img_addr(&tool);
	create_background(&tool, tool.c_color);
	init_player_pos(&tool);
	create_grid(&tool);
	display_player(&tool);
	mlx_put_image_to_window(tool.mlx_ptr, tool.win_ptr, tool.img_ptrnew, 0, 0);
	mlx_hook(tool.win_ptr, 2, 1L<<0, press, &tool);
	mlx_hook(tool.win_ptr, 3, 1L<<1, release, &tool);
	//////mlx_hook(tool->win_ptr, 25, 1L<<18, resize, tool);
	//////mlx_loop_hook(tool->mlx_ptr, apply, tool);
	mlx_loop(tool.mlx_ptr);
	return 0;
}