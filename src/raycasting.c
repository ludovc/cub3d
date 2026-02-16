/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:49:54 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:49:56 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_ray_steps(t_ray *ray, double player_x, double player_y)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (player_x - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->mapx + 1.0 - player_x) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (player_y - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->mapy + 1.0 - player_y) * ray->delta_disty;
	}
}

void	digital_differential_analysis(t_game *g, t_ray *ray)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(g, ray->mapx, ray->mapy))
			hit = 1;
	}
}

void	calc_perp_dist(t_ray *ray, double player_x, double player_y)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->mapx - player_x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dirx;
	else
		ray->perp_dist = (ray->mapy - player_y + (1 - ray->step_y) / 2.0)
			/ ray->ray_diry;
	if (ray->perp_dist < 0.01)
		ray->perp_dist = 0.01;
}

void	get_line_limits(t_ray *ray)
{
	ray->line_h = (int)(HEIGHT / ray->perp_dist);
	ray->draw_start = -(ray->line_h) / 2 + HEIGHT / 2;
	ray->draw_end = (ray->line_h) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->line_h < 1)
		ray->line_h = 1;
}

void	calculate_wall_x(t_game *g, t_ray *ray, t_column *col)
{
	if (ray->side == 0)
		col->wall_x = g->player.y + ray->perp_dist * ray->ray_diry;
	else
		col->wall_x = g->player.x + ray->perp_dist * ray->ray_dirx;
	col->wall_x -= floor(col->wall_x);
}

/*calculate_wall_x (caso side = 1)
se il raggio colpisce una parete verticale calcola la distanza percorsa
dal raggio lungo l'asse y fino al punto di impatto con la parete.

Se la mappa è una griglia e il raggio colpisce la parete a x = 4.73,
questa indica la posizione globale, dice che il punto d’impatto si trova 
nella cella 4 (partendo da 0) e a 0.73 della larghezza della cella.

per posizionare la texture ci dobbiamo ricavare la posizione relativa, il 0.73.

in qesto caso ci serve la coordinata y del punto d’impatto,
possiamo calcolarla con:
wall_x = player.y + perp_dist * ray_diry

otteniamo la coordinata relativa sottraendone la parte intera.
col->wall_x -= floor(col->wall_x);

ora sappiamo quanto il punto d’impatto è distante dal bordo sinistro
della singola cella, così da poter applicare la texture correttamente.

avanzando con x in raycast_scene() calcoliamo quale pixel della texture usare.*/
