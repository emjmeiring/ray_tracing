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

static int	ft_ilen(int n)
{
	int	i;
	
	i = 0;
	if (n < 0)
		i += 1;
	while (n /= 10)
		i += 1;
	return (i + 1);
}

char		*ft_itoa(int n)
{
	char	*str;
	
	if ((str = (char*)malloc(sizeof(char) * ft_ilen(n))) == NULL)
		return (NULL);
	if (n >= 0)
	{
		while (n != 0)
		{
			*--str = '0' + (n % 10);
			n /= 10;
		}
		return (str);
	}
	else
	{
		while (n != 0)
		{
			*--str = '0' - (n % 10);
			n /= 10;
		}
		*--str = '-';
	}
	return (str);
}

void	save_xpm(char *f_name, unsigned char *image, int width, int height)
{
	FILE *file;

	file = fopen(f_name, "w");
	fprintf(file, "P6 %d %d %d\n", width, height, 255);
	fwrite(image, 3, width*height, file);
	fclose(file);
}
/*
#define WIDTH  800
#define HEIGHT 500

int main(){
	
	unsigned char img[WIDTH * HEIGHT * 3];
	int i,j;
	
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			if( intersect_sphere( ){
				img[(j + i*WIDTH)*3 + 0] = 0;
				img[(j + i*WIDTH)*3 + 1] = 0;
				img[(j + i*WIDTH)*3 + 2] = 128;
			}else{
				img[(j + i*WIDTH)*3 + 0] = 255;
				img[(j + i*WIDTH)*3 + 1] = 255;
				img[(j + i*WIDTH)*3 + 2] = 255;
			}
		}
		
	}
	
	save_xpm("scene1.xpm", img, WIDTH, HEIGHT);
	
	return 0;
}
*/