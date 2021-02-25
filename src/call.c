#include "../include/cub3d.h"
#include "../Libft/libft.h"
#include <math.h>
/*
void struct_init(tools *tool)
{
	tool->sprite_path = "";
	tool->no_path = "";
	tool->so_path = "";
	tool->ea_path = "";
	tool->we_path = "";
	tool->res_x = 1920;
	tool->res_y = 1080;
	tool->f_color = 65280;
	tool->c_color = 65280;
	tool->width = 64;
	tool->height = 64;
	tool->title = "je suis la";
	tool->keyup = 0;
	tool->keyleft = 0;
	tool->keydown = 0;
	tool->keyright = 0;
	tool->mlx_ptr = mlx_init();
	tool->win_ptr = mlx_new_window(tool->mlx_ptr, tool->res_x, tool->res_y, tool->title);
	//tool->img_ptrblank = mlx_new_image(tool->mlx_ptr, 1000, 1000);
	tool->speed = 0;
}
*/
void	ft_error(int a)/////////////////////////////////////////////////////
{
	if (a == 1)
		write(1, "Error\nfile not found", 20);
}

int check_path_format(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	close(fd);
	return (1);
}

int get_north_texture(char **no_texture, tools *tool)
{
	int	i;

	i = 0;
	while (no_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(no_texture[0], "NO"))
		return (0);
	if (check_path_format(no_texture[1]) == 1)
		tool->no_path = ft_strdup(no_texture[1]);
	else
		return (0);
	return (1);
}

int get_south_texture(char **so_texture, tools *tool)
{
	int	i;

	i = 0;
	while (so_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(so_texture[0], "SO"))
		return (0);
	if (check_path_format(so_texture[1]) == 1)
		tool->so_path = ft_strdup(so_texture[1]);
	else
		return (0);
	return (1);
}

int get_east_texture(char **ea_texture, tools *tool)
{
	int	i;

	i = 0;
	while (ea_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(ea_texture[0], "EA"))
		return (0);
	if (check_path_format(ea_texture[1]) == 1)
		tool->ea_path = ft_strdup(ea_texture[1]);
	else
		return (0);
	return (1);
}

int get_west_texture(char **we_texture, tools *tool)
{
	int	i;

	i = 0;
	while (we_texture[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(we_texture[0], "WE"))
		return (0);
	if (check_path_format(we_texture[1]) == 1)
		tool->we_path = ft_strdup(we_texture[1]);
	else
		return (0);
	return (1);
}

int get_sprite(char **sprite, tools *tool)
{
	int	i;

	i = 0;
	while (sprite[i])
		++i;
	if (i < 2)
		return (0);
	i = 0;
	if (ft_strcmp(sprite[0], "S"))
		return (0);
	if (check_path_format(sprite[1]) == 1)
		tool->sprite_path = ft_strdup(sprite[1]);
	else
		return (0);
	return (1);
}

int get_rgb(char *colors)
{
	char	**temp;
	int		rgb[3];
	int		i;

	i = 0;
	temp = ft_split(colors, ',');
	while (temp[i])
		i++;
	if (i != 3)
		return (-1);
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(temp[i]);
		if (!(rgb[i] >= 0 && rgb[i] <= 255))
			return (-1);
	}
	rgb[0] <<= 16;
	rgb[1] <<= 8;
	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	return (rgb[0] | rgb[1] | rgb[2]);
}

int get_ground_color(char **ground, tools *tool)
{
	int	i;

	i = 0;
	while (ground[i])
		++i;
	if (i != 2)
		return (0);
	i = 0;
	if (ft_strcmp(ground[0], "F"))
		return (0);
	if ((tool->f_color = get_rgb(ground[1])) == -1)
		return (0);
	return (1);
}

int get_top_color(char **top, tools *tool)
{
	int	i;

	i = 0;
	while (top[i])
		++i;
	if (i != 2)
		return (0);
	i = 0;
	if (ft_strcmp(top[0], "C"))
		return (0);
	if ((tool->c_color = get_rgb(top[1])) == -1)
		return (0);
	return (1);
}

int get_res(char **res, tools *tool)
{
	int	i;

	i = 0;
	while (res[i])
		++i;
	if (i < 3)
		return (0);
	i = 0;
	if (ft_strcmp(res[0], "R"))
		return (0);
	while (ft_isdigit(res[1][i]) && res[1][0] > '0')
		++i;
	if (res[1][i] == '\0')
		tool->res_x = ft_atoi(res[1]);
	else
		return (0);
	i = 0;
	while (ft_isdigit(res[2][i]) && res[2][0] > '0')
		++i;
	if (res[2][i] == '\0')
		tool->res_y = ft_atoi(res[2]);
	else
		return (0);
	return (1);
}

void free_params(char **params)
{
	int i;

	i = -1;
	while(params[++i])
		free(params[i]);
	free(params);
}

int	param_check(char **params, tools *tool)
{
	static int	a = 0;
	int i;

	i = -1;
	if (a == 255)
		return (1);
	else if (get_res(params, tool))
		a |= (1 << 0);
	else if (get_north_texture(params, tool))
		a |= (1 << 1);
	else if (get_south_texture(params, tool))
		a |= (1 << 2);
	else if (get_west_texture(params, tool))
		a |= (1 << 3);
	else if (get_east_texture(params, tool))
		a |= (1 << 4);
	else if (get_sprite(params, tool))
		a |= (1 << 5);
	else if (get_ground_color(params, tool))
		a |= (1 << 6);
	else if (get_top_color(params, tool))
		a |= (1 << 7);
	free_params(params);
	return (a == 255? 1 : 0);
}

int is_player(char c, tools *tool)
{
	if (c == 'N')
		tool->dir = M_PI_2;
	else if (c == 'S')
		tool->dir = 3 * M_PI_4;
	else if (c == 'E')
		tool->dir = 0;
	else if (c == 'W')
		tool->dir = M_PI;
	else
		return (0);
	return (1);
}

int is_column(char **map, int max, tools *tool)
{
	static int	j = 0;
	int			i;
	int			a;

	i = 0;
	while (i <= max)
	{
		a = i;
		while (i <= max && map[i][j] == ' ')
			++i;
		while (i <= max && map[i][j] == '1')
		{
			++i;
			while (i <= max && (map[i][j] == '0' || map[i][j] == '2' || is_player(map[i][j], tool)))
			{
				if (i == max || map[++i][j] == ' ')
					return (0);
			}
		}
		if (i == a)
			return (0);
	}
	return (++j);
}

int is_line(char *str, tools *tool)
{
	int	i;
	int	a;

	i = 0;
	while (str[i])
	{
		a = i;
		while (str[i] == ' ')
			++i;
		while (str[i] == '1')
		{
			++i;
			while (str[i] == '0' || str[i] == '2' || is_player(str[i], tool))
			{
				++i;
				if (str[i] == '\0' || str[i] == ' ')
					return (0);
			}
		}
		if (i == a)
			return (0);
	}
	return (1);
}

char *ft_strcpy_vtwo(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = src[i];
	return (dest);
}

char	*realloc_extended_map(char **str, int max)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i])
		++i;
	temp = *str;
	if (!((*str) = malloc(sizeof(char) * (max + 1))))
		return (NULL);
	ft_strcpy_vtwo(*str, temp);
	while (i < max) // i <= max
		(*str)[i++] = ' ';
	(*str)[i] = '\0';
	free(temp);
	return (*str);
}

int map_check_line(char *str, tools *tool)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1'
		&& str[i] != '2' && !is_player(str[i], tool))
			return (0);
		++i;
	}
	return (1);
}

int empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			++i;
		else
			return (0);
	}
	return (1);
}

int realloc_map(tools *tool)
{
	static int	n = 1;
	char		**temp;
	char		**new_map;
	int			i;

	i = -1;
	temp = tool->map;
	if (!(new_map = malloc(sizeof(char*) * n)))
		return (0);
	tool->map = new_map;
	while (++i < n - 1 && n > 1)
	{
		new_map[i] = ft_strdup(temp[i]);
		free(temp[i]);
		//new_map[i] = tool->map[i];
	}
	if (n > 1)
		free(temp);
	++n;
	return (1);
}

int check_player(tools *tool, int max_y)
{
	int	x;
	int	y;
	int	p;

	y = 0;
	p = 0;
	while (y <= max_y)
	{
		x = 0;
		while (tool->map[y][x])
		{
			if (is_player(tool->map[y][x], tool))
			{
				tool->pos_player[0] = (double)y;
				tool->pos_player[1] = (double)x;
				++p;
			}
			++x;
		}
		++y;
	}
	if (p != 1)
		return (0);
	return (1);
}

int map_master_two(int j, int max_x, tools *tool)
{
	int	max_y;

	max_y = --j;
	while (j >= 0 && is_line(tool->map[j], tool))
	{
		tool->map[j] = realloc_extended_map(&tool->map[j], max_x);
		--j;
	}
	if (j != -1)
		return (0);
	while (++j < (int)max_x)
	{
		if (!is_column(tool->map, max_y, tool))
			return (0);
	}
	tool->max_y = max_y;
	return (check_player(tool, max_y));
}

int skip_empty_lines(int fd, char **line)
{
	get_next_line(fd, &*line);
	while (empty_line(*line))
	{
		free(*line);
		if (get_next_line(fd, &*line) != 1)
			return (0);
	}
	return (1);
}

int map_master(int fd, tools *tool)
{
	char			*line;
	unsigned int	max_x;
	int				j;

	max_x = 0;
	j = 0;
	if (!skip_empty_lines(fd, &line))
		return (0);
	while (map_check_line(line, tool))
	{
		max_x = max_x < ft_strlen(line) ? ft_strlen(line) : max_x;
		realloc_map(tool);
		tool->map[j++] = ft_strdup(line);
		free(line);
		get_next_line(fd, &line);
	}
	free(line);
	return (map_master_two(j, max_x, tool));
}

int get_map_param(char *path, tools *tool)
{
	char			*line;
	char			**params;
	int				fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line);
	params = ft_split(line, ' ');
	while (!param_check(params, tool))
	{
		free(line);
		if (get_next_line(fd, &line) != 1)
			return (0);
		params = ft_split(line, ' ');
	}
	free(line);
	if (!map_master(fd, tool))
		return (0);
	close(fd);
	return (param_check(params, tool));
}
/*
int main(int ac, char**av)
{
	tools	src;
	tools	*tool;

	tool = &src;
	(void)(ac);
	if (get_map_param(av[1], tool))
	{
		printf("tous les parametres sont bons\n");
	}
	else
		printf("error\n");
	return 0;
}*/