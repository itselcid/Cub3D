/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:25 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/07 14:15:16 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print1(void)
{
	printf("\t\t\t░█████╗░██╗░░░██╗██████╗░██████╗░██████╗░\n");
	printf("\t\t\t██╔══██╗██║░░░██║██╔══██╗╚════██╗██╔══██╗\n");
	printf("\t\t\t██║░░╚═╝██║░░░██║██████╦╝░█████╔╝██║░░██║\n");
	printf("\t\t\t██║░░██╗██║░░░██║██╔══██╗░╚═══██╗██║░░██║\n");
	printf("\t\t\t╚█████╔╝╚██████╔╝██████╦╝██████╔╝██████╔╝\n");
	printf("\t\t\t░╚════╝░░╚═════╝░╚═════╝░╚═════╝░╚═════╝░\n\n");
}

void	print(void)
{
	print1();
	printf(GREEN "YOU CAN MOVE WITH THE FOLLOWING KEYS\n\n\n" RESET);
	printf(RED "MOUVEMENT \n" RESET);
	printf("\t\t\t\tmove forward: ");
	printf(GREEN "W\n" RESET);
	printf("\tmove left: ");
	printf(GREEN "A" RESET);
	printf("\t\t\t\t\t\tmove right: ");
	printf(GREEN "D\n" RESET);
	printf("\t\t\t\tmove backward: ");
	printf(GREEN "S\n" RESET);
	printf("\n\n");
	printf(RED "ROTATION \n" RESET);
	printf("\trotate left: ");
	printf(GREEN "left arrow" RESET);
	printf("\t\t\t\t\t\trotate right: ");
	printf(GREEN "right arrow\n" RESET);
}

int	game_loop(t_data *data)
{
	move_player(data);
	cast_rays(data);
	projection_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_map, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || !av[1])
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (parse_map(&data, av[1]))
		return (1);
	init_data(&data);
	init_image_and_ray(&data);
	//print();
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, key_handler, &data);
	mlx_hook(data.win, 3, 1L << 1, relase_key, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
