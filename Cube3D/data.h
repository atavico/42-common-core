/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:15:25 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 15:06:34 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "libft/libft.h"
#include "amlx/mlx.h"
// #include "minilibx/mlx.h"

#define PI 3.14159265359
#define RAD 0.0174533

#define FOV 60
#define HALF_FOV 30
#define FOV_R   60 * (PI/180)

#define ROT 0.03299066

//keypress
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53
# define    SPEED 0.07

#define HEIGHT	1117	// 2^10
#define WEIGHT	1728	// 2^11

# define WP		2383707

typedef struct s_ray
{
    float   x;         //origine X raggio
    float   y;         //origine Y raggio
    float   dist;      // distanza origine-muro raggio
    float   r_dist;
    float   wall;      // dimensione muro
    int     w_x;
}               t_ray;

typedef struct s_texture
{
    void    *ptr;
    char    *addr;
    int     bfp;
    int     l_bytes;
    int     endian;
    int     width;
    int     height;
}               t_texture;

typedef struct s_player
{
    float     x;
    float     y;
    int     w;              //flag tasto avanti
    int     a;              //flag  tasto sinistra
    int     s;              //flag  tasto indietro
    int     d;              //flag  tasto destra
    float   dx;
    float   dy;
    float   angle;          //orientamento player (angolo rispetto allo 0)
    int     rigth;          //flag tasto vista destra
    int     left;           //flag tasto vista sinistra
}              t_player;

typedef struct s_image
{
    void    *img;
    char    *addr;
    int     l_bytes;
    int     bfp;
    int     endian;
}               t_image;

typedef struct s_map
{
	char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    char    *DO;
	char	**map;
	int		mm_H;		//minimappsize(altezza)
	int		mm_W;		//minimappsize(larghezza)
}			t_map;

typedef struct s_cube3D
{
    
    
    int     row;         //numero righe mappa
    int     col;          //numero colonne mappa
    int     mm_H;           //minimapp size (altezza)
    int     mm_W;           //minimapp size (larghezza)
    int     cH_size;        //cella matrice size (altezza)
    int     cW_size;        //cella matrice size (larghezza)
    int     cellsize;
    int     s_h;            //screen size altezza
    int     s_w;            //screen size larghezza
    void    *mlx;
    void    *win;
    
    int     frame;
    int         F;
    int         C;
    t_texture   north;
    t_texture   south;
    t_texture   east;
    t_texture   west;
    t_texture   door;
    t_texture   door2;
    t_player    p;
    t_image     screen;
    t_image     minimap;
    t_ray       ray;
    t_map       map;
}               t_cube3D;



//init

void    ft_init_info(t_cube3D *data);
void    ft_init(t_cube3D *data);
void    ft_map_size(t_cube3D *data);
//utility
int     ft_skip_space(char *str);
char    *ft_find_map(int fd);
void	ft_print_struct(t_cube3D data);
void	ft_free_struct(t_cube3D *data);

//check
void    ft_check_map(char **map);
void    ft_check_file(char *file_name);
void    ft_check_info(t_cube3D *data);
void    ft_check_angle(float *angle);
void	ft_check_color(char *str);

//read_file

void    ft_get_info(t_cube3D *data, int fd);
char    **ft_fill_map(char *str, char **matrix, int fd, char *file_name);
int     ft_get_color(char *str);

//movements
int     ft_on(int keycode, t_cube3D *data);
int     ft_off(int keycode, t_cube3D *data);
void    ft_movements(t_cube3D *data);

//draw
void	my_pixel_put(t_image s_image, int x, int y, int color);
void    ft_draw_player(t_cube3D *data, int x, int y);
void    ft_draw_cell(t_cube3D *data, int x, int y, int c);
int     ft_draw(t_cube3D *data);
void    ft_draw_minimap(t_cube3D *data);

int     ft_exit(t_cube3D *data);

//texture
t_texture   ft_assign_text(char *path, t_cube3D *data);
int	        gettextcolor(int x, int y, t_texture text);void    ft_init_texture(t_cube3D *data);
void	    text_pixel_put(t_cube3D *data, t_ray *r, int *y, t_texture text);

#endif
