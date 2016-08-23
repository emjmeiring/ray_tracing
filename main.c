#include "includes/rt.h"
#include "includes/get_scene.h"

float	length2(t_ray *r)
{
	float x;

	x = r->dir.x * r->dir.x + r->dir.y * r->dir.y + r->dir.z * r->dir.z;
	return (x);
}

t_vec	normalize(t_ray *r)
{
	float	len;
	float	bla;
	t_vec	dir;

	bla = length2(r);
	if (bla > 0)
	{
		len = 1.f / sqrt(bla);
		//printf("1x=%f==\n", r->dir.x);
			//printf("1y=%f==\n", r->dir.y);
			//printf("1z=%f==\n", r->dir.z);
			//printf("1len		%f\n", sqrt(length2(r)));
		dir.x = r->dir.x * len;
		dir.y = r->dir.y * len;
		dir.z = r->dir.z * len;
		//printf("2x=%f==\n", dir.x);
		//printf("2y=%f==\n", dir.y);
		//printf("2z=%f==\n", dir.z);
		//printf("2len		%f\n", sqrt(length2(r)));
	}
	return (dir);
}

t_color		trace(t_ray *r, t_object *objects, int depth)
{
	t_color		pixel;
	t_object	*sphere;
	t_object	*pony;
	float		tclosest;
	float		t0;
	float		t1;
	static int i =0;
	sphere = NULL;
	pony =	objects;
	t0 = INF;
	t1 = INF;
	tclosest = INF;
	while (pony)
	{
//printf("^^%f^%f^^\n", t[0], t[1]);//printf("pos = #%f#%f#%f#\n", pony->position_x, pony->position_y, pony->position_z);
		if (intersect_sphere(r, pony, &t0, &t1))
		{
//i++;//printf("hit");//printf("name: %s\n", pony->name);//printf("**%p**\n", sphere);
			t0 < 0 ? t0 = t1 : 0;
			if (t0 < tclosest)
			{
				tclosest = t0;
				sphere = pony;
//printf("**%p**\n", sphere);
			}
		}
//printf("2^^%f^%f^^\n", t[0], t[1]);//printf("name:		%s\n", pony->name);
			//printf("**%p**\n", sphere);
		pony = pony->next;
	}
	if(return)
		sphere t_vec{2,2,2};
	
//printf(" :%d: ", i);
	return (pixel);
}
//remove this pony if getsnene works
t_object	*my_pony(void)
{
	t_object	*pony;
	static int i=0;
	pony = (t_object*)malloc(sizeof(t_object));
	pony->name = "sphere";
	pony->red = 200;
	pony->green = 100;
	pony->blue = 255;
	pony->reflection = 1;
	pony->position_x = 0;
	pony->position_y = i;
	pony->position_z = -20;
	pony->radius = 2*(++i);
	pony->radius_x2 = pony->radius*pony->radius;
	pony->length_x = 0;
	pony->length_y = 0;
	pony->length_z = 0;
	pony->next = NULL;
	return (pony);
}

void le_main(t_object *objects)
{
	t_object		*pony;
	t_ray			r;
	t_index			num;
	unsigned char	img[WIDTH * HEIGHT * 3];
	t_color			pixel;

	r.origin.x = 0;
	r.origin.y = 0;
	r.origin.z = 0;
	set_up_num(&num);
	objects = my_pony();
	objects->next = my_pony();
	while (num.i < HEIGHT)
	{
		num.j = 0;
		num.y_dir = (1 - 2 * ((num.i + 0.5f) * num.inv_h)) * num.angle;
		while (num.j < WIDTH)
		{
			num.x_dir = (2 * ((num.j + 0.5f) * num.inv_w) - 1) * num.angle * 							num.aspect_r;
			r.dir.x = num.x_dir;
			r.dir.y = num.y_dir;
			r.dir.z = -1.f;
			
			/*printf("1x=%f==\n", r.dir.x);
			printf("1y=%f==\n", r.dir.y);
			printf("1z=%f==\n", r.dir.z);
			printf("1len		%f\n", sqrt(length2(&r)));
			*/
			r.dir = normalize(&r);
			pixel = trace(&r, objects, 0);
			/*
			printf("x=%f==\n", r.dir.x);
			printf("y=%f==\n", r.dir.y);
			printf("z=%f==\n", r.dir.z);
			printf("len		%f\n", sqrt(length2(&r)));
			//printf("**%f**\n", r.dir.x);*/
			num.j++;
		}
		num.i++;
	}
	
	
	/*
	pony = objects;
	for(i=0;i<HEIGHT;i++){
		r.origin.y = i;
		for(j=0;j<WIDTH;j++){
			r.origin.x = j;
			while (pony)
			{
				t = 2000.00f;
				s.position.x = pony->position_x;
					//printf("**%f**", s.position.x);
				s.position.y = pony->position_y;
				s.position.z = pony->position_z;
				s.radius = pony->radius;
					//printf("**%f**", s.radius);
				hit = intersect_sphere(&r, &s, &t);
					//printf("-%d-", hit);
				if(hit)
				{
					img[(j + i*WIDTH)*3 + 0] = 255;
					img[(j + i*WIDTH)*3 + 1] = 190;
					img[(j + i*WIDTH)*3 + 2] = 0;
				}else
				{
					img[(j + i*WIDTH)*3 + 0] = 219;
					img[(j + i*WIDTH)*3 + 1] = 20;
					img[(j + i*WIDTH)*3 + 2] = 147;
				}
				pony = pony->next;
			}
			pony = objects;
		}
	}
	save_xpm("scene1.xpm", img, WIDTH, HEIGHT);
*/
}

int	main(int argc, char **argv)
{
	int		a;
	t_object	*pony;
	t_object	*objects;
	
	if (argc != 2)
		return (0);
	while (*++argv)
	{
		objects = get_scene(*argv);
		pony = objects;
		while (pony)
		{
			printf("%s - name:		%s\n", *argv, pony->name);
			printf("%s - red:		%f\n", *argv, pony->red);
			printf("%s - green:		%f\n", *argv, pony->green);
			printf("%s - blue:		%f\n", *argv, pony->blue);
			printf("%s - reflection:	%f\n", *argv, pony->reflection);
			printf("%s - position_x:	%f\n", *argv, pony->position_x);
			printf("%s - position_y:	%f\n", *argv, pony->position_y);
			printf("%s - position_z:	%f\n", *argv, pony->position_z);
			printf("%s - radius:		%f\n", *argv, pony->radius);
			printf("%s - radius_x2:	%f\n", *argv, pony->radius_x2);
			printf("%s - length_x:	%f\n", *argv, pony->length_x);
			printf("%s - length_y:	%f\n", *argv, pony->length_y);
			printf("%s - length_z:	%f\n\n", *argv, pony->length_z);
			pony = pony->next;
		}
	}
	le_main(objects);
	pony_freedom(objects);
	return (2000);
}


/*
printf("**%d**\n", num.i);
	printf("**%d**\n", num.j);
	printf("**%d**\n", num.k);
	printf("**%f**\n", num.inv_width);
	printf("**%f**\n", num.inv_height);
	printf("**%f**\n", num.f_v);
	printf("**%f**\n", num.aspect_r);
	printf("**%f**\n", num.angle);*/
