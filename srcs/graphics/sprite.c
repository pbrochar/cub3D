/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:34:25 by pbrochar          #+#    #+#             */
/*   Updated: 2021/03/29 18:25:16 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_y_sprite(t_main *main_struct, t_sprite_val sprite)
{
	int d;
	int y;
	int color;

	y = sprite.draw_start_y;
	while (y < sprite.draw_end_y)
	{
		d = (y) * 256 - (RES_Y - 1) * 128 + (sprite.sprite_height - 1) * 128;
		sprite.tex_y = (((d * (TEXTURES[4]->height - 1))
						/ (sprite.sprite_height - 1)) / 256);
		if (sprite.tex_y < 0)
			sprite.tex_y = 0;
		if (sprite.tex_y >= RES_Y)
			sprite.tex_y = RES_Y - 1;
		color = get_pxl_color(TEXTURES[4], sprite.tex_x, sprite.tex_y);
		if ((color & 0x00FFFFFF) != 0)
			pxl_put(main_struct, sprite.stripe, y, color);
		y++;
	}
}

static void	draw_stripe(t_main *main_struct, t_sprite_val sprite)
{
	int y;
	int d;

	sprite.stripe = sprite.draw_start_x;
	while (sprite.stripe < sprite.draw_end_x)
	{
		sprite.tex_x = (int)((256 * (sprite.stripe - (-sprite.sprite_width / 2
							+ sprite.sprite_screen_x))
							* (TEXTURES[4]->width - 1)
							/ (sprite.sprite_width - 1)) / 256);
		if (sprite.tex_x < 0)
			sprite.tex_x = 0;
		y = sprite.draw_start_y;
		if (sprite.transform_y > 0 && sprite.stripe > 0 && sprite.stripe < RES_X
			&& sprite.transform_y < WALL_DIST_BUF[sprite.stripe])
			draw_y_sprite(main_struct, sprite);
		sprite.stripe++;
	}
}

void		draw_sprite(t_main *main_struct)
{
	t_sprite_val	sprite;
	int				i;

	lst_to_tab(main_struct);
	sort_sprite_tab(main_struct);
	i = 0;
	while (i < NB_SPRITE)
	{
		sprite = initial_sprite_calculation(main_struct, i);
		draw_stripe(main_struct, sprite);
		i++;
	}
	free_sprite_list(main_struct);
	free(SPRITE_TAB);
}
