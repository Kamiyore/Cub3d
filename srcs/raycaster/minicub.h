

#include "../../include/cub3d.h"
#include "../../libft/libft.h"
#include <float.h>
#include <math.h>

#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000
#define TILE_SIZE 64
#define FIELD_OF_VIEW 60
#define ROTATION_SPEED 0.045
#define MOVEMENT_SPEED 4
#define TILE_CENTER (TILE_SIZE / 2)

typedef struct s_player
{
	int			pixel_x;
	int			pixel_y;
	double		angle;
	float		view_radian;
	bool		rotation;
	bool		left_right;
	bool		up_down;

}				t_player;

typedef struct s_ray
{
	double		angle;
	double		distance;
	bool		is_vartical;
}				t_ray;

typedef struct s_map
{
	char		**map2d;
	int			player_x;
	int			player_y;
	int			width;
	int			height;
}				t_map;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void *img_ptr; // returned by mlx_new_image()
	int *img_data; // pixel buffer
	int bpp;       // bits per pixel
	int size_l;    // length of line (bytes)
	int endian;    // endianness
	t_ray		*ray;
	t_map		*map;
	t_player	*ply;
}				t_cub;

typedef struct s_xy
{
	float		x;
	float		y;
}				t_xy;

//#################################################################################//
//################################### FUNCTION ####################################//
//#################################################################################//

float			get_horizontal_intersection(t_cub *cub);
float			get_vertical_intersection(t_cub *cub);
void			render_wall(t_cub *cub, int ray_count);

// helper
int				get_quandrant(float angle);
float			normalize_angle(float angle);
int				is_out_of_bounds(t_cub *cub, float inter_x, float inter_y);
int				is_wall(t_cub *cub, float inter_x, float inter_y);
float			compute_adjacent(float opposite, float angle);
float			compute_opposite(float adjacent, float angle);
float			compute_hypotenuse(float opposite, float adjacent);

// get step
float			get_horizontal_step_x(t_cub *cub);
float			get_horizontal_step_y(t_cub *cub);
float			get_vartical_step_y(t_cub *cub);
float			get_vartical_step_x(t_cub *cub);

// direction helper
bool			look_left(float angle);
bool			look_right(float angle);
bool			look_down(float angle);
bool			look_up(float angle);
