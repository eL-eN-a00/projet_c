#include "coord.h"
#include <math.h>

coord_t creer_coord(int x, int y)
{
    coord_t p;
    p.x = x;
    p.y = y;
    return p;
}

int get_x(coord_t p)
{
    return p.x;
}

int get_y(coord_t p)
{
    return p.y;
}

void set_x(coord_t *p, int x)
{
    p->x = x;
}

void set_y (coord_t *p, int y)
{
    p->y = y;
}

bool memes_coord(coord_t p1, coord_t p2)
{
    return (p1.x == p2.x) && (p1.y == p2.y);
}

coord_t translation(coord_t p, int dx, int dy)
{
    coord_t resultat;
    resultat.x = p.x + dx;
    resultat.y = p.y + dy;
    return resultat;
}

float distance_euclidienne(coord_t p1, coord_t p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrtf((float)(dx * dx + dy * dy));
}
