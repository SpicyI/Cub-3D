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
			r->sp_hitptf[X] = r->x_inter;
			r->sp_hitptf[Y] = r->y_inter;
			my_mlx_pixel_put(mlx, r->sprite_x, r->sprite_y, 0x0000FFFF);
	}
}

int set_start(t_mlx *mlx, t_inter s)
{
	int start;
	float	p[2];

	p[X] = s.sp_hitpt[X] * mlx->_m.map_scale;
	p[Y] = s.sp_hitpt[Y] * mlx->_m.map_scale;
	start = 0;
	if (s.hit_side == HOR)
		start = ((s.sp_hitptf[X] - p[X]) / mlx->_m.map_scale) * mlx->sp_img.width;
	else if (s.hit_side == VER)
		start = ((s.sp_hitptf[Y] - p[Y]) / mlx->_m.map_scale) * mlx->sp_img.width;
	return (start);
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
	mlx->_sp[i].start = set_start(mlx,s);
	if (i > 0 && mlx->_sp[i].sp_hitpt[X] == mlx->_sp[i - 1].sp_hitpt[X]
			&& mlx->_sp[i].sp_hitpt[Y] == mlx->_sp[i - 1].sp_hitpt[Y])
	{
		if (mlx->_sp[i].sprite_dist >= mlx->_sp[i - 1].sprite_dist)
			mlx->_sp[i].sprite_dist = mlx->_sp[i - 1].sprite_dist;
		else
			mlx->_sp[i - 1].sprite_dist = mlx->_sp[i].sprite_dist;
		mlx->_sp[i].start = mlx->_sp[i - 1].start;
	}
	else if (i > 0 && (mlx->_sp[i].sp_hitpt[X] != mlx->_sp[i - 1].sp_hitpt[X]
			|| mlx->_sp[i].sp_hitpt[Y] != mlx->_sp[i - 1].sp_hitpt[Y]))
		mlx->_sp[i].sp_id = mlx->ident++;
}