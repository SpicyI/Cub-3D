#include "../Cub3D.h"

void check_sprite(t_mlx *mlx, t_inter *r, float x, float y)
{
	if (!r->hit_sprite)
	{
			r->sprite_x = x * mlx->_m.map_scale;
			r->sprite_y = y * mlx->_m.map_scale;
			r->sprite_dist = sqrt(pow(mlx->_p.player_x - r->sprite_x, 2)
					+ pow(mlx->_p.player_y - r->sprite_y, 2));
			r->hit_sprite = 1;
			r->sp_hitpt[X] = x;
			r->sp_hitpt[Y] = y;
			my_mlx_pixel_put(mlx, r->sprite_x, r->sprite_y, 0x0000FFFF);
	}
}

void sprite_detection(t_mlx *mlx, t_inter *r, t_ray *ray, int i)
{
	t_inter s;

	mlx->_sp[i].sprite_exist = 0;
	s = smin(r[0], r[1]);
	mlx->_sp[i].sprite_dist = s.sprite_dist * cos(mlx->_p.player_angle
			- ray->ray_angle);
	mlx->_sp[i].sp_hitpt[X] = s.sp_hitpt[X];
	mlx->_sp[i].sp_hitpt[Y] = s.sp_hitpt[Y];
	if (mlx->_sp[i].sprite_dist < ray->dist)
		mlx->_sp[i].sprite_exist = 1;
	if (i > 0 && mlx->_sp[i].sp_hitpt[X] == mlx->_sp[i - 1].sp_hitpt[X]
			&& mlx->_sp[i].sp_hitpt[Y] == mlx->_sp[i - 1].sp_hitpt[Y])
		mlx->_sp[i].sprite_dist = mlx->_sp[i - 1].sprite_dist;
	else if (i > 0 && (mlx->_sp[i].sp_hitpt[X] != mlx->_sp[i - 1].sp_hitpt[X]
			|| mlx->_sp[i].sp_hitpt[Y] != mlx->_sp[i - 1].sp_hitpt[Y]))
		mlx->_sp[i].sp_id = mlx->ident++;
}