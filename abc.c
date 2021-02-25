#include <stdlib.h>
#include <stdio.h>

void abc(void)
{
	char *src;
	src = malloc(12);
	src = malloc(12);
}

int main()
{
	char *src;

	src = malloc(sizeof(*src));
	abc();
	exit(0);
	return (0);
}
// int realloc_map(tools *tool)
// {
// 	static int	n = 1;
// 	char		**temp;
// 	char		**new_map;
// 	int			i;

// 	i = -1;
// 	temp = tool->map;
// 	if (!(new_map = malloc(sizeof(char*) * n)))
// 		return (0);
// 	tool->map = new_map;
// 	while (++i < n - 1 && n > 1)
// 	{
// 		new_map[i] = ft_strdup(temp[i]);
// 		//temp[i] = new_map[i];
// 		free(temp[i]);
// 		//new_map[i] = tool->map[i];
// 	}
// 	//printf("je suis la\n");
// 	/*if (n > 1)
// 		tool->map[i] = new_map[i];*/
// 	//tool->map = new_map;
// 	if (n > 1)
// 		free(temp);
// 	++n;
// 	return (1);
// }*/