/*
*Author :Tharindra Galahena
*Project:swap_wall(desktop wallpaper changer for linux)
*Date   :11/06/2012
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void read_config(char *dir, char *style, int *time_gap){

	char *config = "config.default";
	char *home_dir = getenv("HOME");
	char *config_path = malloc(strlen(home_dir) + strlen(config) + 2);

	strcpy(config_path, home_dir);
	strcat(config_path, "/");
	strcat(config_path, config);

	FILE *fr = fopen (config_path, "rt");

	char *line = malloc(40);
	fgets(line, 40, fr);
	strcpy(dir, &line[4]);
	dir[strlen(dir) - 1] = '\0';
	free(line);

	line = malloc(20);
	fgets(line, 20, fr);
	strcpy(style, &line[6]);
	style[strlen(style) - 1] = '\0';
	free(line);

	char *timeout = malloc(20);
	fgets(timeout, 20, fr);
	*time_gap = atoi(&timeout[5]);
	fclose(fr);
}

void write_pid(int pid){
	char *pid_file = ".pid_wall";
	char *home_dir = getenv ("HOME");
	char *pid_path = malloc(strlen(home_dir) + strlen(pid_file) + 2);

	strcpy(pid_path, home_dir);
	strcat(pid_path, "/");
	strcat(pid_path, pid_file);

	FILE *fp=fopen(pid_path, "w+");
	char buf[6];
	sprintf(buf, "%d", pid);
	fprintf(fp, buf);

	fclose(fp);
}

int read_pid(){
	char *pid_file = ".pid_wall";
	char *home_dir = getenv ("HOME");
	char *pid_path = malloc(strlen(home_dir) + strlen(pid_file) + 2);

	strcpy(pid_path, home_dir);
	strcat(pid_path, "/");
	strcat(pid_path, pid_file);

	FILE *fp=fopen(pid_path, "r+");
	char buf[6];
	fgets(buf, 20, fp);

	fclose(fp);

	return atoi(buf);
}
