#include "cub3d.h"

int check_file_extension(char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'c' || filename[name_len - 2] != 'u' || filename[name_len - 1] != 'b')
	{
		write(1, "Error\nInvalid file extension.\n", 31);
		return (1);
	}
	return (0);
}
int check_texture_extension(char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'x' || filename[name_len - 2] != 'p' || filename[name_len - 1] != 'm')
	{
		write(1, "Error\nInvalid texture extension.\n", 34);
		return (1);
	}
	return (0);
}
int parse_texture(char *line, char direction)
{
	char **str;
	str = ft_split(line, ' ');
	if( ft_strncmp(str[0],direction,3)||str[2]!=NULL || check_texture_extension(str[1]))
	{
		write(1, "Error\nInvalid texture.\n", 24);
		return 1;
	}
	if (direction == "NO" && game.map.no_texture == NULL)
		game.map.no_texture = ft_strdup(str[1]);
	else if (direction == "SO" && game.map.so_texture == NULL)
		game.map.so_texture = ft_strdup(str[1]);
	else if (direction == "WE"  && game.map.we_texture == NULL)
		game.map.we_texture = ft_strdup(str[1]);
	else if (direction == "EA" && game.map.ea_texture == NULL)
		game.map.ea_texture = ft_strdup(str[1]);
	else
	{
		write(1, "Error\nInvalid texture.\n", 24);
		return 1;
	}

}
init_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->sky_color[0] = -1;
	map->sky_color[1] = -1;
	map->sky_color[2] = -1;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
}
int parse_color(char *line, char direction)
{

}
int parse_map(char **filename)
{
	t_game game;

	int i = 0;
	int fd;
	char *line;

	init_map(&game.map);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strnstr(line, "NO ", 3))
			parse_texture(line, "NO");
		else if (ft_strnstr(line, "SO ", 3))
			parse_texture(line, "SO");
		else if (ft_strnstr(line, "WE ", 3))
			parse_texture(line, "WE");
		else if (ft_strnstr(line, "EA ", 3))
			parse_texture(line, "EA");
		else if (ft_strnstr(line, "F ", 2))
			parse_color(line, 'F');
		else if (ft_strnstr(line, "C ", 2))
			parse_color(line, 'C');
		else if (validate_map_line(line))
			parse_map(line);
		else
		{
			write(1, "Error\nInvalid map.\n", 20);
			return 1;
		}
		free(line);

	}
}
