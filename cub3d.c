#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define MAP_WIDTH 11
#define MAP_HEIGHT 8
#define SQUARE_SIZE 50

int def_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
    int player_x;
    int player_y;
    int player_size;
    int square_size;
    int map[MAP_HEIGHT][MAP_WIDTH];
    float map_player_x; 
    float map_player_y;
} t_data;


void init_map(t_data *data)
{
    int y = 0;
    while (y < MAP_HEIGHT)
    {
        int x = 0;
        while (x < MAP_WIDTH)
        {
            data->map[y][x] = def_map[y][x];
            x++;
        }
        y++;
    }
}

void put_color(t_data *data, int x, int y, int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_square(t_data *data, int start_x, int start_y, int size, int color)
{
    int y = start_y;
    while (y < start_y + size)
    {
        int x = start_x;
        while (x < start_x + size)
        {
            put_color(data, x, y, color);
            x++;
        }
        y++;
    }
}


void draw_map(t_data *data)
{
    int y = 0;
    while (y < MAP_HEIGHT)
    {
        int x = 0;
        while (x < MAP_WIDTH)
        {
            int color;
            if (data->map[y][x] == 1)
                color = 0x000000;
            else
                color = 0xFFFFFF;
            draw_square(data, x * data->square_size, y * data->square_size,
                        data->square_size, color);
            x++;
        }
        y++;
    }
}

void draw_player(t_data *data)
{
    int screen_x = (int)(data->map_player_x * data->square_size);
    int screen_y = (int)(data->map_player_y * data->square_size);
    draw_square(data, screen_x - data->player_size / 2,
                screen_y - data->player_size / 2, data->player_size, 0xFF0000);
}

int is_wall(t_data *data, float x, float y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        return 1;
    return data->map[map_y][map_x];
}


int key_handler(int key_code, t_data *data)
{
    float new_x = data->map_player_x;
    float new_y = data->map_player_y;

    if (key_code == 65307)
        exit(0);
    else if (key_code == 119 || key_code == 65362) 
        new_y = data->map_player_y - 0.1;
    else if (key_code == 115 || key_code == 65364) 
        new_y = data->map_player_y + 0.1;
    else if (key_code == 97 || key_code == 65361) 
        new_x = data->map_player_x - 0.1;
    else if (key_code == 100 || key_code == 65363)
        new_x = data->map_player_x + 0.1;

    if (!is_wall(data, new_x, new_y))
    {
        data->map_player_x = new_x;
        data->map_player_y = new_y;
    }

    if (key_code == 119 || key_code == 115 || key_code == 97 || key_code == 100 ||
        key_code == 65361 || key_code == 65362 || key_code == 65363 || key_code == 65364)
    {
        draw_map(data);
        draw_player(data);
        mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    }
    return (0);
}

int main()
{
    t_data data;

    data.square_size = SQUARE_SIZE;
    data.width = MAP_WIDTH * data.square_size;
    data.height = MAP_HEIGHT * data.square_size;

    data.map_player_x = MAP_WIDTH / 2;
    data.map_player_y = MAP_HEIGHT / 2;
    data.player_size = data.square_size / 3;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.width, data.height, "Cub3D");
    data.img = mlx_new_image(data.mlx, data.width, data.height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
                                  &data.line_length, &data.endian);

    init_map(&data);
    draw_map(&data);
    draw_player(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

    mlx_hook(data.win, 2, 1L << 0, key_handler, &data);
    mlx_loop(data.mlx);
    return (0);
}