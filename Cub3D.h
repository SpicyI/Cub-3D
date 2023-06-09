/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:39 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 20:57:26 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//   includes
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>

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
# define GROUNDCOLOR 0x009370DB
# define WHITE 0x00FFFFFF
# define METAL 0x00232322
# define PURPLE 0x9D00FF
// logic
# define TRUE 1
# define FALSE 0
# define ON 1
# define OFF 0
# define X 0
# define Y 1
# define VERTICAL 0
# define HORIZONTAL 1
# define VER 0
# define HOR 1
# define PRESSED 1
# define RELEASED 0
// texture data

enum
{
	NO,
	SO,
	WE,
	EA,
	DR,
};
enum			e_keys
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

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_side
{
	int			tex;
	int			x;
}				t_side;

typedef struct s_door
{
	int			door_exist;
	float		door_dist;
	int			door_color;
}				t_door;

typedef struct s_sprite
{
	int			sprite_exist;
	float		sprite_dist;
	int			sprite_color;
	int			sp_id;
	int			sp_hitpt[2];
	int			start;
}				t_sprite;

typedef struct s_inter
{
	float		x_inter;
	float		y_inter;
	float		xstep;
	float		ystep;
	float		hit_x;
	float		hit_y;
	float		door_x;
	float		door_y;
	float		sprite_x;
	float		sprite_y;
	int			hit_door;
	int			hit_sprite;
	float		door_dest;
	float		sprite_dist;
	int			doorcolor;
	int			sp_hitpt[2];
	float		sp_hitptf[2];
	int			hit_side;
}				t_inter;

typedef struct s_mouse
{
	int			mouse_x;
	int			mouse_y;
	float		mouse_angle;
	int			y_offset;
}				t_mouse;

typedef struct s_bloc
{
	int			x;
	int			y;
	int			bloc_x;
	int			bloc_y;
}				t_bloc;

typedef struct t_elements
{
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	int			f_color;
	int			f;
	int			c;
	int			c_color;
}				t_elements;

typedef struct t_components
{
	t_elements	elements;
	int			player_x;
	int			player_y;
	int			map_h;
	int			map_w;
	char		**map;
}				t_components;

// ray tools
typedef struct s_ray
{
	int			rays_number;
	float		step;
	float		ray_angle;
	float		max_angle;
	float		hit_point[2];
	int			hit_side;
	float		x;
	float		y;
	float		dist;
}				t_ray;

// map data
typedef struct s_map
{
	char		**map;
	void		*map_img;
	void		*mapimg_addr;
	int			map_width;
	int			map_height;
	int			map_scale;
	int			display_map;
	int			img_ypos;
	int			img_xpos;
	int			c_color;
	int			f_color;
}				t_map;

//player data
typedef struct s_player
{
	float		player_x;
	float		player_y;
	float		pmovment_speed;
	float		rotation_speed;
	float		player_angle;

	void		*player_img;
	void		*icon_img;
}				t_player;

//genaral data
typedef struct s_mlx
{
	void		*p_mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		_m;
	t_player	_p;
	float		*distances;
	t_side		*_s;
	t_data		*_t;
	t_sprite	*_sp;
	int			on_change;
	int			control_keys[8];
	float		fov;
	float		sreen_dist;
	int			mouse;
	t_data		load_screen[15];
	t_data		gun_frames[7];
	void		*load_screen_img;
	void		*gun_img;
	t_data		crosshair;
	int			shoot;
	pthread_t	thread;
	t_mouse		_mo;
	t_door		*_d;
	t_data		sp_img;
	int			ident;
	void		*sp_imgptr;
	void		*dr_imgptr;
	t_data		glitch;
	t_data		*sp_ptr;
}				t_mlx;

typedef struct s_scene
{
	t_mlx		tmp;
	int			x;
	int			y;
	int			offset;
	int			s_id;
	int			color;
	int			x_ratio;
	int			y_ratio;
	int			sprite_start;
	int			height;
}				t_scene;

/*           parcing        */
char			*get_next_line(int fd);
size_t			ft_strlen(const char *s);
char			*ft_join(char *str1, char *str2);
char			*ft_strchr(const char *str, int c);
size_t			get_len(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *ptr);
int				ft_strlcpy(char *dst, const char *src, int dstsize);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_free_all_mfs(char **str);
long long		ft_atoi(const char *str);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_isdigit(int arg);
int				read_file(char *arg, t_components *comp);
int				read_map(int fd, t_components *comp, char *line);
int				check_map(char **map, t_components *comp);
int				is_map_element(char *str);
int				arr_size(char **arr);
int				check_space(char **map, int i, int j);
int				create_trgb(unsigned char t, unsigned char r, unsigned char g,
					unsigned char b);
int				check_map_2(char **map, t_components *comp, int player);
char			*fill_map(int n, char *line);
int				check_walls(char **map);
int				get_max_line(char **map);
int				valid_space(char **map, t_components *comp);
int				num_of_commas(char *str);
int				is_dir(t_elements *elements);
int				check_comps(t_components *comp);
void			initialize_comps(t_components *comp);
void			set_player_cords(t_components *comp);
char			*ft_strjoin(char *dst, char *src);
char			*ft_itoa(int n);
char			*ft_strdup(const char *s);

/*                  mlxTools         */
void			exit_game(t_mlx *mlx);
void			my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int				render(t_mlx *mlx);

/*                control           */
int				keys_pressed(int key, t_mlx *mlx);

/*                2d rendring           */
void			draw_map(t_mlx *mlx);
void			put_player(t_mlx *mlx);
void			ray_caster(t_mlx *mlx);

/*             3d rendring*/
void			render_scene(t_mlx *mlx);
int				shader(int color, int shad_percentage);
int				key_released(int key, t_mlx *mlx);

/*				inits					*/
void			init_map(t_mlx *mlx, t_components *comp);
void			init_player(t_mlx *mlx, t_components *comp);
void			init_gun(t_mlx *mlx);
void			init_data(t_mlx *mlx, t_components *comp);
void			init_loadscreen(t_mlx *mlx);
void			init_texture(t_mlx *mlx, t_components *comp);
void			init_sprite(t_mlx *mlx);

/*				animation			*/
void			*framer(void *p);
void			*gun_framer(void *p);

/*				mouse				*/
int				mlx_mouse_hide(void);
int				mlx_mouse_move(void *win_ptr, int x, int y);
int				mouse_click(int button, int x, int y, t_mlx *mlx);
int				mouse_controls(int x, int y, t_mlx *mlx);

/*				keyboard			*/
int				key_released(int key, t_mlx *mlx);
int				keys_pressed(int key, t_mlx *mlx);
void			key_stroke(t_mlx *mlx, float step_x, float step_y);
void			arrows(t_mlx *mlx, float step_x, float step_y);
void			move_down(t_mlx *mlx, float step_x, float step_y);
void			move_up(t_mlx *mlx, float step_x, float step_y);

/*            update      */
void			update_minimap(t_mlx *mlx);
void			update(t_mlx *mlx);
void			open_door(t_mlx *mlx);

/*             cast      */
float			cast(t_ray *ray, t_mlx *mlx, int i);
float			get_distance(t_mlx *mlx, t_inter *r, t_ray *ray, int side);

/*				sprite		*/
void			check_sprite(t_mlx *mlx, t_inter *r, float x, float y);
void			sprite_detection(t_mlx *mlx, t_inter *r, t_ray *ray, int i);
t_inter			smin(t_inter r1, t_inter r2);

/*				scene layers   */
int				draw_wall(t_mlx *mlx, int i, int offset, t_scene *s);
void			draw_ceiling(t_scene *s, int i, t_mlx *mlx);
void			draw_floor(t_scene *s);
void			draw_door(t_scene *s, t_mlx *mlx, int offset);
void			transparence_line(int start, int end, t_mlx *m, int x);
void			draw_sprites(t_mlx *mlx);
/*                tools   */
t_inter			rmin(t_inter r1, t_inter r2);
int				min(int a, int b);
void			put_player(t_mlx *mlx);
int				get_img_color(t_data *data, int x, int y);
void			crop_img(t_mlx *mlx, int x, int y);
void			transparent_bg(t_mlx *mlx, int img_width, int img_height);
#endif