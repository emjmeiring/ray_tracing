/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smashele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 12:45:52 by smashele          #+#    #+#             */
/*   Updated: 2016/08/21 12:45:55 by smashele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_SCENE_H
# define GET_SCENE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define R1		pony->radius

typedef struct	s_mem_list
{
	void				*address;
	struct s_mem_list	*next;
}				t_mem_list;

typedef struct	s_object
{
	char			*name;
	float			red;
	float			green;
	float			blue;
	float			reflection;
	float			position_x;
	float			position_y;
	float			position_z;
	float			radius;
	float			radius_x2;
	float			length_x;
	float			length_y;
	float			length_z;
	struct s_object *next;
}				t_object;

t_object		*fresh_pony(void);
t_object		*get_scene(char *name);
char			*clone(char **s, int count, int size);
char			*unicorn_name(char *s, int a);
int				f_cmp(const char *s1, const char *s2, int a);
void			pony_freedom(t_object *first);
float			f_atof(const char *s, int a);

#endif
