#include "cub3d.h"

void init_map(t_map *map)
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
	map->map_data = NULL;
	map->width = 0;
	map->height = 0;
}
void cleanup_up(int num)
{
    if (game.map.line)
        free(game.map.line);
    if (game.map.fd > 0)
        close(game.map.fd);
    if (game.map.no_texture)
        free(game.map.no_texture);
    if (game.map.so_texture)
        free(game.map.so_texture);
    if (game.map.we_texture)
        free(game.map.we_texture);
    if (game.map.ea_texture)
        free(game.map.ea_texture);
    if (game.map.map_data)
    {
        int i = 0;
        while (game.map.map_data[i])
            free(game.map.map_data[i++]);
        free(game.map.map_data);
    }
	if(num==1)
		exit(1);
}

int check_file_extension(char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'c' ||
		filename[name_len - 2] != 'u' || filename[name_len - 1] != 'b')
	{
		write(1, "Error\nInvalid file extension.\n", 31);
			cleanup_up(1);
	}
	return (0);
}
int check_texture_extension(char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'x' ||
		filename[name_len - 2] != 'p' || filename[name_len - 1] != 'm')
	{
		write(1, "Error\nInvalid texture extension.\n", 34);
			cleanup_up(1);
	}
	return (0);
}
int parse_texture(char *line, char *direction)
{
	char **str;
	int fd;
	str = ft_split(line, ' ');
	if (ft_strncmp(str[0], direction, 2) || str[2] != NULL || check_texture_extension(str[1]))
	{
		write(1, "Error\nInvalid texture 1.\n", 24);
			cleanup_up(1);
	}

	fd = open(str[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nCant acces texture file.\n", 32);
			cleanup_up(1);
	}
	close(fd);
	if (ft_strncmp(direction, "NO", 2) == 0 && game.map.no_texture == NULL)
		game.map.no_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "SO", 2) == 0 && game.map.so_texture == NULL)
		game.map.so_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "WE", 2) == 0 && game.map.we_texture == NULL)
		game.map.we_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "EA", 2) == 0 && game.map.ea_texture == NULL)
		game.map.ea_texture = ft_strdup(str[1]);
	else
	{
		write(1, "Error\nInvalid texture.\n", 24);
			cleanup_up(1);
	}

	return 0;
}

int parse_color(char *line, char direction)
{
	char **str;
	char **colors;
	int commas = 0;
	int i = 0;

	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
	{
		write(1, "Error\nInvalid color format.\n", 28);
			cleanup_up(1);
	}

	str = ft_split(line, ' ');
	if (str[2] != NULL || str[0][0] != direction || !str[1])
	{
		write(1, "Error\nInvalid color format.\n", 28);
			cleanup_up(1);
	}

	i = 0;
	while (str[1][i])
	{
		if (!(str[1][i] >= '0' && str[1][i] <= '9') && str[1][i] != ',')
		{
			write(1, "Error\nInvalid color character.\n", 32);
				cleanup_up(1);
		}
		i++;
	}

	colors = ft_split(str[1], ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		write(1, "Error\nInvalid color format.\n", 29);
			cleanup_up(1);
	}
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			write(1, "Error\nColor out of range\n", 26);
				cleanup_up(1);
		}
		if ((direction == 'F' && game.map.floor_color[i] != -1) ||
			(direction == 'C' && game.map.sky_color[i] != -1))
		{
			write(1, "Error\nDuplicated color\n", 24);
				cleanup_up(1);
		}
		i++;
	}

	i = 0;
	while (i < 3)
	{
		if (direction == 'F')
			game.map.floor_color[i] = ft_atoi(colors[i]);
		else if (direction == 'C')
			game.map.sky_color[i] = ft_atoi(colors[i]);
		i++;
	}
	return 0;
}
int is_empty_line(char *line)
{
	int i = 0;

	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] == '\0')
		return 1;
	return 0;
}
int check_parsed_elements(void)
{
	if (!game.map.no_texture || !game.map.so_texture ||
		!game.map.we_texture || !game.map.ea_texture ||
		game.map.floor_color[0] == -1 || game.map.sky_color[0] == -1)
		return 0;
	return 1;
}
int handle_map_line(char *line)
{
	char **tmp;
	int i;

	if (game.map.map_data == NULL)
	{
		game.map.map_data = malloc(sizeof(char *) * 2);
		game.map.map_data[0] = ft_strdup(line);
		game.map.map_data[1] = NULL;
		game.map.height = 1;
		game.map.width = ft_strlen(line);
	}
	else
	{
		int old_height = game.map.height;
		tmp = malloc(sizeof(char *) * (old_height + 2));
		i = 0;
		while (i < old_height)
		{
			tmp[i] = game.map.map_data[i];
			i++;
		}
		tmp[i] = ft_strdup(line);
		tmp[i + 1] = NULL;
		free(game.map.map_data);
		game.map.map_data = tmp;
		game.map.height++;
		if (ft_strlen(line) > game.map.width)
			game.map.width = ft_strlen(line);
	}
	return 0;
}
int parse_map(char *filename)
{
    int elements_done = 0;
    int map_begin = 0;

    init_map(&game.map);
    game.map.fd = open(filename, O_RDONLY);
    if (game.map.fd < 0 || check_file_extension(filename))
        return 1;
    
    game.map.line = get_next_line(game.map.fd);
    while (game.map.line)
    {
        if (!check_parsed_elements())
        {
            if (!is_empty_line(game.map.line))
            {
                if (ft_strnstr(game.map.line, "NO ", 3) || ft_strnstr(game.map.line, "NO\t", 3))
                    parse_texture(game.map.line, "NO");
                else if (ft_strnstr(game.map.line, "SO ", 3) || ft_strnstr(game.map.line, "SO\t", 3))
                    parse_texture(game.map.line, "SO");
                else if (ft_strnstr(game.map.line, "WE ", 3) || ft_strnstr(game.map.line, "WE\t", 3))
                    parse_texture(game.map.line, "WE");
                else if (ft_strnstr(game.map.line, "EA ", 3) || ft_strnstr(game.map.line, "EA\t", 3))
                    parse_texture(game.map.line, "EA");
                else if (ft_strnstr(game.map.line, "F ", 2) || ft_strnstr(game.map.line, "F\t", 3))
                    parse_color(game.map.line, 'F');
                else if (ft_strnstr(game.map.line, "C ", 2) || ft_strnstr(game.map.line, "C\t", 3))
                    parse_color(game.map.line, 'C');
                else
                {
                    write(1, "Error\nInvalid element!\n", 24);
					cleanup_up(1);
                }
            }
        }
        else
        {
            if (!is_empty_line(game.map.line))
            {
                elements_done = 1;
                map_begin = 1;
                handle_map_line(game.map.line);
            }
            else if (map_begin)
                handle_map_line(game.map.line);
        }
        free(game.map.line);
        game.map.line = get_next_line(game.map.fd);
    }
    close(game.map.fd);
    if (!elements_done)
    {
        write(1, "Error\nMissing map data\n", 24);
			cleanup_up(1);
    }
    return 0;
}
