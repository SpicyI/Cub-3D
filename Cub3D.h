/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:39 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/07 00:38:21 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//   includes
# include <mlx.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// constants
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define RAYNUMBER SCREEN_WIDTH

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
# define SKYCOLOR 0x003E2F84
# define GROUNDCOLOR  0x009370DB
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
# define PRESSED 1
# define RELEASED 0
// texture data

enum 
{
	NO,
	SO,
	WE,
	EA,
};
enum				e_keys
{
	UP_ARROW,
	DOWN_ARROW,
	LEFT_ARROW,
	RIGHT_ARROW,
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY
};


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_side {
	int 	tex;
	int 	x;
}				t_side;


typedef struct s_inter
{
	float x_inter;
	float y_inter;
	float xstep;
	float ystep;
	float hit_x;
	float hit_y;
}		t_inter;

typedef struct s_mouse
{
	int 			mouse_x;
	int 			mouse_y;
	float 			mouse_angle;
	int			    y_offset;	
} t_mouse;

typedef struct s_bloc
{
	int 			x;
	int 			y;
	int 			bloc_x;
	int 			bloc_y;
}					t_bloc;

typedef struct t_elements
{
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	int				f_color;
	int				c_color;
}					t_elements;

typedef struct t_components
{
	t_elements	elements;
	int			player_x;
	int			player_y;
	int			map_h;
	int			map_w;
	char 		**map;
}					t_components;


// ray tools
typedef struct s_ray
{
	int				rays_number;
	float			step;
	float			ray_angle;
	float			max_angle;
	float			hit_point[2];
	int				hit_side;
	float 			x;
	float 			y;
}					t_ray;

// map data
typedef struct s_map
{
	char			**map;
	void			*map_img;
	void			*mapimg_addr;
	int				map_width;
	int				map_height;
	int				map_scale;
	int				display_map;
	int				img_ypos;
	int				img_xpos;
}					t_map;

//player data
typedef struct s_player
{
	float			player_x;
	float			player_y;
	float			pmovment_speed;
	float			rotation_speed;
	float			player_angle;

	void			*player_img;
	void			*icon_img;
	void			*gun_img;
}					t_player;



//genaral data
typedef struct s_mlx
{
	void			*p_mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_map			_m;
	t_player		_p;
	float			*distances;
	t_side				*_s;
	t_data			*_t;
	int				on_change;
	int				control_keys[8];
	float			fov;
	float			sreen_dist;
	int				mouse;
	t_data			load_screen[15];
	t_data			gun_frames[7];
	void			*load_screen_img;
	void 			*gun_img;
	int 			shoot;
	pthread_t		thread;
	t_mouse			_mo;
}					t_mlx;

/*           parcing        */
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_join(char *str1, char *str2);
char		*ft_strchr(const char *str, int c);
size_t		get_len(char *str);
int     	ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *ptr);
int			ft_strlcpy(char *dst, const char *src, int dstsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_free_all_mfs(char **str);
long long	ft_atoi(const char *str);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_isdigit(int arg);
int			read_file(char *arg, t_components *comp);
int	read_map(int fd, t_components *comp, char *line);
int check_map(char **map, t_components *comp);
int is_map_element(char *str);
int	arr_size(char **arr);
int check_space(char **map, int i, int j);
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	initialize_comps(t_components *comp);
int	check_comps(t_components *comp);
void print_data(t_components *comp);
void	set_player_cords(t_components *comp);
/*                  mlxTools         */
void				exit_game(t_mlx *mlx);
void				my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int					render(t_mlx *mlx);

/*                control           */
int					keys_pressed(int key, t_mlx *mlx);
void				update(t_mlx *mlx);

/*                2d rendring           */
void				transparent_Bg(t_mlx *mlx, int img_width, int img_height);
void				drawMap(t_mlx *mlx);
void				putPlayer(t_mlx *mlx);
void				ray_caster(t_mlx *mlx);
void				update_minimap(t_mlx *mlx);

/*             3d rendring*/
void				putWalls(t_mlx *mlx);
int					shader(int color, int shad_percentage);
int					key_released(int key, t_mlx *mlx);

/*                tools   */
int					min(int a, int b);
void				putPlayer(t_mlx *mlx);
int     mlx_mouse_hide();
int     mlx_mouse_show();
int     mlx_mouse_move();
int		get_img_color(t_data *data, int x, int y);
#endif