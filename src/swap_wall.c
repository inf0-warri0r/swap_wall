/*
*Author :Tharindra Galahena charles de Cuckmagne IV
*Project:swap_wall(desktop wallpaper changer for linux)
*Date   :11/06/2012
*/

#include <stdlib.h>
#include <time.h>
#include <gconf/gconf-client.h>
#include <stdio.h>
#include <glib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "swap_wall.h"
#include "read_file.h"

char *current_dir;
int time_gap = 10;
char *style;

gboolean get_image(char *name)
{
	char *image_name = malloc(strlen(current_dir) + strlen(name) + 2);
	strcpy(image_name, current_dir);
	strcat(image_name, name);
	return set_wallpaper(image_name, style);
}

void read_images()
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(current_dir);

	if(dir != NULL){
		while((ent = readdir(dir)) != NULL){

			struct stat st_buf;
			stat(ent -> d_name, &st_buf);
			if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
				if (!get_image(ent -> d_name)) printf("Failed\n");
				sleep(time_gap);
			}
		}
		closedir(dir);
	}
}

gboolean set_wallpaper( const gchar *image_path, char *style)
{
    GConfClient *client;
    char *options = style;

    client = gconf_client_get_default();

    gconf_client_set_string( client,
		"/desktop/gnome/background/picture_filename",
		image_path,
		NULL );

    gboolean result = gconf_client_set_string( client,
		"/desktop/gnome/background/picture_options",
        options,
        NULL);
    g_object_unref( G_OBJECT(client) );
    return result;
}

void kill_wall(int pid)
{
	if(pid != 0) kill(pid, SIGKILL);
}

void start_wall()
{
	current_dir = malloc(40);
	style = malloc(20);
	read_config(current_dir, style, &time_gap);

	int pid = fork();
	if(!pid)
    {
        while(1)
        {
            read_images();
            sleep(time_gap);
        }
    }
    else
        write_pid(pid);
}

int parse_arguments(int argc, char *argv[])
{
    int option_index = 0, c, i, j = 0;

    while (1)
    {
        static struct option long_options[] = {
            {"restart", no_argument, 0, 'r'},
            {"stop", no_argument, 0, 's'},
            {0, 0, 0, 0}};

        c = getopt_long(
                argc,
                argv,
                "rs",
                long_options,
                &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            case 'r':
                kill_wall(read_pid());
                start_wall();
                break;

            case 's':
                kill_wall(read_pid());
                break;

            case '?':
                exit(EXIT_FAILURE);
                break;

            default:
                printf("Usage: swap_wall [--stop|restart]\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    parse_arguments(argc, argv);
    start_wall();
    return 0;
}
