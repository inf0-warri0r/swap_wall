#ifndef _SWAP_WALL_H_
#define _SWAP_WALL_H_
#include <glib.h>
gboolean set_wallpaper( const gchar*, char*);
gboolean get_image(char *name);
void read_images();
void kill_wall(int);
void start_wall();
int parse_arguments(int, char**);
int main(int, char**);
#endif /* _SWAP_WALL_H_ */
