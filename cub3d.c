#include "cub3d.h"

int map[MAP_ROWS][MAP_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

t_game game;

void ft_initialize()
{
	game.player.x = WINDOW_WIDTH / 2;
	game.player.y = WINDOW_HEIGHT / 2;
	game.player.turn_direction = 0;
	game.player.walk_direction = 0;
	game.player.rotation_angle = PI / 2;
	game.player.walk_speed = 1;	  
	game.player.turn_speed = 0.02; 
}

int ft_init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error initializing MLX.\n");
		return 0;
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D");
	if (!game->win)
	{
		printf("Error creating MLX window.\n");
		return 0;
	}
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	return 1;
}

void ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;
	dst = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	double delta_x = end_x - start_x;
	double delta_y = end_y - start_y;
	double steps = fmax(fabs(delta_x), fabs(delta_y));

	double x_increment = delta_x / steps;
	double y_increment = delta_y / steps;

	double x = start_x;
	double y = start_y;

	for (int i = 0; i <= steps; i++)
	{
		ft_mlx_pixel_put(game, (int)x, (int)y, color);
		x += x_increment;
		y += y_increment;
	}
}

int ft_key_press(int keycode)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 65362)
		game.player.walk_direction = +1;
	if (keycode == 65364)
		game.player.walk_direction = -1;
	if (keycode == 65363)
		game.player.turn_direction = +1;
	if (keycode == 65361)
		game.player.turn_direction = -1;
	return 0;
}

int ft_key_release(int keycode)
{
	if (keycode == 65362 || keycode == 65364)
		game.player.walk_direction = 0;
	if (keycode == 65363 || keycode == 65361)
		game.player.turn_direction = 0;
	return 0;
}

void ft_move_player()
{
	float move_step;
	float new_x;
	float new_y;
	int map_x;
	int map_y;

	game.player.rotation_angle += game.player.turn_direction * game.player.turn_speed;
	move_step = game.player.walk_direction * game.player.walk_speed;

	new_x = game.player.x + cos(game.player.rotation_angle) * move_step;
	new_y = game.player.y + sin(game.player.rotation_angle) * move_step;

	map_x = (int)(new_x / SQUARE_SIZE);
	map_y = (int)(new_y / SQUARE_SIZE);

	if (!map[map_y][map_x])
	{
		game.player.x = new_x;
		game.player.y = new_y;
	}
}

void ft_draw_map()
{
	int square_color;
	int i = 0;
	while (i < MAP_ROWS)
	{
		int j = 0;
		while (j < MAP_COLS)
		{
			int square_x = j * SQUARE_SIZE;
			int square_y = i * SQUARE_SIZE;
			if (map[i][j] != 0)
				square_color = 0xFFFFFF;
			else
				square_color = 0x000000;
			int y = 0;
			while (y < SQUARE_SIZE)
			{
				int x = 0;
				while (x < SQUARE_SIZE)
				{
					ft_mlx_pixel_put(&game, square_x + x, square_y + y, square_color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void ft_draw_player()
{
	int x = game.player.x;
	int y = game.player.y;
	int i = -2;
	while (i < 2)
	{
		int j = -2;
		while (j < 2)
		{
			ft_mlx_pixel_put(&game, x + i, y + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int its_wall(float x, float y)
{
	int map_x = floor(x / SQUARE_SIZE);
	int map_y = floor(y / SQUARE_SIZE);

	if (map_y < 0 || map_y >= MAP_ROWS || map_x < 0 || map_x >= MAP_COLS)
		return 1;
	return map[map_y][map_x];
}

void normalize_angle(float *angle)
{
	while (*angle > 2 * PI)
		*angle -= 2 * PI;
	while (*angle < 0)
		*angle += 2 * PI;
}

void horizontal_intersection(int ray_index)
{
	float first_y;
	float first_x;
	float step_y;
	float step_x;
	t_ray *ray = &game.rays[ray_index];

	if (ray->is_ray_facing_up)
	{
		first_y = floor(game.player.y / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		step_y = -SQUARE_SIZE;
	}
	else
	{
		first_y = floor(game.player.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		step_y = SQUARE_SIZE;
	}

	first_x = game.player.x + (first_y - game.player.y) / tan(ray->ray_angle);
	step_x = step_y / tan(ray->ray_angle);

	if ((ray->is_ray_facing_left && step_x > 0) || (ray->is_ray_facing_right && step_x < 0))
		step_x = -step_x;

	float next_x = first_x;
	float next_y = first_y;

	while (next_x >= 0 && next_x <= WINDOW_WIDTH && next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{

		if (its_wall(next_x, next_y))
		{
			ray->horizontal_wall_hit_x = next_x;
			ray->horizontal_wall_hit_y = next_y;
			ray->horizontal_hit_distance =
				sqrt(pow(next_x - game.player.x, 2) + pow(next_y - game.player.y, 2));
			return;
		}
		next_x += step_x;
		next_y += step_y;
	}
	ray->horizontal_hit_distance = FLT_MAX;
}


void vertical_intersection(int ray_index)
{
	float first_x;
	float first_y;
	float step_x;
	float step_y;
	t_ray *ray = &game.rays[ray_index];

	if (ray->is_ray_facing_left)
	{
		first_x = floor(game.player.x / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		step_x = -SQUARE_SIZE;
	}
	else
	{
		first_x = floor(game.player.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		step_x = SQUARE_SIZE;
	}

	first_y = game.player.y + (first_x - game.player.x) * tan(ray->ray_angle);
	step_y = step_x * tan(ray->ray_angle);

	if ((ray->is_ray_facing_up && step_y > 0) || (ray->is_ray_facing_down && step_y < 0))
		step_y = -step_y;

	float next_x = first_x;
	float next_y = first_y;

	while (next_x >= 0 && next_x <= WINDOW_WIDTH && next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{

		if (its_wall(next_x, next_y))
		{
			ray->vertical_wall_hit_x = next_x;
			ray->vertical_wall_hit_y = next_y;
			ray->vertical_hit_distance =
				sqrt(pow(next_x - game.player.x, 2) + pow(next_y - game.player.y, 2));
			return;
		}
		next_x += step_x;
		next_y += step_y;
	}
	ray->vertical_hit_distance = FLT_MAX;
}

void cast_ray(float ray_angle, int ray_index)
{
	normalize_angle(&ray_angle);

	game.rays[ray_index].ray_angle = ray_angle;

	game.rays[ray_index].is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	game.rays[ray_index].is_ray_facing_up = !game.rays[ray_index].is_ray_facing_down;
	game.rays[ray_index].is_ray_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	game.rays[ray_index].is_ray_facing_left = !game.rays[ray_index].is_ray_facing_right;

	horizontal_intersection(ray_index);
	vertical_intersection(ray_index);

	if (game.rays[ray_index].horizontal_hit_distance < game.rays[ray_index].vertical_hit_distance)
	{
		game.rays[ray_index].distance = game.rays[ray_index].horizontal_hit_distance;
		game.rays[ray_index].wall_hit_x = game.rays[ray_index].horizontal_wall_hit_x;
		game.rays[ray_index].wall_hit_y = game.rays[ray_index].horizontal_wall_hit_y;
		ft_draw_line(&game, game.player.x, game.player.y,
					 game.rays[ray_index].wall_hit_x,
					 game.rays[ray_index].wall_hit_y, 0xFF0000);
	}
	else
	{
		game.rays[ray_index].distance = game.rays[ray_index].vertical_hit_distance;
		game.rays[ray_index].wall_hit_x = game.rays[ray_index].vertical_wall_hit_x;
		game.rays[ray_index].wall_hit_y = game.rays[ray_index].vertical_wall_hit_y;
		ft_draw_line(&game, game.player.x, game.player.y,
					 game.rays[ray_index].wall_hit_x,
					 game.rays[ray_index].wall_hit_y, 0xFF0000);
	}
}

void cast_rays()
{
	float ray_angle = game.player.rotation_angle - (FOV_ANGLE / 2);
	float angle_increment = FOV_ANGLE / NUM_RAYS;
	int ray_index = 0;

	while (ray_index < NUM_RAYS)
	{
		cast_ray(ray_angle, ray_index);
		ray_angle += angle_increment;
		ray_index++;
	}
}

int ft_game_loop(t_game *game)
{

	ft_move_player();
	ft_draw_map();
	ft_draw_player();
	cast_rays();
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}

