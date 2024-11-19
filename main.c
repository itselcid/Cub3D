#include <mlx.h>
#include <stdlib.h>

int key_hanler(int key_code, void *param)
{
    (void)param;
    if (key_code == 65307)
        exit(0);
    return 0;
}

int main()
{
    void *mlx;
    void *win;
    int height = 600;
    int width = 800;
    int graycolor = 0x808080;

    mlx = mlx_init();

    win = mlx_new_window(mlx, width, height, "Cub3D");

    int y = 0;
    while (y < height)
    {
        int x = 0;
        while (x < width)
        {
            mlx_pixel_put(mlx, win, x, y, graycolor);
            x++;
        }
        y++;
    }

    mlx_key_hook(win, key_hanler, NULL);
    mlx_loop(mlx);
    return (0);
}