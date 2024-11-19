#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>


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
} t_data;



void put_color(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void draw_player(t_data *data)
{
    draw_square(data, data->player_x, data->player_y, data->player_size, 0xFF0000);
}

int key_handler(int key_code, t_data *data)
{
    if (key_code == 65307) 
        exit(0);
    else if (key_code == 119 || key_code == 65362) // W or UP
        data->player_y--;
    else if (key_code == 115 || key_code == 65364) // S or DOWN
        data->player_y++; 
    else if (key_code == 97 || key_code == 65361)  // A or LEFT
        data->player_x--;
    else if (key_code == 100 || key_code == 65363) // D or RIGHT
        data->player_x++;
                
    
    if (key_code == 119 || key_code == 115 || key_code == 97 || key_code == 100 ||
        key_code == 65361 || key_code == 65362 || key_code == 65363 || key_code == 65364)
    {
        int y = 0;
        while (y < data->height)
        {
            int x = 0;
            while (x < data->width)
            {
                put_color(data, x, y, 0x808080);
                x++;
            }
            y++;
        }
        draw_player(data);
        mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    }
    return (0);
}

int main()
{
    t_data data;
    int graycolor;

    data.width = 800;
    data.height = 600;
    data.player_x = data.width / 2;   
    data.player_y = data.height / 2;   
    data.player_size = 10;             
    graycolor = 0x808080;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.width, data.height, "Cub3D");
    data.img = mlx_new_image(data.mlx, data.width, data.height);
    

    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, 
                                 &data.line_length, &data.endian);
    int y = 0;
    while (y < data.height)
    {
        int x = 0;
        while (x < data.width)
        {
            put_color(&data, x, y, graycolor);
            x++;
        }

        y++;
    }

    draw_player(&data);

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 1L<<0, key_handler, &data);  // Changed this line
    mlx_loop(data.mlx);
    return (0);
}