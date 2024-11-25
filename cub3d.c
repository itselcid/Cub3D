#include "cub3d.h"
#include <math.h>

void init_map(t_game *game)
{
    int map[MAP_ROWS][MAP_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    int i = 0;
    int j;
    while (i < MAP_ROWS)
    {
        j = 0;
        while (j < MAP_COLS)
        {
            game->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int key_Pressed(int key_code, t_game *game)
{
    if (key_code == 65307)
        exit(0);
    else if (key_code == 119)
        game->player.walkDirection = 1;
    else if (key_code == 115)
        game->player.walkDirection = -1;
    else if (key_code == 97)
        game->player.turnDirection = -1;
    else if (key_code == 100)
        game->player.turnDirection = 1;

    printf(" walkd%d\n", game->player.walkDirection);
    printf(" turnd%d\n", game->player.turnDirection);
    return (0);
}

int key_Released(int key_code, t_game *game)
{
    if (key_code == 119 || key_code == 115)
        game->player.walkDirection = 0;
    else if (key_code == 97 || key_code == 100)
        game->player.turnDirection = 0;

    printf(" walkd%d\n", game->player.walkDirection);
    printf(" turnd%d\n", game->player.turnDirection);
    return (0);
}

void draw_line(t_img *img, int start_x, int start_y, int end_x, int end_y, int color)
{
    double distance_x = end_x - start_x;
    double distance_y = end_y - start_y;
    double total_steps;

    if (fabs(distance_x) > fabs(distance_y))
        total_steps = fabs(distance_x);
    else
        total_steps = fabs(distance_y);

    double x_increment = distance_x / total_steps;
    double y_increment = distance_y / total_steps;

    double current_x = start_x;
    double current_y = start_y;

    int step = 0;
    while (step <= total_steps)
    {
        my_mlx_pixel_put(img, current_x, current_y, color);
        current_x += x_increment;
        current_y += y_increment;
        step++;
    }
}

void draw_player(t_game *game)
{
    int square_size = 8;
    int start_x = game->player.x - square_size / 2;
    int start_y = game->player.y - square_size / 2;
    int y = start_y;

    while (y < start_y + square_size)
    {
        int x = start_x;
        while (x < start_x + square_size)
        {
            my_mlx_pixel_put(&game->img, x, y, 0xFF0000);  
            x++;
        }
        y++;
    }
    int end_x = game->player.x + cos(game->player.rotationAngle) * 30;
    int end_y = game->player.y + sin(game->player.rotationAngle) * 30;

    draw_line(&game->img, game->player.x, game->player.y, end_x, end_y, 0x0000FF);  
}

void render_map(t_game *game)
{
    int i = 0;
    int j;
    while (i < MAP_ROWS)
    {
        j = 0;
        while (j < MAP_COLS)
        {
            int tile_x = j * TILE_SIZE;
            int tile_y = i * TILE_SIZE;
            int color = game->map[i][j];

            if (color == 1)
                color = 0x444444;  // Darker gray for walls
            else
                color = 0xFFFFFF;

            int y = tile_y;
            while (y < tile_y + TILE_SIZE)
            {
                int x = tile_x;
                while (x < tile_x + TILE_SIZE)
                {
                    my_mlx_pixel_put(&game->img, x, y, color);
                    x++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
    draw_player(game);
}

void update_player(t_game *game)
{
    double moveStep;
    double newX;
    double newY;

    game->player.rotationAngle += game->player.turnDirection * game->player.rotateSpeed;
    if (game->player.rotationAngle < 0)
        game->player.rotationAngle += 2 * M_PI;
    if (game->player.rotationAngle > 2 * M_PI)
        game->player.rotationAngle -= 2 * M_PI;

    moveStep = game->player.walkDirection * game->player.moveSpeed;
    newX = game->player.x + cos(game->player.rotationAngle) * moveStep;
    newY = game->player.y + sin(game->player.rotationAngle) * moveStep;
    int mapGridX = (int)(newX / TILE_SIZE);
    int mapGridY = (int)(newY / TILE_SIZE);

    if (game->map[mapGridY][mapGridX] != 1)
    {
        game->player.x = newX;
        game->player.y = newY;
    }
}

int game_loop(t_game *game)
{
    memset(game->img.addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * (game->img.bits_per_pixel / 8));

    update_player(game);
    render_map(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

    return (0);
}

t_player init_player(void)
{
    t_player player;

    player.x = TILE_SIZE * 2;
    player.y = TILE_SIZE * 2;
    player.radius = 3;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = M_PI / 2;
    player.moveSpeed = 2.0;
    player.rotateSpeed = 0.001;

    return player;
}

int main(void)
{
    t_game game;

    game.mlx = mlx_init();
    game.player = init_player();
    game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    game.img.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
                                      &game.img.line_length, &game.img.endian);

    init_map(&game);
    render_map(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    mlx_hook(game.win, 2, 1L << 0, (int (*)(int, void *))key_Pressed, &game);
    mlx_hook(game.win, 3, 1L << 1, (int (*)(int, void *))key_Released, &game);
    mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}
