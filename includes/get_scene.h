/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smashele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 15:59:25 by smashele          #+#    #+#             */
/*   Updated: 2016/08/08 16:53:52 by smashele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_SCENE_H
# define GET_SCENE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define D1	':'
# define D2	';'
# define NAME	name
# define RED	red
# define GREEN	green
# define BLUE	blue
# define REF	reflection
# define POS_X	position_x
# define POS_Y	position_y
# define POS_Z	position_z
# define RAD	radius
# define LEN_X	length_x
# define LEN_Y	length_y
# define LEN_Z	length_z

typedef struct	s_object
{
	char		*NAME;
	float		RED;
	float		GREEN;
	float		BLUE;
	float		REF;
	float		POS_X;
	float		POS_Y;
	float		POS_Z;
	float		RAD;
	float		LEN_X;
	float		LEN_Y;
	float		LEN_Z;
	struct		s_object *next;
}				t_object;

t_object	*fresh_pony();
t_object	*get_scene(char *name);
char		*clone(char **s, int count, int size);
char		*unicorn_name(char *s, int a);
int			f_cmp(const char *s1, const char *s2, int a);
float		f_atof(const char *s, int a);

#endif
