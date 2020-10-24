#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// Compile with -> gcc mapeo.c -o mapeo $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
// execute with -> ./mapeo



int matrix_maze[16][16] = {
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //1
                            {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1}, //2
                            {1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1}, //3
                            {1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1}, //4
                            {1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1}, //5
                            {1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1}, //6
                            {1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1}, //7
                            {1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1}, //8
                            {1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0}, //9
                            {1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1}, //10
                            {1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1}, //11
                            {1,0,1,1,0,1,1,1,1,0,0,0,1,0,1,1}, //12
                            {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1}, //13
                            {1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1}, //14
                            {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1}, //15
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //16    
                          };
const char *martian_color_array[] = {"marciano1.png", "marciano2.png", "marciano3.png", "marciano4.png","marciano5.png"};
struct martian
{
    int pos_x;
    int pos_y;
    int id;
    ALLEGRO_BITMAP* martian_color;
};
struct martian MARTIANS[100]; // Array of martians.

void must_init(bool test, const char *description);
void matrix_to_image(int x_matrix, int y_matriz, int *x_image, int *y_image);
bool is_valid_pos(int x, int y);
void create_martian(int id, int pos_x, int pos_y);
void move_martian(int id, int x, int y);


int main(){
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(1024, 1024);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* laberinto = al_load_bitmap("laberinto.png");
    must_init(laberinto, "laberinto");


    ALLEGRO_BITMAP* marciano1 = al_load_bitmap("marciano1.png");
    must_init(marciano1, "marciano1");

    ALLEGRO_BITMAP* marciano2 = al_load_bitmap("marciano2.png");
    must_init(marciano2, "marciano1");

    ALLEGRO_BITMAP* marciano3 = al_load_bitmap("marciano3.png");
    must_init(marciano3, "marciano1");

    ALLEGRO_BITMAP* marciano4 = al_load_bitmap("marciano4.png");
    must_init(marciano4, "marciano1");

    ALLEGRO_BITMAP* marciano5 = al_load_bitmap("marciano5.png");
    must_init(marciano5, "marciano5");

    must_init(al_init_primitives_addon(), "primitives"); //For creating shapes.

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //create a martian:
    create_martian(0,0,0);
    create_martian(1, 3,3);

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_draw_bitmap(laberinto, 0, 0, 0);
            //For the first martian-------------------------------------------------
            int matrix_x = 0;
            int matrix_y = 1;
            int image_x = 0;
            int image_y = 0;
            matrix_to_image(matrix_x, matrix_y, &image_x, &image_y);
            al_draw_bitmap(marciano1, image_x, image_y, 0);
            //----------------------------------------------------------------------
            //For the second martian------------------------------------------------
            int matrix2_x = 1;
            int matrix2_y = 1;
            int image2_x = 0;
            int image2_y = 0; 
            matrix_to_image(matrix2_x, matrix2_y, &image2_x, &image2_y);
            al_draw_bitmap(marciano2, image2_x, image2_y, 0);
            //----------------------------------------------------------------------
            //For the third martian-------------------------------------------------
            int matrix3_x = 2;
            int matrix3_y = 1;
            int image3_x = 0;
            int image3_y = 0; 
            matrix_to_image(matrix3_x, matrix3_y, &image3_x, &image3_y);
            al_draw_bitmap(marciano3, image3_x, image3_y, 0);
            //----------------------------------------------------------------------
            //For the fourth martian-------------------------------------------------
            int matrix4_x = 3;
            int matrix4_y = 1;
            int image4_x = 0;
            int image4_y = 0; 
            matrix_to_image(matrix4_x, matrix4_y, &image4_x, &image4_y);
            al_draw_bitmap(marciano4, image4_x, image4_y, 0);
            //----------------------------------------------------------------------
            //For the fifth martian-------------------------------------------------
            int matrix5_x = 3;
            int matrix5_y = 2;
            int image5_x = 0;
            int image5_y = 0; 
            matrix_to_image(matrix5_x, matrix5_y, &image5_x, &image5_y);
            al_draw_bitmap(marciano5, image5_x, image5_y, 0);
            
            if (is_valid_pos(2,2)){
                printf("Si es valida esta posición\n");
            }else{
                printf("No es valida esta posicion.\n");
            }

            al_draw_bitmap(MARTIANS[0].martian_color, MARTIANS[0].pos_x, MARTIANS[0].pos_y, 0);
            al_draw_bitmap(MARTIANS[1].martian_color, MARTIANS[1].pos_x, MARTIANS[1].pos_y, 0);

            move_martian(0, 4,5);
            //Everything here will be shown.
            al_flip_display();

            
            


            redraw = false;
        }
    }

    al_destroy_bitmap(laberinto);
    al_destroy_bitmap(marciano1);
    al_destroy_bitmap(marciano2);
    al_destroy_bitmap(marciano3);
    al_destroy_bitmap(marciano4);
    al_destroy_bitmap(marciano5);
    al_destroy_bitmap(MARTIANS[0].martian_color);
    al_destroy_bitmap(MARTIANS[1].martian_color);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

}

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void matrix_to_image(int x_matrix, int y_matrix, int *x_image, int *y_image){
    (*x_image) = 64*x_matrix;
    (*y_image) = 64*y_matrix;
}

bool is_valid_pos(int x, int y){
    if (matrix_maze[x][y] == 1){
        return false;
    }else{
        return true;
    }
}

void create_martian(int id, int pos_x, int pos_y){
    int pos_x_converted = 0;
    int pos_y_converted = 0;
    matrix_to_image(pos_x, pos_y, &pos_x_converted, &pos_y_converted);
    struct martian new_Martian;
    new_Martian.id = id;
    new_Martian.pos_x = pos_x_converted;
    new_Martian.pos_y = pos_y_converted;
    new_Martian.martian_color = al_load_bitmap(martian_color_array[rand()%3]);
    MARTIANS[id] = new_Martian;
}

void move_martian(int id, int x, int y){
    int new_x = 0;
    int new_y = 0;
    matrix_to_image(x, y, &new_x, &new_y);
    MARTIANS[id].pos_x = new_x;
    MARTIANS[id].pos_y = new_y;
}