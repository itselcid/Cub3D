#include "cub3d.h"

void ft_initialize(t_game *game)
{
	game->player.x = game->map.player_x * SQUARE_SIZE + SQUARE_SIZE / 2;
	game->player.y = game->map.player_y * SQUARE_SIZE + SQUARE_SIZE / 2;
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.strafe_direction = 0;
	if (game->map.player_dir == 'N')
		game->player.rotation_angle = 3 * PI / 2;
	else if (game->map.player_dir == 'S')
		game->player.rotation_angle = PI / 2;
	else if (game->map.player_dir == 'E')
		game->player.rotation_angle = 0;
	else if (game->map.player_dir == 'W')
		game->player.rotation_angle = PI;
	game->player.walk_speed = 0.8;
	game->player.turn_speed = 0.02;
}

// Modify ft_init_window to load textures after MLX initialization
int ft_init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error initializing MLX.\n");
		return 0;
	}

	game->window_width = WINDOW_WIDTH;
	game->window_height = WINDOW_HEIGHT;

	game->win = mlx_new_window(game->mlx, game->window_width, game->window_height, "Cube3D");
	if (!game->win)
	{
		printf("Error creating MLX window.\n");
		return 0;
	}

	game->img.img = mlx_new_image(game->mlx, game->window_width, game->window_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
									   &game->img.line_length, &game->img.endian);

	// Load textures after MLX initialization
	if (!load_textures(game))
	{
		printf("Error loading textures.\n");
		return 0;
	}

	return 1;
}

void ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= game->window_width || y < 0 || y >= game->window_height)
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

int ft_key_press(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W key
		game->player.walk_direction = +1;
	if (keycode == 115) // S key
		game->player.walk_direction = -1;
	if (keycode == 97) // A key
		game->player.strafe_direction = -1;
	if (keycode == 100) // D key
		game->player.strafe_direction = +1;
	if (keycode == 65361) // Left arrow
		game->player.turn_direction = -1;
	if (keycode == 65363) // Right arrow
		game->player.turn_direction = +1;
	return 0;
}

int ft_key_release(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 115) // W or S
		game->player.walk_direction = 0;
	if (keycode == 97 || keycode == 100) // A or D
		game->player.strafe_direction = 0;
	if (keycode == 65361 || keycode == 65363) // Left or Right arrow
		game->player.turn_direction = 0;
	return 0;
}

// Update movement function to handle strafing
void ft_move_player(t_game *game)
{
	float move_step;
	float strafe_step;
	float new_x;
	float new_y;

	// Handle rotation
	game->player.rotation_angle += game->player.turn_direction * game->player.turn_speed;
	normalize_angle(&game->player.rotation_angle);

	// Handle forward/backward movement
	move_step = game->player.walk_direction * game->player.walk_speed;
	new_x = game->player.x + cos(game->player.rotation_angle) * move_step;
	new_y = game->player.y + sin(game->player.rotation_angle) * move_step;

	// Handle strafing (left/right movement)
	strafe_step = game->player.strafe_direction * game->player.walk_speed;
	new_x += cos(game->player.rotation_angle + PI / 2) * strafe_step;
	new_y += sin(game->player.rotation_angle + PI / 2) * strafe_step;

	// Check for collision and update position if no wall
	if (!its_wall(game, new_x + (cos(game->player.rotation_angle) * 5),
				  new_y + (sin(game->player.rotation_angle) * 5)))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void ft_draw_map(t_game *game)
{
	int square_color;
	int i = 0;
	while (i < game->map.height)
	{
		int j = 0;
		while (j < game->map.width)
		{
			int square_x = j * SQUARE_SIZE;
			int square_y = i * SQUARE_SIZE;
			if (game->map.map_data[i][j] == '1')
				square_color = 0xFFFFFF;
			else
				square_color = 0x000000;
			int y = 0;
			while (y < SQUARE_SIZE)
			{
				int x = 0;
				while (x < SQUARE_SIZE)
				{
					ft_mlx_pixel_put(game, square_x + x, square_y + y, square_color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void ft_draw_player(t_game *game)
{
	int x = game->player.x;
	int y = game->player.y;
	int i = -2;
	while (i < 2)
	{
		int j = -2;
		while (j < 2)
		{
			ft_mlx_pixel_put(game, x + i, y + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int its_wall(t_game *game, float x, float y)
{
	if (x < 0 || x >= game->map.width * SQUARE_SIZE ||
		y < 0 || y >= game->map.height * SQUARE_SIZE)
		return 1;

	int map_x = floor(x / SQUARE_SIZE);
	int map_y = floor(y / SQUARE_SIZE);

	return (game->map.map_data[map_y][map_x] == '1' ||
			game->map.map_data[map_y][map_x] == ' ');
}

void normalize_angle(float *angle)
{
	while (*angle > 2 * PI)
		*angle -= 2 * PI;
	while (*angle < 0)
		*angle += 2 * PI;
}

void horizontal_intersection(t_game *game, int ray_index)
{
	float first_y;
	float first_x;
	float step_y;
	float step_x;
	t_ray *ray = &game->rays[ray_index];

	if (ray->is_ray_facing_up)
	{
		first_y = floor(game->player.y / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		step_y = -SQUARE_SIZE;
	}
	else
	{
		first_y = floor(game->player.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		step_y = SQUARE_SIZE;
	}

	first_x = game->player.x + (first_y - game->player.y) / tan(ray->ray_angle);
	step_x = step_y / tan(ray->ray_angle);

	if ((ray->is_ray_facing_left && step_x > 0) || (ray->is_ray_facing_right && step_x < 0))
		step_x = -step_x;

	float next_x = first_x;
	float next_y = first_y;

	while (next_x >= 0 && next_x <= game->window_width && next_y >= 0 && next_y <= game->window_height)
	{

		if (its_wall(game, next_x, next_y))
		{
			ray->horizontal_wall_hit_x = next_x;
			ray->horizontal_wall_hit_y = next_y;
			ray->horizontal_hit_distance =
				sqrt(pow(next_x - game->player.x, 2) + pow(next_y - game->player.y, 2));
			return;
		}
		next_x += step_x;
		next_y += step_y;
	}
	ray->horizontal_hit_distance = FLT_MAX;
}

void vertical_intersection(t_game *game, int ray_index)
{
	float first_x;
	float first_y;
	float step_x;
	float step_y;
	t_ray *ray = &game->rays[ray_index];

	if (ray->is_ray_facing_left)
	{
		first_x = floor(game->player.x / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		step_x = -SQUARE_SIZE;
	}
	else
	{
		first_x = floor(game->player.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		step_x = SQUARE_SIZE;
	}

	first_y = game->player.y + (first_x - game->player.x) * tan(ray->ray_angle);
	step_y = step_x * tan(ray->ray_angle);

	if ((ray->is_ray_facing_up && step_y > 0) || (ray->is_ray_facing_down && step_y < 0))
		step_y = -step_y;

	float next_x = first_x;
	float next_y = first_y;

	while (next_x >= 0 && next_x <= game->window_width && next_y >= 0 && next_y <= game->window_height)
	{

		if (its_wall(game, next_x, next_y))
		{
			ray->vertical_wall_hit_x = next_x;
			ray->vertical_wall_hit_y = next_y;
			ray->vertical_hit_distance =
				sqrt(pow(next_x - game->player.x, 2) + pow(next_y - game->player.y, 2));
			return;
		}
		next_x += step_x;
		next_y += step_y;
	}
	ray->vertical_hit_distance = FLT_MAX;
}

// Modify cast_ray function to remove ray visualization
void cast_ray(t_game *game, float ray_angle, int ray_index)
{
	normalize_angle(&ray_angle);

	game->rays[ray_index].ray_angle = ray_angle;

	game->rays[ray_index].is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	game->rays[ray_index].is_ray_facing_up = !game->rays[ray_index].is_ray_facing_down;
	game->rays[ray_index].is_ray_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	game->rays[ray_index].is_ray_facing_left = !game->rays[ray_index].is_ray_facing_right;

	horizontal_intersection(game, ray_index);
	vertical_intersection(game, ray_index);

	if (game->rays[ray_index].horizontal_hit_distance < game->rays[ray_index].vertical_hit_distance)
	{
		game->rays[ray_index].distance = game->rays[ray_index].horizontal_hit_distance;
		game->rays[ray_index].wall_hit_x = game->rays[ray_index].horizontal_wall_hit_x;
		game->rays[ray_index].wall_hit_y = game->rays[ray_index].horizontal_wall_hit_y;
	}
	else
	{
		game->rays[ray_index].distance = game->rays[ray_index].vertical_hit_distance;
		game->rays[ray_index].wall_hit_x = game->rays[ray_index].vertical_wall_hit_x;
		game->rays[ray_index].wall_hit_y = game->rays[ray_index].vertical_wall_hit_y;
	}
}

void draw_ceiling(t_game *game, int x, int wall_top)
{
	for (int y = 0; y < wall_top; y++)
	{
		ft_mlx_pixel_put(game, x, y,
						 (game->map.sky_color[0] << 16) |
							 (game->map.sky_color[1] << 8) |
							 game->map.sky_color[2]);
	}
}

void draw_floor(t_game *game, int x, int wall_bottom)
{
	for (int y = wall_bottom; y < game->window_height; y++)
	{
		ft_mlx_pixel_put(game, x, y,
						 (game->map.floor_color[0] << 16) |
							 (game->map.floor_color[1] << 8) |
							 game->map.floor_color[2]);
	}
}

void draw_wall_strip(t_game *game, int x, float wall_height, int ray_index)
{
	int wall_top = (game->window_height - wall_height) / 2;
	if (wall_top < 0)
		wall_top = 0;

	int wall_bottom = (game->window_height + wall_height) / 2;
	if (wall_bottom >= game->window_height)
		wall_bottom = game->window_height - 1;

	// Draw ceiling
	draw_ceiling(game, x, wall_top);

	// Draw wall
	for (int y = wall_top; y < wall_bottom; y++)
	{
		int color;
		// Different colors for horizontal and vertical walls for visual distinction
		if (game->rays[ray_index].horizontal_hit_distance < game->rays[ray_index].vertical_hit_distance)
			color = 0x808080; // Darker for horizontal walls
		else
			color = 0xA0A0A0; // Lighter for vertical walls

		ft_mlx_pixel_put(game, x, y, color);
	}

	// Draw floor
	draw_floor(game, x, wall_bottom);
}


int load_textures(t_game *game)
{
	char *texture_paths[4] = {game->map.no_texture, game->map.so_texture,
							  game->map.we_texture, game->map.ea_texture};
	int i;

	for (i = 0; i < 4; i++)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, texture_paths[i],
													  &game->textures[i].width,
													  &game->textures[i].height);
		if (!game->textures[i].img)
			return (0);
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
												   &game->textures[i].bits_per_pixel,
												   &game->textures[i].line_length,
												   &game->textures[i].endian);
	}
	return (1);
}

void get_texture_pixel(t_texture *texture, int x, int y, unsigned int *color)
{
	char *dst;

	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
	{
		dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
		*color = *(unsigned int *)dst;
	}
}

void draw_textured_wall(t_game *game, int x, float wall_height, int ray_index)
{
    int wall_top = (game->window_height - wall_height) / 2;
    if (wall_top < 0)
        wall_top = 0;

    int wall_bottom = (game->window_height + wall_height) / 2;
    if (wall_bottom >= game->window_height)
        wall_bottom = game->window_height - 1;

    // Draw ceiling
    draw_ceiling(game, x, wall_top);

    // Select texture based on wall orientation and direction
    int texture_index;
    float wall_x;

    // Improved precision for texture mapping
    if (game->rays[ray_index].horizontal_hit_distance < game->rays[ray_index].vertical_hit_distance)
    {
        wall_x = game->rays[ray_index].wall_hit_x;
        texture_index = game->rays[ray_index].is_ray_facing_up ? 0 : 1;
    }
    else
    {
        wall_x = game->rays[ray_index].wall_hit_y;
        texture_index = game->rays[ray_index].is_ray_facing_left ? 2 : 3;
    }

    // Precise texture coordinate calculation
    wall_x = wall_x - floor(wall_x / SQUARE_SIZE) * SQUARE_SIZE;
    float tex_x = wall_x * game->textures[texture_index].width / SQUARE_SIZE;
    
    // Prevent texture bleeding
    tex_x = fmin(tex_x, game->textures[texture_index].width - 0.0001);

    // Use high-precision step calculation
    double step = (double)game->textures[texture_index].height / wall_height;
    double tex_pos = (wall_top - game->window_height / 2.0 + wall_height / 2.0) * step;

    // Apply distance-based darkness for depth perception
    float darkness = fmin(1.0, 1.0 / (game->rays[ray_index].distance * 0.0025));

    // Draw the wall strip with improved texture sampling
    for (int y = wall_top; y < wall_bottom; y++)
    {
        int tex_y = (int)tex_pos & (game->textures[texture_index].height - 1);
        
        unsigned int color;
        get_texture_pixel(&game->textures[texture_index], tex_x, tex_y, &color);

        // Apply distance-based shading
        unsigned char r = ((color >> 16) & 0xFF) * darkness;
        unsigned char g = ((color >> 8) & 0xFF) * darkness;
        unsigned char b = (color & 0xFF) * darkness;

        // Combine channels with improved color depth
        color = (r << 16) | (g << 8) | b;

        ft_mlx_pixel_put(game, x, y, color);
        tex_pos += step;
    }

    // Draw floor
    draw_floor(game, x, wall_bottom);
}

// Modify the cast_rays function to use textured walls
void cast_rays(t_game *game)
{
	float ray_angle = game->player.rotation_angle - (FOV_ANGLE / 2);
	float angle_increment = FOV_ANGLE / NUM_RAYS;

	for (int ray_index = 0; ray_index < NUM_RAYS; ray_index++)
	{
		cast_ray(game, ray_angle, ray_index);

		float correct_distance = game->rays[ray_index].distance *
								 cos(ray_angle - game->player.rotation_angle);

		float wall_height = (SQUARE_SIZE / correct_distance) * PROJ_DISTANCE;

		// Make sure ray_index matches screen width
		if (ray_index < WINDOW_WIDTH)
			draw_textured_wall(game, ray_index, wall_height, ray_index);

		ray_angle += angle_increment;
	}
}

// Add these new functions for minimap
void draw_minimap_square(t_game *game, int map_x, int map_y, int color)
{
	int margin_x = 0;
	int margin_y = 0;
	float scale = MINIMAP_SCALE;
	float square_size = SQUARE_SIZE * scale;
	int size = ceil(square_size);

	float tile_x = map_x * square_size;
	float tile_y = map_y * square_size;
	float player_x = game->player.x * scale;
	float player_y = game->player.y * scale;

	int screen_x = margin_x + (int)(tile_x - player_x + (MINIMAP_SIZE / 2));
	int screen_y = margin_y + (int)(tile_y - player_y + (MINIMAP_SIZE / 2));

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int px = screen_x + x;
			int py = screen_y + y;
			if (px >= margin_x && px < margin_x + MINIMAP_SIZE &&
				py >= margin_y && py < margin_y + MINIMAP_SIZE)
			{
				ft_mlx_pixel_put(game, px, py, (color == 0xFFFFFF) ? 0xDDDDDD : color);
			}
		}
	}
}

void draw_minimap_player(t_game *game)
{
	int margin_x = 0;
	int margin_y = 0;
	int center_x = margin_x + (MINIMAP_SIZE / 2);
	int center_y = margin_y + (MINIMAP_SIZE / 2);
	float player_size = MINIMAP_SIZE * 0.02; // Adjusted for better fit

	for (float y = -player_size; y <= player_size; y += 0.5)
	{
		for (float x = -player_size; x <= player_size; x += 0.5)
		{
			float dist = sqrt(x * x + y * y);
			if (dist <= player_size)
			{
				int px = (int)(center_x + x);
				int py = (int)(center_y + y);
				if (px >= margin_x && px < margin_x + MINIMAP_SIZE &&
					py >= margin_y && py < margin_y + MINIMAP_SIZE)
				{
					ft_mlx_pixel_put(game, px, py, 0xFF0000);
				}
			}
		}
	}

	float line_length = MINIMAP_SIZE / 15;
	int end_x = center_x + cos(game->player.rotation_angle) * line_length;
	int end_y = center_y + sin(game->player.rotation_angle) * line_length;
	ft_draw_line(game, center_x, center_y, end_x, end_y, 0xFF0000);
}

void draw_minimap(t_game *game)
{
	// Calculate view range in map coordinates
	float player_map_x = game->player.x / SQUARE_SIZE;
	float player_map_y = game->player.y / SQUARE_SIZE;
	float view_radius = 15.0; // Increased view radius to show more of the map

	// Calculate visible boundaries with floating-point precision
	int start_y = fmax(0, floor(player_map_y - view_radius));
	int end_y = fmin(game->map.height, ceil(player_map_y + view_radius));
	int start_x = fmax(0, floor(player_map_x - view_radius));
	int end_x = fmin(game->map.width, ceil(player_map_x + view_radius));

	// Draw map elements with different colors for better distinction
	for (int y = start_y; y < end_y; y++)
	{
		for (int x = start_x; x < end_x; x++)
		{
			char tile = game->map.map_data[y][x];
			if (tile == '1')
				draw_minimap_square(game, x, y, 0xFFFFFF);
			else if (tile == '0' || tile == game->map.player_dir)
				draw_minimap_square(game, x, y, 0x444444);
		}
	}

	draw_minimap_player(game);
}

// Update game loop to include minimap
int ft_game_loop(t_game *game)
{
	// Clear the image
	ft_memset(game->img.addr, 0, game->window_width * game->window_height * (game->img.bits_per_pixel / 8));

	ft_move_player(game);
	cast_rays(game);
	draw_minimap(game); // Draw minimap last so it appears on top

	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}
