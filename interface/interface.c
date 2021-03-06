
//gcc test.c -o test $(pkg-config --cflags --libs gtk+-2.0) -lallegro -lallegro_dialog

//This is only with allegro:
// Compile with -> gcc interface.c -o interface $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
// execute with -> ./interface

//This is with allegro and gtk:
//Compiling: gcc interface.c -o interface $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 gtk+-3.0 --libs --cflags)
//Exdcuting: ./interface
#include <pthread.h>
#include "interface.h"
/*
 * This function initialize all the required variables like the mapped maze in matrix, initial position of the martians
 * initial bar status, initial martian counter and the path of the different images of the martians.
 * */

void init_vars(){
    martian_counter = -1;
    bar_pos_x = 1100;
    bar_pos_y = 0;
    char * array_to_copy[] = {"../images/marciano1.png", "../images/marciano2.png", "../images/marciano3.png", "../images/marciano4.png","../images/marciano5.png"};
    int i = 0;
    while (i!=5){
        martian_color_array[i] = array_to_copy[i];
        i++;
    }
    i = 0;
    int j = 0;
    int matrix_to_copy[16][16] =  {
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

    while (i != 16){
        while (j!=16){
            matrix_maze[i][j] = matrix_to_copy[i][j];
            j++;
        }
        j=0;
        i++;
    }
    printf("El valor en matriz es %d",matrix_maze[1][2]);

}
int argc;
char *argv[];
/**
 * Le pasa el head que tiene mi process admin "processHeadList"
 * @param process_head
 */
void move_inside_intervals(struct process * process_head){
    int x_init_1 = 1300;
    int y_init_1 = 870;
    int index = 0;
    while (process_head!=NULL){
        printf("Entro a la función y al while\n");
        struct interval * to_move = process_head->intervalList;
        while (to_move!=NULL){
            //Aqui puede llamar el metodo, el proceso contiene el numero de alien y de ahi
            //le puede sacar el color y el numero para graficarlo, tambien saca el intervalo
            //META FUNCION AQUI

            int step = (int)1100/cycleNum;
            int init_x_pos = 1300;
            printf("Unidades de inicio %i\n", to_move->unitBegin);
            int a = (int)((to_move->unitBegin*step) + 1300);
            int b = (int)((to_move->unitEnd*step) + 1300);
            al_draw_filled_rectangle(a,y_init_1 ,b ,y_init_1+ 30 , al_map_rgba_f(MARTIAN_BARS[index].r, MARTIAN_BARS[index].g, MARTIAN_BARS[index].b, 0.5));

            to_move = to_move->nextInterval; // mueve al siguiente
        }
        y_init_1 -= 30;
        index++;
        process_head = process_head->next;
    }
}

int main(int argc, char *argv[]){
    inExecution=1;
    //pthread_t * threadPrinc = malloc(sizeof(pthread_t));
    //pthread_create(threadPrinc,NULL, &execute_main_thread, NULL);
    start = false;
    pause_ = false;
    init_vars();
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    //ALLEGRO_DISPLAY* disp = al_create_display(2000, 1024);
    disp = al_create_display(2500, 1024);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* laberinto = al_load_bitmap("../images/laberinto.png");
    must_init(laberinto, "laberinto");

    must_init(al_init_primitives_addon(), "primitives"); //For creating shapes.

    //al_init_native_dialog_addon();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

//    //create a martian:
//    create_martian(0,0,1,1);
//    create_martian(3,3,1,1);

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    //counters for the matrix:
    int counter_x = 0;
    int counter_y = 0;

    al_start_timer(timer);

    //main loop.
    create_martian(0,0,0,0);

//    create_head_thread_safe(3,8);
//    add_process_list_thread_safe(15,7);
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
                if(event.keyboard.keycode == ALLEGRO_KEY_UP){
                    move_martian(1, MARTIANS[1].matrix_position_x, MARTIANS[1].matrix_position_y-=1);
                    reduce_bar(1, 1);
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                    move_martian(1, MARTIANS[1].matrix_position_x, MARTIANS[1].matrix_position_y+=1);
                    reduce_bar(1, 1);
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    //create_martian(martian_counter,martian_counter);
                    interface_init_manual(argc, argv);
                    g_free(md);
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_N){
                    show_warning(1);
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_R){ //RF mode
                    if (start == false){
                        mode = 1;
                        pthread_t * threadPrinc = malloc(sizeof(pthread_t));
                        pthread_create(threadPrinc,NULL, &execute_main_thread, NULL);
                        start = true;
                    }else{
                        continue;
                    }
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_E){ //EDF mode.
                    if (start == false){
                        mode = 0;
                        pthread_t * threadPrinc = malloc(sizeof(pthread_t));
                        pthread_create(threadPrinc,NULL, &execute_main_thread, NULL);
                        start = true;
                    }else{
                        continue;
                    }
                }

                if(event.keyboard.keycode == ALLEGRO_KEY_X){// Stop the excecution and show the graphics.
                    printf("Cycles -> %d\n", cycleNum);
                    stop_execution_var = -1;
                    pause_ = true;
                    //break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_Q){
                    restart_interface();
                }
                if(event.keyboard.keycode != ALLEGRO_KEY_SPACE){
                    break;
                }

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;
        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 1030, 530, 0, "SALIDA");
            al_draw_bitmap(laberinto, 0, 0, 0);
            if(mode == 1){
                al_draw_text(font, al_map_rgb(255, 255, 255), 1030, 560, 0, "Modo RF");
            }else if(mode == 0){
                al_draw_text(font, al_map_rgb(255, 255, 255), 1030, 560, 0, "Modo EDF");
            }

            //Aca se puede poner alguna logica.

            //If pause is true, then the report is shown.
            if(pause_ == true){
                int step = (int)1100/cycleNum;
                int init_x_pos = 1300;
                for (int i = 0; i <= cycleNum; i++){
                    al_draw_line(init_x_pos, 50, init_x_pos, 900, al_map_rgb_f(255, 255, 255), 1);
                    init_x_pos += step;
                }
                init_x_pos += step;
                al_draw_line(init_x_pos, 50, init_x_pos, 900, al_map_rgb_f(255, 255, 255), 1);
                al_draw_line(1300, 900, 2400, 900, al_map_rgb_f(255, 255, 255), 2);
                al_draw_text(font, al_map_rgb_f(255, 255, 255), 1850, 930, 0, "Ciclos(1 segundo)");


                move_inside_intervals(processHeadList);

            }

            //This "for" refresh the display, printing al the status of the martians and the life bars.
           for (int i = 0; i < martian_counter; i++)
           {
               al_draw_bitmap(MARTIANS[i].martian_color, MARTIANS[i].pos_x, MARTIANS[i].pos_y, 0);
               al_draw_filled_rectangle(MARTIAN_BARS[i].dot_x1, MARTIAN_BARS[i].dot_y1, MARTIAN_BARS[i].dot_x2, MARTIAN_BARS[i].dot_y2, al_map_rgba_f(MARTIAN_BARS[i].r, MARTIAN_BARS[i].g, MARTIAN_BARS[i].b, 0.5));
               al_draw_text(MARTIAN_BARS[i].font, al_map_rgb(255, 255, 255), MARTIAN_BARS[i].dot_x2, MARTIAN_BARS[i].dot_y1, 0, MARTIAN_BARS[i].str);
           }



           //al_draw_filled_rectangle(1100, 0, 1250, 50, al_map_rgba_f(0, 0, 0.5, 0.5));

            //Everything here will be shown.
            al_flip_display();



            redraw = false;
        }
    }

    al_destroy_bitmap(laberinto);
    //Este for debe estar para eliminar estos marcianos.
    for (int i = 0; i < martian_counter; i++)
    {
        al_destroy_bitmap(MARTIANS[i].martian_color);
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

}

/*
 * must_init function verifies the status of each intialization, ensuring everything goes well. Its params are
 * the object to evaluate and a description given. If the object intialization is false, then the program
 * shuts down.
 * */
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

/*
 * matric_to_image convert some position in the matrix that describes the maze, and convert the values in to
 * canvas numbers. The new values that are traduce are passed by reference, so those params are the outout of the current
 * function.
 * */

void matrix_to_image(int x_matrix, int y_matrix, int *x_image, int *y_image){
    (*x_image) = 64*x_matrix;
    (*y_image) = 64*y_matrix;
}

/*
 * is_valid_pos return false if the cordinates that are consulted are available for the martian to go ahead or not.
 * The params are a certain pair of coordinates.
 * */

bool is_valid_pos(int x, int y){
    if (x<0 || y<0){
        return false;
    }
    if (x>=16 || y>=16){
        return false;
    }
    if (matrix_maze[y][x] != 0){
        return false;
    }else{
        return true;
    }
}

/*
 * create_martian abstracts the way of creating martians. It takes the initial position, the energy and period to
 * create the martian in a correct way. It returns the martian id for future references.
 * */

int create_martian(int pos_x, int pos_y, int energy, int period){
    int pos_x_converted = 0;
    int pos_y_converted = 0;
    matrix_to_image(pos_x, pos_y, &pos_x_converted, &pos_y_converted);
    struct martian new_Martian;
    new_Martian.id = martian_counter;
    new_Martian.matrix_position_x = pos_x;
    new_Martian.matrix_position_y = pos_y;
    new_Martian.pos_x = pos_x_converted;
    new_Martian.pos_y = pos_y_converted;
    new_Martian.color = rand()%4;
    new_Martian.martian_color = al_load_bitmap(martian_color_array[new_Martian.color]);
    new_Martian.energy = energy;
    new_Martian.energy_backup = energy;
    new_Martian.period = period;
    MARTIANS[martian_counter] = new_Martian;
    martian_counter++;
    martian_bar(new_Martian.id, new_Martian.color);
    return new_Martian.id;
}

/*
 * move_martian uses the id of a certain martian, and the new x and y position to be moved.
 * */

void move_martian(int id, int x, int y){
    int new_x = 0;
    int new_y = 0;
    MARTIANS[id].matrix_position_x = x;
    MARTIANS[id].matrix_position_y = y;
    matrix_to_image(x, y, &new_x, &new_y);
    MARTIANS[id].pos_x = new_x;
    MARTIANS[id].pos_y = new_y;
}

/*
 * martian_bar creates a life bar for each created martian. It only takes the id of the martian and the color, then
 * it is assign to the bar.
 * */

void martian_bar(int id, int color){
    struct life_bar new_Bar;
    new_Bar.id = id;
    new_Bar.dot_x1 = bar_pos_x;
    new_Bar.dot_x2 = bar_pos_x + 150;
    new_Bar.dot_y1 = bar_pos_y + (id)*50;
    new_Bar.dot_y2 = new_Bar.dot_y1 + 50;
    if (color == 0){ // The martian is blue
        new_Bar.r = 0;
        new_Bar.g = 0;
        new_Bar.b = 255;
    }else if (color == 1){ // The martian is red
        new_Bar.r = 255;
        new_Bar.g = 0;
        new_Bar.b = 0;
    }else if (color == 2){ // The martian is green
        new_Bar.r = 0;
        new_Bar.g = 255;
        new_Bar.b = 0;
    }else if (color == 3){ // The martian is purple
       new_Bar.r = 230;
       new_Bar.g = 0;
       new_Bar.b = 255;
    }else if (color == 4){ // The martian is light green
        new_Bar.r = 0;
        new_Bar.g = 255;
        new_Bar.b = 200;
    }
    new_Bar.font = al_create_builtin_font();
    sprintf(new_Bar.str, "%d", new_Bar.id);
    MARTIAN_BARS[id] = new_Bar;
}

/*
 * reduce_bar takes a certain bar and reduces it as the life of the martian decreases, so it is posible to
 * watch what is the status in the interface. It takes the id of the martian and the percentage of reduction.
 * */
void reduce_bar(int id, float percentage){
    if (MARTIAN_BARS[id].dot_x2 <= MARTIAN_BARS[id].dot_x1){
        MARTIAN_BARS[id].dot_x2 = MARTIAN_BARS[id].dot_x1;
        MARTIANS[id].energy = 0;
        //reload_bar(id);
    }else{
        //percentage = 1 - percentage;
        MARTIAN_BARS[id].dot_x2 =  (int)(MARTIAN_BARS[id].dot_x1+150 - 150*percentage);//(int)(MARTIAN_BARS[id].dot_x2 - MARTIAN_BARS[id].dot_x1)*percentage/150;
        printf("Percentage %f\n", percentage);
        printf("%i\n", (MARTIAN_BARS[id].dot_x2 - MARTIAN_BARS[id].dot_x1) );
        MARTIANS[id].energy -= 1;
    }
}

/*
 * reload_bar is used only when a martian has reloaded energy, it is a simple representation in interface.
 * */
void reload_bar(int id){
    MARTIAN_BARS[id].dot_x2 = bar_pos_x + 150;
    MARTIANS[id].energy = MARTIANS[id].energy_backup;
}


/*
 * on_activate is an example of a generic window in GTK.
 * */
static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  //Resizing the window and make it not resizable.
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

  GtkWidget *entry = gtk_entry_new ();
  GtkWidget *label = gtk_label_new_with_mnemonic ("_Hello");
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), entry);
  // Create a new button
  GtkWidget *button = gtk_button_new_with_label ("Hello, World!");
  // When the button is clicked, close the window passed as an argument
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);

  //gtk_container_add(GTK_CONTAINER(window), entry);
  gtk_container_add(GTK_CONTAINER(window), label);
  //gtk_container_add(GTK_CONTAINER(window), button);
  gtk_widget_show_all (window);
}
//-----------------Manual mode-------------------------------//
/*
 * button_get_info get the information inside the text entries in which the user assign a period and life. It takes
 * the window attached(father window) and a pointer assigned to the data from the entries.
 * */
static void button_get_info(GtkWidget *widget, gpointer data){
    printf("Hola\n");
    martian_data* md = (martian_data*)data;
    const gchar *period;
    const gchar *energy;

    period = gtk_entry_get_text (GTK_ENTRY (md->period));
    energy = gtk_entry_get_text (GTK_ENTRY (md->energy));
    g_print ("Contents of entries:\n%s\n%s\n", period, energy);

    int martian_period = atoi(period);
    int martian_energy = atoi(energy);

    if (martian_period <= 0 || martian_energy <= 0){
        show_warning_values();
    }else{
        add_process_list_thread_safe(martian_period, martian_energy);
    }


    printf("Period %i and energy %i\n", martian_period, martian_energy);


}

/*
 * new_martian_window helps the user in creating a new martian with period and the energy attached to each martian.
 * It takes the father window as a param.
 * */
static void new_martian_window(GtkApplication *app){
    GtkWidget *window = gtk_application_window_new (app);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    GtkWidget *table = gtk_table_new(3, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    GtkWidget *label_period = gtk_label_new("Período:");
    GtkWidget *label_energy = gtk_label_new("Energía:");

    gtk_table_attach(GTK_TABLE(table), label_period, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label_energy, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    //GtkWidget *entry_period = gtk_entry_new();
    //GtkWidget *entry_energy = gtk_entry_new();

    md = g_malloc(sizeof(*md));

    md->period = gtk_entry_new();
    md->energy = gtk_entry_new();


    gtk_table_attach(GTK_TABLE(table), md->period, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), md->energy , 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    GtkWidget *button = gtk_button_new_with_label ("Agregar Marciano");
    gtk_table_attach(GTK_TABLE(table), button, 1, 2,2,3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    //g_signal_connect_swapped (button, "clicked", G_CALLBACK(button_get_info), (gpointer) md);
    g_signal_connect (button, "clicked", G_CALLBACK(button_get_info), (gpointer) md);

    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_show_all (window);
}

/*
 * interface_init_manual starts a main window GTK application that gets params from executable.
 * */
int interface_init_manual(int argc, char *argv[]){
    GtkApplication *app = gtk_application_new ("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);
    //g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
    g_signal_connect (app, "activate", G_CALLBACK (new_martian_window), NULL);
    return g_application_run (G_APPLICATION (app), argc, argv);
}

/*
 * show_warning is used to show everytime a set of processes are not schedule available. It takes as a param the
 * id of certain process.
 * */
void show_warning(int id) {

    //GtkApplication *app = gtk_application_new ("com.example.GtkApplication1", G_APPLICATION_FLAGS_NONE);
    //GtkWindow *window = gtk_application_window_new (app);
    gtk_init(&argc, &argv);
    const char str[5];
    sprintf(str, "%d", id);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "No se puede calendarizar los procesos, error critico en el sistema cierre la aplicacion.");

    gtk_window_set_title(GTK_WINDOW(dialog), str);
    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);

    gtk_window_close(GTK_WINDOW(dialog));
}

/*
 * show_warning_values is used when the user does not assign a positive and greatter than 0 values to period and
 * energy to a certain martian.
 * */
void show_warning_values() {

    //GtkApplication *app = gtk_application_new ("com.example.GtkApplication1", G_APPLICATION_FLAGS_NONE);
    //GtkWindow *window = gtk_application_window_new (app);
    gtk_init(&argc, &argv);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_WARNING,
                                               GTK_BUTTONS_OK,
                                               "Por favor ingrese valores de energia y periodo mayores a 0.");

    gtk_window_set_title(GTK_WINDOW(dialog), "Error en los valores de ingreso");
    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);

    gtk_window_close(GTK_WINDOW(dialog));
}

/*
 * restart_interface is used in case the user want to restart the entire program. It cleans martian array,
 * martian bars array, start and pause flags, and re init the variables.
 * */
void restart_interface(){
    memset(MARTIANS, 0, sizeof(struct martian));
    memset(MARTIAN_BARS, 0, sizeof(struct life_bar));
    martian_counter = -1;
    start = false;
    pause_ = false;
    struct martian MARTIANS[100]; // Array of martians.
    struct life_bar MARTIAN_BARS[100];
    init_vars();
}

