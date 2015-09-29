/*
*Author :Tharindra Galahena Charles de Cuckmagne IV
*Project:swap_wall(desktop wallpaper changer for linux)
*Date   :11/06/2012
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "swap_wall.h"
#include "read_file.h"
#include "error.h"

void read_config(char *dir, char *style, int *time_gap){

	char *config_name = "config.default";
	char *home_dir = getenv("HOME");
	char *config_path = malloc(strlen(home_dir) + strlen(config_name) + 2);

    sprintf(config_path, "%s/%s", home_dir, config_name);
    printf("%s\n", config_path);

    FILE *fr = fopen(config_path, "rt");
	if (fr == NULL)
        die(errno);

	char *line = malloc(40);
	fgets(line, 40, fr);
    printf(line);
	strcpy(dir, &line[4]);
	dir[strlen(dir)] = '\0';
    printf(dir);
	free(line);

	line = malloc(20);
	fgets(line, 20, fr);
	strcpy(style, &line[6]);
	style[strlen(style) - 1] = '\0';
	free(line);

	char *timeout = malloc(20);
	fgets(timeout, 20, fr);
	*time_gap = atoi(&timeout[5]);
    free(timeout);
    free(config_path);
	fclose(fr);
}

char *get_pid_path()
{
	char *home_dir = getenv ("HOME");
	char *pid_file = ".pid_wall";
    char *pid_path = malloc(strlen(home_dir) + strlen(pid_file) + 2);
    /* ^^ +2: one for '/' and one for '\0' (given by sprintf) ^^ */

    if (sprintf(pid_path, "%s/%s", home_dir, pid_file) <= 0)
        exit(EXIT_FAILURE);

    return pid_path;
}

void write_pid(int pid)
{
	char *pid_path = get_pid_path();
	FILE *fp = fopen(pid_path, "w+");

    if (fp == NULL)
        die(errno);

	char buf[6];
	sprintf(buf, "%d", pid);
	fprintf(fp, buf);

    fclose(fp);
    free(pid_path);
}

int read_pid()
{
    char *pid_path = get_pid_path();
    FILE *fp = fopen(pid_path, "r+");

    if (fp == NULL)
        die(errno);

    char buf[6];
    fgets(buf, 20, fp);

    fclose(fp);
    return atoi(buf);
}
