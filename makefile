#Author :Tharindra Galahena
#Project:swap_wall
#Date   :11/06/2012

CC    = gcc
FILES = swap_wall.c
FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gconf-2.0)

all:
	$(CC) -o swap_wall $(FILES) $(FLAGS)
