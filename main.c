#include "includes/rt.h"
#include "includes/get_scene.h"

#define WIDTH  800
#define HEIGHT 600

void le_main(t_object *objects)
{
	t_object		*pony;
	t_sphere		s;
	t_ray			r;
	//material		met;
	int				i;
	int				j;
	unsigned char	img[WIDTH * HEIGHT * 3];
	int				hit;
	float			t;
	
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;
	r.origin.z = 0;
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
}

int	main(int argc, char **argv)
{
	int		a;
	t_object	*pony;
	t_object	*objects;

	a = 0;
	while (argv[++a])
	{
		objects = get_scene(argv[a]);
		pony = objects;
		while (pony)
		{
			printf("%s - name:		%s\n", argv[1], pony->NAME);
			printf("%s - red:		%f\n" , argv[1], pony->RED);
			printf("%s - green:		%f\n" , argv[1], pony->GREEN);
			printf("%s - blue:		%f\n" , argv[1], pony->BLUE);
			printf("%s - reflection:	%f\n" , argv[1], pony->REF);
			printf("%s - position_x:	%f\n" , argv[1], pony->POS_X);
			printf("%s - position_y:	%f\n" , argv[1], pony->POS_Y);
			printf("%s - position_z:	%f\n" , argv[1], pony->POS_Z);
			printf("%s - radius:		%f\n" , argv[1], pony->RAD);
			printf("%s - length_x:	%f\n" , argv[1], pony->LEN_X);
			printf("%s - length_y:	%f\n" , argv[1], pony->LEN_Y);
			printf("%s - length_z:	%f\n\n" , argv[1], pony->LEN_Z);
			pony = pony->next;
		}
	}
	le_main(objects);
	return (2000);
}

