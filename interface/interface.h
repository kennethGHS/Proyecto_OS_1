//
// Created by kenneth on 26/10/20.
//

#ifndef PROYECTO_OS_1_INTERFACE_H
#define PROYECTO_OS_1_INTERFACE_H
#include "../ThreadManagement/process_admin.h"
#include "../BasicStructures/interval_structure.h"
#include "../BasicStructures/process_structure.h"

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <unistd.h>
#include <gtk/gtk.h>

int matrix_maze[16][16] ;
const char *martian_color_array[5] ;
bool start;
bool pause_;
struct martian
{
    int matrix_position_x;         // X position in matrix
    int matrix_position_y;         // Y position in matrix
    int pos_x;                     // X position in canvas
    int pos_y;                     // Y position in canvas
    int id;                        // List position.
    int color;                     // color of the martian
    int energy;
    int energy_backup;
    int period;
    ALLEGRO_BITMAP* martian_color; // Image.
};

struct life_bar{
    int id;
    int dot_x1;
    int dot_x2;
    int dot_y1;
    int dot_y2;
    int r;
    int g;
    int b;
    ALLEGRO_FONT* font;
    char str[4];
};

typedef struct martian_data
{
    GtkWidget *period;
    GtkWidget *energy;
} martian_data;
martian_data* md;

struct martian MARTIANS[100]; // Array of martians.
struct life_bar MARTIAN_BARS[100]; // Array of martian bars.

//------Some usefull funtions-----------------
void must_init(bool test, const char *description);
void matrix_to_image(int x_matrix, int y_matriz, int *x_image, int *y_image);
bool is_valid_pos(int x, int y);
int create_martian(int pos_x, int pos_y, int energy, int period);
void move_martian(int id, int x, int y);
void martian_bar(int id, int color);
void reduce_bar(int id, float percentage);
void reload_bar(int id);
void init_vars();
void move_inside_intervals(struct process * process_head);
//-----Some functions for interface--------
int interface_init_manual(int argc, char *argv[]);
static void on_activate (GtkApplication *app);
static void new_martian_window(GtkApplication *app);
static void button_get_info(GtkWidget *widget, gpointer data);
void show_warning(int id);
int martian_counter ;
int bar_pos_x ;// First bar
int bar_pos_y ;   // First bar
ALLEGRO_KEYBOARD_STATE ks;
ALLEGRO_DISPLAY* disp;
char period[10];
char energia[10];
#endif //PROYECTO_OS_1_INTERFACE_H
