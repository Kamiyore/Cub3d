

#include "../../include/cub3d.h"

/*---------------------------------------------------------------------------*/
/* 1) Compute one‐tile size so that the whole world fits inside               */
/*    SCREEN_* * MINIMAP_SCALE                                              */
/*---------------------------------------------------------------------------*/
static int	compute_tile_size(t_cub *cub)
{
	float	max_w;
	float	max_h;
	float	world_w;
	float	world_h;
	float	scale_w;
	float	scale_h;
	float	down;

	max_w = SCREEN_WIDTH * MINIMAP_SCALE;
	max_h = SCREEN_HEIGHT * MINIMAP_SCALE;
	world_w = cub->map->width * TILE_SIZE;
	world_h = cub->map->height * TILE_SIZE;
	scale_w = max_w / world_w;
	scale_h = max_h / world_h;
	down = fminf(scale_w, scale_h);
	// at least 1px per tile
	return (int)fmaxf(1.0f, TILE_SIZE * down);
}

/*---------------------------------------------------------------------------*/
/* 2) Initialize the minimap image                                           */
/*---------------------------------------------------------------------------*/
void	init_minimap_bonus(t_cub *cub)
{
	if (BONUS_MODE == false)
		return ;
	cub->mini.tile_size = compute_tile_size(cub);
	cub->mini.width = cub->map->width * cub->mini.tile_size;
	cub->mini.height = cub->map->height * cub->mini.tile_size;
	cub->mini.img_ptr = mlx_new_image(cub->mlx, cub->mini.width,
			cub->mini.height);
	cub->mini.img_data = (int *)mlx_get_data_addr(cub->mini.img_ptr,
			&cub->mini.bpp, &cub->mini.size_l, &cub->mini.endian);
}
