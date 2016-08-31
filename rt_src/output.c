/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 15:58:34 by jomeirin          #+#    #+#             */
/*   Updated: 2016/07/15 15:58:37 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	save_xpm(char *f_name, unsigned char *image, int width, int height)
{
	FILE *file;

	file = fopen(f_name, "w");
	fprintf(file, "P6\n %d %d \n%d\n", width, height, 255);
	fwrite(image, 3, width*height, file);
	fclose(file);
}
