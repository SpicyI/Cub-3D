/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:39 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/29 20:27:11 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//   includes
# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// constants
# define PI 3.1415926535
# define FOV 60 * (PI / 180)
# define screenWidth 1280
# define screenHeight 720
# define RAYNUMBER screenWidth
# define mapWidthd 25
# define mapHeightd 24
# define SCALEFACTOR 100

// Calculations marcos
# define SCREEN_DIST ((screenWidth / 2) / tan(FOV / 2))
# define WALL_HIGHT(dist, scale) (scale / dist) * SCREEN_DIST
# define MIN(a, b) ((a) < (b) ? (a) : (b))

// print colors
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

// mlx colors
# define WALLCOLOR 0xFFFF90FF
# define FLOORCOLOR 0x80FFFFFF
# define TRANSPARENT 0xFF000000
# define ARROWCOLOR 0x60FFFF00
# define RAYCOLOR 0xC0022C36
# define SKYCOLOR 0x0089CFF0
# define GROUNDCOLOR 0x009A7B4F
# define WHITE 0x00FFFFFF
# define METAL 0x00a1a4a3
// logic
# define TRUE 1
# define FALSE 0
# define ON 1
# define OFF 0
# define X 0
# define Y 1
# define VERTICAL 0
# define HORIZONTAL 1
// texture data
typedef struct t_elements
{
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	unsigned char	*f_color;
	unsigned char	*c_color;
}					t_elements;

typedef struct t_components
{
	t_elements		elements;
	char			**map;
}					t_components;

// ray tools
typedef struct s_ray
{
	int				rayNumber;
	float			step;
	float			startAngle;
	float			endAngle;
	float			hitPoint[2];
	float				ScaleFactor;
	int             hitSide; // 0 = vertical, 1 = horizontal
}					t_ray;

// map data
typedef struct s_map
{
	char			**map;
	void			*mapImg;
	void			*mapImgAddr;
	int				mapWidth;
	int				mapHeight;
	int				mapScale;
	int 			displayMap;
	int 			imgPutYpos;
	int 			imgPutXpos;
}					t_map;

//player data
typedef struct s_player
{
	float			playerX;
	float			playerY;
	float			movmentSpeed;
	float			rotationSpeed;
	float			playerAngle;

	void            *playerImg;
	void            *iconImg;
}					t_player;

//genaral data
typedef struct s_mlx
{
	void			*p_mlx;
	void			*win;
	void			*win2d;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_map			_m;
	t_player		_p;
	t_elements		_e;
	float			*distances;
	int				*rayColor;
	int 			inChange;
}					t_mlx;

/*           parcing        */
char				*get_next_line(int fd);
size_t				ft_strlen(const char *s);
char				*ft_join(char *str1, char *str2);
char				*ft_strchr(const char *str, int c);
size_t				get_len(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *ptr);
int					ft_strlcpy(char *dst, const char *src, int dstsize);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_free_all_mfs(char **str);
long long			ft_atoi(const char *str);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_isdigit(int arg);
int					read_file(char *arg, t_components *comp);
int					read_map(int fd, t_components *comp, char *line);
int					check_map(char **map);
int					is_map_element(char *str);
int					arr_size(char **arr);
int					check_space(char **map, int i, int j);
void				initialize_comps(t_components *comp);
int					check_comps(t_components *comp);

/*                  mlxTools         */
void				exit_game(t_mlx *mlx);
void				my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int					render(t_mlx *mlx);

/*                control           */
int					plane_controls(int key, t_mlx *mlx);

/*                2d rendring           */
void	transparent_Bg(t_mlx *mlx, int img_width, int img_height);
void				drawMap(t_mlx *mlx);
void				putPlayer(t_mlx *mlx);
void				putDirection(t_mlx *mlx);
void				rayCaster(t_mlx *mlx);
void minimap(t_mlx *mlx);

/*             3d rendring*/
void				putWalls(t_mlx *mlx);
void	            put_landscape(t_mlx *mlx);
int	shader(int color, int shad_percentage);
#endif