
#include "../Cub3D.h"

void	putPlayer(t_mlx *mlx)
{
	int	y;
	int	player_thickness;
	int x;

	x = 0;
	y = 0;
	player_thickness = 30;
	x = (mlx->_m.img_xpos + mlx->_p.player_x) - player_thickness / 2;
	y = (mlx->_m.img_ypos + + mlx->_p.player_y) - player_thickness / 2;
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.icon_img, x, y);
}