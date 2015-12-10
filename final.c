#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "gfx4.h"
#include <time.h>
#include <string.h>

#define PI M_PI

typedef struct Fireball_S {
    double x_pos;
    double y_pos;
    double angle;
    double radius;
    double bounce_count;
} Fireball;

typedef struct Ladder_S {
    double x_pos; // bottom center
    double y_pos;
    int ch_x;
    double speed;
} Ladder;

typedef struct Mario_S {
    double x_pos;
    double y_pos;
    int draw_count;
    int draw_position;
} Mario;

typedef struct Luigi_S {
    double x_pos;
    double y_pos;
    int draw_count;
    int draw_position;
} Luigi;

typedef struct Peach_S {
    double x_pos; // bottom left
    double y_pos;
    int path_level;
    int is_climbing;
    int is_moving;
    int move_direction; // 1 - right, -1 - left
    int is_jumping;
    double jump_height;
    int jump_direction;
    double jump_speed;
    int is_falling;
    double fall_height;
    double fall_speed;
    double speed;
    int draw_count;
    int draw_position;
    int num_lives;
} Peach;

typedef struct Key_S {
    double x_pos;
    double y_pos;
    double angle;
    int exists;
    int caught;
    int intro_complete;
} Key;

typedef struct Trap_S {
    double x_pos;
    double y_pos;
    int length;
    int path_level;
    int state;
    int exists;
} Trap;

typedef struct Life_S {
    double x_pos;
    double y_pos;
    int path_level;
    int exists;
    int radius;
    int length;
    int count;
} Life;

// character graphics
typedef struct Coordinates_S {
    int x;
    int y;
    int width;
    int height;
    int color[3];
} Coord;

// global variables

int width = 700;
int height = 800;
int difficulty;
double timing;

Coord static_peach_right[49];
Coord moving_peach_right[50];
Coord static_peach_left[49];
Coord moving_peach_left[50];
Coord static_mario[274];
Coord talking_mario[296];

// function prototypes
void import_all();
void set_peach_color(int *,char);
void set_mario_color(int *,char);
void initial_make_all(Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);
void draw_all_static(Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);
void draw_character(int,int,int,int,int []);
void draw_lives(Peach *);
void reset_all(Fireball *,int *,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);

void new_fireball(Fireball *,int);
void draw_fireballs(Fireball *,int);
void draw_fireball(Fireball *,int);
void erase_fireballs(Fireball *,int);
void move_fireballs(Fireball *,Peach *,int *);
void remove_fireball(Fireball *,int,int);
int collided(Fireball *,Peach *,int);

void make_mario(Mario *);
void draw_mario(Mario *,Peach *);
void draw_static_mario(int,int,double);
void draw_talking_mario(int,int,double);
void erase_mario(Mario *);

void make_luigi(Luigi *);
void draw_luigi(Luigi *);

void draw_platform();
void draw_gate();

void make_peach(Peach *);
void reset_peach(Mario *,Luigi *,Peach *,Ladder *);
void draw_peach(Peach *);
void draw_static_peach(int,int,double,int);
void draw_moving_peach(int,int,double,int);
void draw_static_peach_right(int,int,double);
void draw_moving_peach_right(int,int,double);
void draw_static_peach_left(int,int,double);
void draw_moving_peach_left(int,int,double);
void erase_peach(Peach *);
void draw_peach_motion(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);
void move_peach(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *,int,int);
int peach_fall(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);
void peach_jump(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);

int catch_key(Peach *,Key *);
int collect_life(Peach *,Life *);

void make_ladders(Ladder *);
void move_ladders(Peach *,Ladder *);
void move_ladder(Peach *, Ladder *,int);
void draw_ladders(Ladder *);
void draw_ladder(Ladder *);
void erase_ladder(Ladder *);

void draw_paths();
void make_trap(Trap *);
void new_trap(Trap *);
void move_trap(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *);
void draw_trap(Trap *);
int check_trap(Peach *,Trap *);

void make_key(Key *);
void new_key(Key *);
void draw_key(Key *);
void move_key(Key *);
void erase_key(Key *);

void make_life(Life *);
void new_life(Peach *,Life *);
void draw_life(Life *);
void erase_life(Life *);

void menu_sequence();
void print_instructions();
void moving_sequence(Fireball *,int,Mario *,Luigi *,Peach *,Ladder *,Key *,Trap *,Life *,int *,int);
void intro_sequence();
void play_sequence();
int losing_sequence();
void ending_sequence();
int print_text(int,int,char [1000]);
int wait_input(int,int);
void clear_screen();

int in_bounds(int,int);

int main() {
    time_t t;
    srand((unsigned) time(&t));
    char userInput;

    Fireball fireballs[15];
    int numFireballs = 0;

    Ladder ladders[6];
    Mario mario;
    Luigi luigi;
    Peach peach;
    Key key;
    Trap trap;
    Life life;

    timing = pow(10,3.5);
    difficulty = 1;

    gfx_open(width,height,"Princess Peach");
    gfx_clear_color(0,0,0);
    gfx_clear();

    initial_make_all(&mario,&luigi,&peach,ladders,&key,&trap,&life);
    import_all();

    int motion1[12] = {78,1,-30,760,    50,0,48,760,   20,-6,48,760};
    mario.draw_count = 50; // ensure that mario is drawn
    moving_sequence(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,motion1,12);

    clear_screen();
    menu_sequence();

    mario.draw_count = 50; // ensure that mario is drawn
    int motion2[4] = {13,-4,width,160};
    moving_sequence(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,motion2,4);
    peach.path_level = 6; // set position of peach

    while (1) {
        erase_peach(&peach); // erase previous draw
        erase_fireballs(fireballs,numFireballs);
        move_ladders(&peach,ladders); // move ladders
        draw_all_static(&mario,&luigi,&peach,ladders,&key,&trap,&life); // draw all constants

        if (key.exists == 1) { // if key already exists then move
            erase_key(&key);
            move_key(&key);
            draw_key(&key);
        }
        else if (key.intro_complete == 1) { // if key doesn't exist and introduction is complete
            if (key.caught == 0) { // if key hasn't been caught yet
                if (rand()%1000 == 0) {
                    new_key(&key);
                }
            }
        }

        if (life.exists == 0 && peach.num_lives < 3 && key.intro_complete == 1) { // if life doesn't exist and peach needs more
            if (rand()%500 == 0) {
                new_life(&peach,&life);
            }
        }

        if (numFireballs < 15 && key.intro_complete == 1) { // if can make more fireballs and introduction is complete
            if (rand()%100 == 0) {
                new_fireball(fireballs,numFireballs);
                numFireballs++;
            }
        }

        move_fireballs(fireballs,&peach,&numFireballs);

        if (gfx_event_waiting()) {
            userInput = gfx_wait();
            switch(userInput) {
                case 'w': // move upwards on ladder
                    move_peach(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,0,-1);
                break;
                case 's': // move downwards on ladder
                    move_peach(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,0,1);
                break;
                case 'a': // move left
                    peach.move_direction = -1;
                    move_peach(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,-1,0);
                break;
                case 'd': // move right
                    peach.move_direction = 1;
                    move_peach(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life,1,0);
                break;
                case 27:
                    return 0;
                    //intro_sequence();
                break;
                default:
                    peach.is_moving = 0;
                break;
            }
        }
        else {
            peach.is_moving = 0;
            draw_peach(&peach);
        }

        if (peach.is_jumping == 1) { // if peach is currently falling
            peach_jump(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life);
        }

        if (peach.is_falling == 1) { // if peach is currently falling
            if (peach_fall(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life) == 0) {
                return 0; // if dead and done playing
            }
        }

        if (trap.exists == 1) { // if trap exists
            move_trap(fireballs,numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life);
        }

        if(key.exists == 1 && (catch_key(&peach,&key)) == 1) { // if key exists and peach catches key
            erase_key(&key);
            key.exists = 0;
        }

        if (life.exists == 1 && (collect_life(&peach,&life)) == 1) { // if life exists and peach collects life
            erase_life(&life);
            life.exists = 0;
            peach.num_lives++;
            draw_lives(&peach);
        }

        gfx_flush();

        if (peach.num_lives < 1) { // if dead
            clear_screen();
            if (losing_sequence() == 32) { // if trying again
                reset_all(fireballs,&numFireballs,&mario,&luigi,&peach,ladders,&key,&trap,&life);
            }
            else { // if done playing
                return 0;
            }
        }

        if (difficulty >= 3) { // if hard difficulty level
            if (key.intro_complete == 1 && trap.exists == 0) { // if intro completed and trap doesn't exist
                if (rand()%100 == 0) {
                    new_trap(&trap);
                }
            }
        }

        if (peach.is_jumping == 0) {
            usleep(timing*10);
        }
    }
}

void import_all() {
    int i;
    char color;
    FILE *fp;

    fp = fopen("peach_static_right.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&static_peach_right[i].x,&static_peach_right[i].y,&static_peach_right[i].width,&static_peach_right[i].height,&color) != EOF) {
        set_peach_color(static_peach_right[i].color,color);
        i++;
    }

    fp = fopen("peach_moving_right.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&moving_peach_right[i].x,&moving_peach_right[i].y,&moving_peach_right[i].width,&moving_peach_right[i].height,&color) != EOF) {
        set_peach_color(moving_peach_right[i].color,color);
        i++;
    }

    fp = fopen("peach_static_left.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&static_peach_left[i].x,&static_peach_left[i].y,&static_peach_left[i].width,&static_peach_left[i].height,&color) != EOF) {
        set_peach_color(static_peach_left[i].color,color);
        i++;
    }

    fp = fopen("peach_moving_left.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&moving_peach_left[i].x,&moving_peach_left[i].y,&moving_peach_left[i].width,&moving_peach_left[i].height,&color) != EOF) {
        set_peach_color(moving_peach_left[i].color,color);
        i++;
    }

    fp = fopen("mario_static.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&static_mario[i].x,&static_mario[i].y,&static_mario[i].width,&static_mario[i].height,&color) != EOF) {
        set_mario_color(static_mario[i].color,color);
        i++;
    }

    fp = fopen("mario_talking.txt","r");
    i = 0;
    while (fscanf(fp,"%i %i %i %i %c",&talking_mario[i].x,&talking_mario[i].y,&talking_mario[i].width,&talking_mario[i].height,&color) != EOF) {
        set_mario_color(talking_mario[i].color,color);
        i++;
    }
}

void set_peach_color(int *color_array, char color) {
    switch(color) {
        case 'd': color_array[0] = 255; color_array[1] = 50; color_array[2] = 200; break;
        case 'l': color_array[0] = 255; color_array[1] = 115; color_array[2] = 180; break;
        case 'y': color_array[0] = 255; color_array[1] = 225; color_array[2] = 0; break;
        case 's': color_array[0] = 255; color_array[1] = 180; color_array[2] = 150; break;
        case 'b': color_array[0] = 0; color_array[1] = 0; color_array[2] = 255; break;
        case 'r': color_array[0] = 255; color_array[1] = 0; color_array[2] = 0; break;
        case 'w': color_array[0] = 255; color_array[1] = 255; color_array[2] = 255; break;
    }
}

void set_mario_color(int *color_array, char color) {
    switch(color) {
        case 'n': color_array[0] = 128; color_array[1] = 216; color_array[2] = 200; break;
        case 'o': color_array[0] = 64; color_array[1] = 128; color_array[2] = 152; break;
        case 'p': color_array[0] = 32; color_array[1] = 48; color_array[2] = 136; break;
        case 'q': color_array[0] = 136; color_array[1] = 88; color_array[2] = 24; break;
        case 'r': color_array[0] = 248; color_array[1] = 208; color_array[2] = 192; break;
        case 's': color_array[0] = 248; color_array[1] = 112; color_array[2] = 104; break;
        case 't': color_array[0] = 248; color_array[1] = 64; color_array[2] = 112; break;
        case 'u': color_array[0] = 248; color_array[1] = 216; color_array[2] = 112; break;
        case 'v': color_array[0] = 176; color_array[1] = 40; color_array[2] = 96; break;
        case 'w': color_array[0] = 80; color_array[1] = 0; color_array[2] = 0; break;
        case 'x': color_array[0] = 216; color_array[1] = 160; color_array[2] = 56; break;
        case 'y': color_array[0] = 0; color_array[1] = 0; color_array[2] = 0; break;
        case 'z': color_array[0] = 248; color_array[1] = 248; color_array[2] = 248; break;
    }
}

void initial_make_all(Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    make_mario(mario);
    make_luigi(luigi);
    make_peach(peach);
    make_ladders(ladders);
    make_key(key);
    make_trap(trap);
    make_life(life);
}

void draw_all_static(Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    draw_mario(mario,peach);
    draw_luigi(luigi);
    draw_platform();
    draw_paths();
    draw_trap(trap);
    draw_gate();
    draw_ladders(ladders);
    if (life->exists == 1) {
        draw_life(life);
    }
    if (key->exists == 1) {
        draw_key(key);
    }
    gfx_flush();
}

void draw_character(int x,int y,int width,int height,int color[]){
    gfx_color(color[0],color[1],color[2]);
    gfx_fill_rectangle(x,y,width,height);
}

void draw_lives(Peach *peach) {
    int i;
    for (i=0;i<3;i++) {
        if (i<peach->num_lives) {
            draw_static_peach(10+i*20,40,.25,1);
        }
        else {
            gfx_color(0,0,0);
            gfx_fill_rectangle(10+i*20,10,15,30);
        }
    }
}

void reset_all(Fireball *fireballs, int *numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    initial_make_all(mario,luigi,peach,ladders,key,trap,life);
    (*numFireballs) = 0;
    key->exists = 0;
    key->intro_complete = 1;
}

void new_fireball(Fireball *fireballs, int f) {
    fireballs[f].x_pos = 80;
    fireballs[f].y_pos = height-40-100*5-30;
    fireballs[f].angle = (rand()%1000) / 1000. * PI/2.;
    fireballs[f].radius = 25;
    fireballs[f].bounce_count = 0;
}

void draw_fireball(Fireball *fireballs, int f) {
    gfx_color(0,200,25);
    gfx_fill_circle(fireballs[f].x_pos,fireballs[f].y_pos,fireballs[f].radius);
}

void draw_fireballs(Fireball *fireballs, int numFireballs) {
    int i;
    for (i=0;i<numFireballs;i++) {
        draw_fireball(fireballs,i);
    }
}

void erase_fireballs(Fireball *fireballs, int numFireballs) {
    int i;
    for (i=0;i<numFireballs;i++) {
        gfx_color(0,0,0);
        gfx_fill_circle(fireballs[i].x_pos,fireballs[i].y_pos,fireballs[i].radius);
    }
}

void move_fireballs(Fireball *fireballs, Peach *peach, int *numFireballs) {
    int i;
    for (i=0;i<(*numFireballs);i++) {
        fireballs[i].x_pos += cos(fireballs[i].angle)*5;
        fireballs[i].y_pos += sin(fireballs[i].angle)*5;

        if (!(in_bounds(fireballs[i].x_pos,fireballs[i].y_pos))) {
            remove_fireball(fireballs,i,*numFireballs);
            (*numFireballs)--;
        }

        else if (collided(fireballs,peach,i)) {
            remove_fireball(fireballs,i,*numFireballs);
            (*numFireballs)--;
            peach->num_lives--;
            draw_lives(peach);
            gfx_flush();
        }

        draw_fireball(fireballs,i);
    }
}

void remove_fireball (Fireball *fireballs, int f, int numFireballs) {
    int i;
    for (i=f;i<numFireballs;i++) {
        fireballs[i].x_pos = fireballs[i+1].x_pos;
        fireballs[i].y_pos = fireballs[i+1].y_pos;
        fireballs[i].angle = fireballs[i+1].angle;
        fireballs[i].radius = fireballs[i+1].radius;
        fireballs[i].bounce_count = fireballs[i+1].bounce_count;
    }
}

int collided (Fireball *fireballs, Peach *peach, int f) {
    double change_x,change_y,distance,angle,peach_distance;
    change_x = fireballs[f].x_pos - (peach->x_pos+(35/2.));
    change_y = fireballs[f].y_pos - (peach->y_pos-peach->jump_height-peach->fall_height-(60/2.));

    distance = sqrt(pow(change_x,2)+pow(change_y,2));

    angle = atan(change_y/change_x);
    peach_distance = abs(30.*sin(angle));

    if (fireballs[f].radius + peach_distance >= distance) {
        return 1;
    }

    return 0;
}

void make_mario(Mario *mario) {
    mario->x_pos = 325;
    mario->y_pos = height-40-100*6;
    mario->draw_count = 50;
    mario->draw_position = 1;
}

void draw_mario(Mario *mario, Peach *peach) {
    if (mario->draw_position == 0) {
        gfx_color(0,0,0); // erase help text
        if ((peach->is_jumping == 0 && peach->is_moving == 0) || mario->draw_count == 50) {
            if (mario->draw_count < 50) {
                mario->draw_count++;
            } 
            else {
                erase_mario(mario);
                mario->draw_count = 0;
                mario->draw_position = 1;
                draw_talking_mario(mario->x_pos,mario->y_pos,.5);
                gfx_color(255,255,255);
                gfx_text(mario->x_pos,mario->y_pos-90,"HELP!!");
            }
        }
    }
    else if (mario->draw_position == 1) {
        if ((peach->is_jumping == 0 && peach->is_moving == 0) || mario->draw_count == 50) {
            if (mario->draw_count < 50) {
                mario->draw_count++;
            } 
            else {
                erase_mario(mario);
                mario->draw_count = 0;
                mario->draw_position = 0;
                draw_static_mario(mario->x_pos,mario->y_pos,.5);
                gfx_color(0,0,0);
                gfx_fill_rectangle(mario->x_pos-10,mario->y_pos-110,50,25);
            }
        }
    }
}

void draw_talking_mario(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<296;i++) {
        draw_character(xPosition+(talking_mario[i].x)*xRatio,yPosition-(talking_mario[i].y)*yRatio,(talking_mario[i].width)*xRatio,(talking_mario[i].height)*yRatio,talking_mario[i].color);
    }
}

void draw_static_mario(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<274;i++) {
        draw_character(xPosition+(static_mario[i].x)*xRatio,yPosition-(static_mario[i].y)*yRatio,(static_mario[i].width)*xRatio,(static_mario[i].height)*yRatio,static_mario[i].color);
    }
}

void erase_mario(Mario *mario) {
    gfx_color(0,0,0);
    gfx_fill_rectangle(mario->x_pos,mario->y_pos-60,35,60);
}

void make_luigi(Luigi *luigi) {
    luigi->x_pos = 50;
    luigi->y_pos = height-40-100*5;
    luigi->draw_count = 0;
    luigi->draw_position = 0;
}

void draw_luigi(Luigi *luigi) {
    gfx_color(0,180,0);
    gfx_fill_rectangle(luigi->x_pos,luigi->y_pos-50,30,50);
}

void draw_platform() {
    int y = height-40-100*5;
    int x = 300;
    
    gfx_color(200,200,200);

    gfx_fill_rectangle(x-34,0,2,y);
    gfx_fill_rectangle(x-2,0,2,y);

    double i;
    for (i=(1/20.);i<(19/20.);i+=(1/20.)) {
        gfx_fill_rectangle(x-32,y*i,30,2);
    }

    gfx_color(150,0,0);
    gfx_fill_rectangle(x,y-95,400,3);
    gfx_fill_rectangle(x,y-100,400,3);
}

void draw_gate() {
    int y = height-40-100*6;
    int x = 390;

    gfx_color(255,200,0);
    gfx_fill_rectangle(x,y-60,10,60);
}

void make_peach(Peach *peach) {
    peach->x_pos = 45; 
    peach->y_pos = height-40;
    peach->path_level = 0;
    peach->is_climbing = 0;
    peach->is_moving = 0;
    peach->move_direction = 0;
    peach->is_jumping = 0;
    peach->jump_height = 0;
    peach->jump_direction = 1;
    peach->jump_speed = 0;
    peach->is_falling = 0;
    peach->fall_height = 0;
    peach->fall_speed = 0;
    peach->speed = 10;
    peach->draw_count = 0;
    peach->draw_position = 0;
    peach->num_lives = 3;
}

void move_peach(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life, int ch_x, int ch_y) {
    double x,y;
    int l = peach->path_level;

    x = peach->x_pos + peach->speed * ch_x * (double)(difficulty)/2.;
    y = peach->y_pos + peach->speed * ch_y * (double)(difficulty)/2.;

    peach->is_moving = 1; // peach is moving
    
    if (!in_bounds(x,y)) { // if out of left boundary, correct position
        peach->x_pos = 0;
    }
    else if (!in_bounds(x+30,y)) { // if out of right boundary, correct position
        peach->x_pos = width-30;
    }
    else if (peach->is_falling == 1 && ch_y == 0) { // if falling, allow to move morizontally      
        peach->x_pos = x;
        peach->y_pos = y;
        draw_peach_motion(fireballs,numFireballs,mario,luigi,peach,ladders,key,trap,life);
        return;
    }
    else if ((l == 6 && x < 410) && key->caught == 0) { // restrict movement on fifth level if keys not collected
        peach->x_pos = 410;
        if (key->intro_complete == 0) { // if haven't completed intro and approaching mario
            draw_peach(peach);
            gfx_flush();
            usleep(pow(10,5.5));
            intro_sequence();
            trap->exists = 0;

            mario->draw_count = 50; // ensure that mario is drawn
            int motion[8] = {74,4,410,160, 20,4,-30,760};
            moving_sequence(fireballs,numFireballs,mario,luigi,peach,ladders,key,trap,life,motion,8);

            peach->path_level = 0;
            key->intro_complete = 1;

            draw_lives(peach);
            gfx_flush();

            // adjust speed of gameplay based on difficulty level
            if (difficulty == 1) { timing = pow(10,3.5); }
            else if (difficulty == 2) { timing = pow(10,3.3); }
            else if (difficulty == 3) { timing = pow(10,3); }
        }
        else if (key->intro_complete == 1) { //  if completed intro and approaching mario
            draw_peach(peach);
            gfx_color(255,255,255);
            gfx_text(400,15,"To talk to Mario, press space.");
            gfx_flush();
            usleep(pow(10,6));

            char c;
            if (gfx_event_waiting()) {
                c = gfx_wait();
                if (c == 32) {
                    play_sequence();
                    draw_lives(peach); // redraw lives left
                }
            }
            gfx_color(0,0,0);
            gfx_fill_rectangle(400,0,300,15); // erase text

            gfx_flush();
        }
    }
    else if ((l == 6 && x < 410) && key->caught == 1) { // if approaching mario and key has been caught
        peach->x_pos = 410;
        draw_peach(peach);
        gfx_flush();
        usleep(pow(10,6));
        ending_sequence();
    }
    else if (l==5 && x < 300) { // restrict movement on fourth level
        peach->x_pos = 300;
    }
    else { // any other floor
        if (peach->is_climbing==0) { // not on ladder
            if (ch_y == 0) { // moving horizontally
                if (peach->is_jumping == 0) { // if not jumping, move horizontally
                    peach->x_pos = x;
                    peach->y_pos = y;
                    draw_peach_motion(fireballs,numFireballs,mario,luigi,peach,ladders,key,trap,life);
                    return;
                }
            }
            else if (ch_y == -1) { // moving upwards
                if(((peach->x_pos+15) >= (ladders[l].x_pos-16)) && ((peach->x_pos+15) <= (ladders[l].x_pos+18))) { // if can move onto the ladder above
                    peach->x_pos = ladders[l].x_pos-14;
                    peach->y_pos = y;
                    peach->is_climbing = 1;
                    peach->draw_position = 2;
                }
                else { // not between a ladder
                    if (peach->jump_height == 0 && peach->is_falling == 0) { // if currently not jumping or falling
                        peach->is_jumping = 1;
                    }
                }
            }
            else if (ch_y == 1 && l != 0 && key->intro_complete == 1) { // moving downwards
                if(((peach->x_pos+15) >= (ladders[l-1].x_pos-16)) && ((peach->x_pos+15) <= (ladders[l-1].x_pos+18))) { // if can move onto the ladder below
                    peach->x_pos = ladders[l-1].x_pos-14;
                    peach->y_pos = y;
                    peach->is_climbing = 1;
                    peach->draw_position = 2;
                    (peach->path_level)--; // adjust to lower path
                }
            }
        }
        else if (peach->is_climbing==1) { // on ladder
            if (ch_x == 0) { // moving vertically
                peach->draw_position = 2;
                peach->x_pos = x;
                peach->y_pos = y;
                if (ch_y == -1 && y <= ladders[l].y_pos-100) { // top of ladder
                    peach->y_pos = ladders[l].y_pos-100;
                    peach->is_climbing = 0;
                    peach->draw_position = 0;
                    peach->draw_count = 0;
                    (peach->path_level)++; // adjust to higher path
                }
                else if (ch_y == 1 && y >= (ladders[l].y_pos)) { // bottom of ladder
                    peach->y_pos = ladders[l].y_pos;
                    peach->draw_position = 0;
                    peach->draw_count = 0;
                    peach->is_climbing = 0;
                    peach->is_moving = 0;
                }
            }
        }
        draw_peach(peach);
    }
}

void peach_jump(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    int i;
    for (i=0;i<10;i++) {
        erase_peach(peach);
        draw_all_static(mario,luigi,peach,ladders,key,trap,life);
        draw_fireballs(fireballs,numFireballs);
        if (peach->is_jumping == 1) {
            peach->jump_speed = abs(peach->jump_height-125)/100.; // slow at top and faster at bottom of jump
            peach->draw_position = 1;
            peach->jump_height += peach->jump_direction*peach->jump_speed * ((double)(difficulty)/2.);
            if (peach->jump_height >= 90) {
                peach->jump_direction = -1;
            }
            else if (peach->jump_height <= 0) {
                peach->jump_height = 0;
                peach->jump_direction = 1;
                peach->is_jumping = 0;
            }
        }
        draw_peach(peach);
        gfx_flush();
        usleep(timing);
    }
}

int peach_fall(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    int i;
    if (peach->fall_height < 100) {
        erase_peach(peach);
        draw_all_static(mario,luigi,peach,ladders,key,trap,life);
        draw_fireballs(fireballs,numFireballs);
        peach->fall_speed = abs(peach->fall_height-125)/125.; // slow at top and faster at bottom of jump

        peach->fall_height+=peach->fall_speed*5;

        draw_peach(peach);
        gfx_flush();
    }
    else {
        peach->y_pos += peach->fall_height;
        peach->fall_height = 0;
        peach->is_falling = 0;
        peach->path_level--; // decrease path level
        if (peach->path_level < 0) { // if fall off screen then lose
            clear_screen();
            mario->draw_count = 50; // ensure that mario is drawn
            if (losing_sequence() == 32) { // if trying again
                reset_all(fireballs,&numFireballs,mario,luigi,peach,ladders,key,trap,life);
            }
            else { // if done playing, return a 0
                return 0;
            }   
        }
    }
    return 1; // return 1 to continue play
}

void draw_peach(Peach *peach) {
    if (peach->is_jumping == 1) { // jumping
        draw_moving_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
    }
    else if (peach->is_falling == 1) {
        draw_moving_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
    }
    else if (peach->draw_position == 2) { // climbing ladder
        draw_static_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
    }
    else if (peach->draw_position == 0) { // static motion
        draw_static_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
    }
    else if (peach->draw_position == 1) { // moving
        draw_moving_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
    }
}

void draw_static_peach(int xPosition, int yPosition, double ratio, int direction) {
    if (direction < 0) {
        draw_static_peach_left(xPosition,yPosition,ratio);
    }
    else {
        draw_static_peach_right(xPosition,yPosition,ratio);
    }
}

void draw_moving_peach(int xPosition, int yPosition, double ratio, int direction) {
    if (direction < 0) {
        draw_moving_peach_left(xPosition,yPosition,ratio);
    }
    else {
        draw_moving_peach_right(xPosition,yPosition,ratio);
    }
}

void draw_static_peach_right(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<49;i++) {
        draw_character(xPosition+(static_peach_right[i].x)*xRatio,yPosition-(static_peach_right[i].y)*yRatio,(static_peach_right[i].width)*xRatio,(static_peach_right[i].height)*yRatio,static_peach_right[i].color);
    }
}

void draw_moving_peach_right(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<50;i++) {
        draw_character(xPosition+(moving_peach_right[i].x)*xRatio,yPosition-(moving_peach_right[i].y)*yRatio,(moving_peach_right[i].width)*xRatio,(moving_peach_right[i].height)*yRatio,moving_peach_right[i].color);
    }
}

void draw_static_peach_left(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<49;i++) {
        draw_character(xPosition+(static_peach_left[i].x)*xRatio,yPosition-(static_peach_left[i].y)*yRatio,(static_peach_left[i].width)*xRatio,(static_peach_left[i].height)*yRatio,static_peach_left[i].color);
    }
}

void draw_moving_peach_left(int xPosition, int yPosition, double ratio) {
    double xRatio=(140/30)*ratio;
    double yRatio=(60/15)*ratio;

    int i;
    for (i=0;i<49;i++) {
        draw_character(xPosition+(moving_peach_left[i].x)*xRatio,yPosition-(moving_peach_left[i].y)*yRatio,(moving_peach_left[i].width)*xRatio,(moving_peach_left[i].height)*yRatio,moving_peach_left[i].color);
    }
}

void erase_peach(Peach *peach) {
    gfx_color(0,0,0);
    gfx_fill_rectangle(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height-60,35,60);
}

void draw_peach_motion(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    double x_pos = peach->x_pos;
    int i;
    if (peach->is_moving == 1) {
        for (i=peach->speed;i>=0;i--) {
            erase_peach(peach);
            draw_all_static(mario,luigi,peach,ladders,key,trap,life);
            draw_fireballs(fireballs,numFireballs);
            peach->x_pos = x_pos+i*(-1)*peach->move_direction * (double)(difficulty)/2.;
            if (peach->draw_position == 0) { // static draw
                draw_static_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
            }
            else {
                draw_moving_peach(peach->x_pos,peach->y_pos-peach->jump_height+peach->fall_height,0.5,peach->move_direction);
            }
            gfx_flush();
            usleep(timing);
        }

        if (peach->draw_count < 3) {
            peach->draw_count+=2;
        } 
        else {
            if (peach->draw_position == 0) {
                peach->draw_position = 1;
            }
            else if (peach->draw_position == 1) {
                peach->draw_position = 0;
            }
            peach->draw_count = 0;
        }

        peach->x_pos = x_pos;
        draw_peach(peach);
    }
    else {
        draw_peach(peach);
        gfx_flush();
        usleep(timing*10);
    }
}

int catch_key(Peach *peach, Key *key) {
    double distance_x,distance_y,distance;
    double angle;

    distance_x = (key->x_pos+12)-(peach->x_pos+17);
    distance_y = (peach->y_pos-30-peach->jump_height)-(key->y_pos-2);

    angle = atan2(distance_y,distance_x);

    distance = sqrt(pow(distance_x,2) + pow(distance_y,2)); // find distance between centers

    if (distance < 45) { // caught key
        erase_key(key);
        key->caught = 1;
        key->x_pos = 100;
        key->y_pos = 40;
        draw_key(key);
        return 1;
    }
    else {
        return 0;
    }
}

int collect_life(Peach *peach, Life *life) {
    double change_x,change_y,distance,angle,peach_distance;
    change_x = life->x_pos - (peach->x_pos+(35/2.));
    change_y = life->y_pos - (peach->y_pos-peach->jump_height-peach->fall_height-(60/2.));

    distance = sqrt(pow(change_x,2)+pow(change_y,2));

    angle = atan(change_y/change_x);
    peach_distance = abs(30.*sin(angle));

    if (life->radius + peach_distance >= distance) {
        return 1;
    }

    return 0;
}

void make_ladders(Ladder *ladders) {
    int i;
    for (i=0;i<6;i++) {
        ladders[i].x_pos = rand()%(width-34)+16;
        ladders[i].y_pos = height-40-100*i;
        if (rand()%2 == 0) {
            ladders[i].ch_x = -1;
        }
        else {
            ladders[i].ch_x = 1;
        }
        ladders[i].speed = (rand()%4+1) * .5;
    }

    ladders[4].x_pos = width-34-200;

    ladders[5].x_pos = width-34;
    ladders[5].ch_x = 0;
}

void move_ladders(Peach *peach, Ladder *ladders) {
    int i;
    for (i=0;i<6;i++) {
        erase_ladder(&ladders[i]);
        move_ladder(peach,&ladders[i],i);
        draw_ladder(ladders);
    }
}

void move_ladder(Peach *peach, Ladder *ladder, int l) {
    double x;
    x = ladder->x_pos + (double)ladder->ch_x * ladder->speed;

    if (l==4 && ladder->x_pos < 316) {
        ladder->x_pos = 316;
        ladder->ch_x *= -1;
        ladder->speed = (rand()%4+1) * .5;
    }
    else if (!(in_bounds(x-16,ladder->y_pos))) {
        ladder->x_pos = 16;
        ladder->ch_x *= -1;
        ladder->speed = (rand()%4+1) * .5;
    }
    else if (!(in_bounds(x+18,ladder->y_pos))) {
        ladder->x_pos = width-18;
        ladder->ch_x *= -1;
        ladder->speed = (rand()%4+1) * .5;
    }
    else {
        ladder->x_pos = x;
        if (peach->is_climbing == 1 && peach->path_level == l) {
            erase_peach(peach);
            peach->x_pos += ladder->ch_x * ladder->speed;
        }
    }
}

void draw_ladders(Ladder *ladders) {
    int i;
    for (i=0;i<6;i++) {
        draw_ladder(&ladders[i]);
    }
}

void draw_ladder(Ladder *ladder) {
    gfx_color(200,200,200);
    gfx_fill_rectangle(ladder->x_pos-16,ladder->y_pos-92,2,92);
    gfx_fill_rectangle(ladder->x_pos+16,ladder->y_pos-92,2,92);
    double i;
    for (i=(1/8.);i<1;i+=(1/8.)) {
        gfx_fill_rectangle(ladder->x_pos-14,ladder->y_pos-92*i,30,2);
    }
}

void erase_ladder(Ladder *ladder) {
    gfx_color(0,0,0);
    gfx_fill_rectangle(ladder->x_pos-16,ladder->y_pos-92,2,92);
    gfx_fill_rectangle(ladder->x_pos+16,ladder->y_pos-92,2,92);
    double i;
    for (i=(1/8.);i<1;i+=(1/8.)) {
        gfx_fill_rectangle(ladder->x_pos-14,ladder->y_pos-92*i,30,2);
    }
}

void draw_paths() {
    gfx_color(150,0,0);
    int i;
    for (i=0;i<6;i++) {
        gfx_fill_rectangle(0,height-40-100*i,width,3);
        gfx_fill_rectangle(0,height-40-100*i+5,width,3);
    }
}

void make_trap(Trap *trap) {
    trap->exists = 0;
    trap->length = 100;
}

void new_trap(Trap *trap) {
    trap->x_pos = -1*trap->length;
    trap->path_level = rand()%4;
    trap->y_pos = height-40-100*trap->path_level;
    trap->state = 0;
    trap->exists = 1;
}

void move_trap(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life) {
    if (trap->state == 0) { // warning
        if (trap->x_pos < width) { // trap door in bounds
            trap->x_pos+=5;
            draw_all_static(mario,luigi,peach,ladders,key,trap,life);
            draw_fireballs(fireballs,numFireballs);
            draw_peach(peach);
        }
        else {
            trap->x_pos = -1*trap->length;
            trap->state = 1;
        }

    }
    else if (trap->state == 1) { // drop
        if (trap->x_pos < width) { // trap door
            trap->x_pos+=5;
            draw_all_static(mario,luigi,peach,ladders,key,trap,life);
            draw_fireballs(fireballs,numFireballs);
            draw_peach(peach);
        }
        else {
            trap->exists = 0;
        }

        if (peach->is_falling == 0 && check_trap(peach,trap) == 1) { // if peach isn't currently falling
            peach->is_falling = 1;
        }
    }
}

void draw_trap(Trap *trap) {
    if (trap->exists == 1) { // draw only if trap exists
        if (trap->state == 0) {
            gfx_color(255,0,0); // bright red
        }
        else if (trap->state == 1) {
            gfx_color(0,0,0); // black
        }
        gfx_fill_rectangle(trap->x_pos,height-40-100*trap->path_level,trap->length,3);
        gfx_fill_rectangle(trap->x_pos,height-40-100*trap->path_level+5,trap->length,3);
    }
}

int check_trap(Peach *peach,Trap *trap) {
    if (peach->is_climbing == 0 && peach->is_jumping == 0) { // if peach is not jumping or climbing
        if (peach->path_level == trap->path_level) { // if peach is on the same level as the trap
            if ((peach->x_pos+18) > trap->x_pos && (peach->x_pos+18) < (trap->x_pos+trap->length)) {
                return 1;
            }
        }
    }
    return 0; // don't fall
}

void make_key(Key *key) {
    key->intro_complete = 0;
    key->exists = 0;
    key->caught = 0;
}

void new_key(Key *key) {
    key->x_pos = 80;
    key->y_pos = height-40-100*5-30;
    key->angle = (rand()%1000) / 1000. * PI/2.;
    key->exists = 1;
}

void move_key(Key *key) {
    double x,y;
    x = key->x_pos + cos(key->angle)*2;
    y = key->y_pos + sin(key->angle)*2;
    if (key->exists == 1) {
        if (in_bounds(x,y)) {
            key->x_pos = x;
            key->y_pos = y;
        }
        else { // out of bounds
            key->exists = 0;
        }
    }
}

void draw_key(Key *key) {
    if (key->exists == 1) {
        gfx_color(255,200,0);
        gfx_fill_circle(key->x_pos+5,key->y_pos-4,5);
        gfx_fill_rectangle(key->x_pos+9,key->y_pos-4,15,3);
    }
}

void erase_key(Key *key) {
    if (key->exists == 1) {
        gfx_color(0,0,0);
        gfx_fill_circle(key->x_pos+5,key->y_pos-4,5);
        gfx_fill_rectangle(key->x_pos+9,key->y_pos-4,15,3);
    }
}

void make_life(Life *life) {
    life->exists = 0;
    life->radius = 15;
    life->length = 10;
}

void new_life(Peach *peach, Life *life) {
    if (difficulty == 1) { life->path_level = peach->path_level; }
    else { life->path_level = rand()%4; }
    life->x_pos = rand()%(width-2*life->radius) + life->radius;
    life->y_pos = height - 40 - 100*life->path_level - life->radius/2 - life->length;
    life->exists = 1;
    life->count = 0;
}

void draw_life(Life *life) {
    gfx_color(180,90,255);
    gfx_fill_rectangle(life->x_pos-(life->radius/4),life->y_pos,life->radius/2,life->length+life->radius/2);
    gfx_fill_arc(life->x_pos-life->radius,life->y_pos-life->radius/2,life->radius*2,life->radius,0,180);
    if (life->count > 1000) {
        erase_life(life);
        life->exists = 0;
    }
    else {
        life->count++;
    }
}

void erase_life(Life *life) {
    gfx_color(0,0,0);
    gfx_fill_rectangle(life->x_pos-(life->radius/4),life->y_pos,life->radius/2,life->length+life->radius/2);
    gfx_fill_arc(life->x_pos-life->radius,life->y_pos-life->radius/2,life->radius*2,life->radius,0,180);
}

int in_bounds(int x, int y) {
    return (x>=0 && x<width && y>=0 && y<=height);
}

void menu_sequence() {
    int i;
    int state = 0;

    gfx_color(150,0,0); // draw path
    gfx_fill_rectangle(0,615,width,9);
    gfx_fill_rectangle(0,600,width,9);

    for (i=-105;i<width+150;i++) {
        gfx_color(0,0,0); // clear screen as peach moves
        gfx_fill_rectangle(i-150,0,2,height);

        gfx_color(255,255,255); // title
        gfx_text(305,100,"Luigi's Revenge");

        if (state == 0) {
            draw_static_peach(i,600,1.5,1);
            if (i%75 == 0) {
                state = 1;
            }
        }
        else if (state == 1) {
            draw_moving_peach(i,600,1.5,1);
            if (i%75 == 0) {
                state = 0;
            }
        }
        gfx_flush();
        usleep(timing);
        gfx_color(0,0,0);
        gfx_fill_rectangle(i,600-180,105,180);
    }
    gfx_color(255,255,255);
    gfx_text(275,650,"Select a difficulty level...");
    gfx_text(115,525,"(1) Easy");
    gfx_text(310,525,"(2) Medium");
    gfx_text(515,525,"(3) Hard");
    draw_static_peach(100,500,1.5,1);
    draw_static_peach(300,500,1.5,1);
    draw_static_peach(500,500,1.5,1);
    char c;
    do {
        c = gfx_wait();
        if (c == '1') { difficulty = 1; }
        else if (c == '2') { difficulty = 2; }
        else if (c == '3') { difficulty = 3; }
    } while (c != '1' && c != '2' && c != '3');
    clear_screen();
/*
    i = 0;
    while (i <= height) {
        print_instructions();

        gfx_color(0,0,0);
        gfx_fill_rectangle(0,i,width,height-i);

        gfx_flush();
        usleep(pow(10,3.5));
        i+=2;
    }
    usleep(pow(10,6)*3);
    clear_screen();
*/
}

void print_instructions() {
    gfx_color(255,255,255);
    gfx_text(200,100,"Instructions");
    gfx_text(200,125,"a,w,s,d");
    gfx_text(200,150,"Etc");
}

void moving_sequence(Fireball *fireballs, int numFireballs, Mario *mario, Luigi *luigi, Peach *peach, Ladder *ladders, Key *key, Trap *trap, Life *life, int *motion, int length) {
    int i = 0;
    int count = 0;

    // motion array stores: 0 - places moved, 1 - direction moved, 2 - x initial position, 3 - y initial position
    peach->is_moving = 0;

    while (1) {
        peach->move_direction = motion[i+1];
        move_ladders(peach,ladders);
        erase_peach(peach);
        draw_all_static(mario,luigi,peach,ladders,key,trap,life);

        if (motion[i+1] == 0) {
            if (count > 25) {
                gfx_color(255,255,255);
                gfx_text(100,700,"Mario?!!");
            }
        }
        else if (motion[i+1] == -4 && length == 12) {
            gfx_color(255,255,255);
            gfx_text(100,700,"Mario?!!");
        }
        else {
            if (peach->draw_count < 25) {
                peach->draw_count+=2;
            } 
            else {
                if (peach->draw_position == 0) {
                    peach->draw_position = 1;
                }
                else if (peach->draw_position == 1) {
                    peach->draw_position = 0;
                }
                peach->draw_count = 0;
            }
        }

        peach->x_pos = motion[i+2] + motion[i+1]*count;
        peach->y_pos = motion[i+3];
        count++;

        if (count >= motion[i]) {
            count = 0;
            i+=4;
        }

        draw_peach_motion(fireballs,numFireballs,mario,luigi,peach,ladders,key,trap,life);
        gfx_flush();

        if (i>=length) {
            return;
        }

    }
}

void intro_sequence() {
    char c;
    clear_screen();
    gfx_color(150,0,0);
    gfx_fill_rectangle(0,height-100,width,9);
    gfx_fill_rectangle(0,height-115,width,9);

    draw_static_mario(155,height-115,1);

    draw_static_peach(455,height-115,1,-1);

    gfx_color(255,200,0);
    gfx_fill_rectangle(330,height-115-180,20,180);

    gfx_flush();

    c = print_text(1,100," Princess! - - Is it really you?!");

    if (c == 32) {
        gfx_color(0,0,0);
        gfx_fill_rectangle(width-300,height-25,300,25);
        print_text(0,410," Mario! - - What happened?!");
        print_text(0,100," My brother's gone mad! - - He confronted me about seeing us - together and the next thing I know... - - I'm behind this gate!");
        print_text(0,100," He's been taunting anyone nearby by - throwing them a key to the gate! - - If you grab one, - you can let me out!");
        print_text(0,410," That doesn't sound too difficult... - - Is there some kind of catch?");
        if (difficulty == 1) {
            print_text(0,100," He's just standing there - cackling at my misery, really.");
            print_text(0,410," That's it? - - No fireballs? - - No falling floors? - - No anything?");
            print_text(0,100," Well if you wanted something harder - you should have chosen it! - - Don't go shooting the messenger!");
        }
        else if (difficulty == 2) {
            print_text(0,100," He's been launching fireballs at any - potential rescuers to scare them off! - - Please help me! - I don't know what I'll do if I - stay another minute in here...");
            print_text(0,410," Of course I'll save you, Mario! - - What kind of girlfriend would I be - if I left you here...");
            print_text(0,100," Peach...");
            print_text(0,410," Don't look so starstruck! - - So... -- are these fireballs dangerous?");
            print_text(0,100," Be very careful! - - You only have three chances to be hit - by a fireball before you'll be drained - of all your energy! - - ...And possibly die... - - I don't really know...");  
        }
        else if (difficulty == 3) {
            print_text(0,100," He's been launching fireballs at any - potential rescuers to scare them off! - - Three hits and it's lights out!");
            print_text(0,100," The floor is also very unstable!! - - Every so often you might find yourself - falling through them...");
            print_text(0,410," So do I get any warning if I'm suddenly - about to drop through a floor?");
            print_text(0,100," The floor will turn red before it - disappears! - - Make sure you're not standing on it - when it does or you'll fall!");
        }
        print_text(0,410," How delightful...");
        gfx_color(0,0,0);
        gfx_fill_rectangle(0,0,width,500);
        gfx_color(255,255,255);
        gfx_text(5,height-15,"Press space to return to the game...");
        gfx_flush();
        while (gfx_wait() != 32);
    }
    
    clear_screen();
}

void play_sequence() {
    char c;
    clear_screen();
    gfx_color(150,0,0);
    gfx_fill_rectangle(0,height-100,width,9);
    gfx_fill_rectangle(0,height-115,width,9);

    draw_static_mario(155,height-115,1);

    draw_static_peach(455,height-115,1,-1);

    gfx_color(255,200,0);
    gfx_fill_rectangle(330,height-115-180,20,180);

    gfx_flush();
    if (difficulty == 1) {
        c = print_text(1,100," Princess! - - Do you have the key?");
    }
    else if (difficulty == 2) {
        c = print_text(1,100," Princess! - - Am I glad to see you!");
    }
    else if (difficulty == 3) {
        c = print_text(1,100," Princess! - - You're not dead!");
    }

    if (c == 32) {
        gfx_color(0,0,0);
        gfx_fill_rectangle(width-300,height-25,300,25);
        if (difficulty == 2) {
            print_text(0,410," And I you! - - How are you feeling?");
            print_text(0,100," Like my brother tossed me in a cage. - - Please say you have the key?");
        }
        else if (difficulty == 3) {
            print_text(0,410," Surprised? - - Me too...");
            print_text(0,100," Did you, by any miracle, manage - to catch a key yet?");
        }
        print_text(0,410," Not yet...");
        print_text(0,100," Please hurry! - - I don't know how much longer - I can stay in here before I - go crazy!");
        print_text(0,410," Assuming that you weren't already... - - But alright, Mario. - - I'll keep trying...");
        gfx_color(0,0,0);
        gfx_fill_rectangle(0,0,width,500);
        gfx_color(255,255,255);
        gfx_text(5,height-15,"Press space to return to the game...");
        gfx_flush();
        while (gfx_wait() != 32);
    }

    clear_screen();
}

int losing_sequence() {
    char c;
    clear_screen();
    gfx_color(150,0,0);
    gfx_fill_rectangle(0,height-100,width,9);
    gfx_fill_rectangle(0,height-115,width,9);

    draw_talking_mario(155,height-115,1);

    gfx_color(255,200,0);
    gfx_fill_rectangle(330,height-115-180,20,180);

    print_text(0,410," PEACH. - - I SAVE YOU SO MANY TIMES. - - AND YOU JUST LET ME DOWN - LIKE THIS. - - WOW.");
    print_text(0,410," ARE YOU GOING TO TRY AGAIN? - - OR ARE YOU A LITTLE BITCH?");
    gfx_color(0,0,0);
    gfx_fill_rectangle(0,0,width,500);
    gfx_color(255,255,255);
    gfx_text(5,height-15,"Press space to try again or 'esc' to quit...");
    gfx_flush();
    while ((c = gfx_wait()) != 32 && c != 27);

    clear_screen();

    return c;
}

void ending_sequence() {
    char c;
    clear_screen();
    gfx_color(150,0,0);
    gfx_fill_rectangle(0,height-100,width,9);
    gfx_fill_rectangle(0,height-115,width,9);

    draw_static_mario(155,height-114,1);

    draw_static_peach(455,height-115,1,-1);

    gfx_color(255,200,0);
    gfx_fill_rectangle(330,height-115-180,20,180);

    gfx_flush();

    c = print_text(1,100," Princess! - - Did you catch the key?");

    if (c == 32) {
        gfx_color(0,0,0);
        gfx_fill_rectangle(width-300,height-25,300,25);
        print_text(0,410," Of course I did! - - Don't tell me that you doubted - my abilities?");
        print_text(0,100," I was just worried about you! - - I don't know what I'd do - if you got hurt...");
        print_text(0,410," Mario...!");
        print_text(0,100," You said you had the key?");
        print_text(0,410," Oh. - - Yes. - - I'll unlock the gate now...");
        gfx_color(0,0,0);
        gfx_fill_rectangle(0,0,width,500);
        gfx_color(255,255,255);
        gfx_text(5,height-15,"Press space to return to the game...");
        gfx_flush();
        while (gfx_wait() != 32);
    }
    clear_screen();
}

int print_text(int allowEsc, int xPos, char text[1000]) {
    char str[1000];
    strcpy(str,text);

    int i = 0;
    const char s[2] = "-";
    char *token;

    token = strtok(str,s);

    gfx_color(0,0,0);
    gfx_fill_rectangle(0,0,width,500);

    if (xPos < 300) { // if mario is speaking
        gfx_color(0,0,0);
        gfx_fill_rectangle(155,height-115-120,75,120);
        draw_talking_mario(155,height-115,1);
    }
    else { // if peach is speaking
        gfx_color(0,0,0);
        gfx_fill_rectangle(455,height-115-120,75,120);
        draw_moving_peach(455,height-115,1,-1);
    }

    while(token != NULL) {
        gfx_color(255,255,255);
        gfx_text(xPos,height-500+(i*15),token);
        gfx_flush();
        usleep(pow(10,6)/2);

        token = strtok(NULL,s);
        i++;
    }
    return wait_input(allowEsc,xPos);
}

int wait_input(int allowEsc, int xPos) {
    char c;
    gfx_color(255,255,255);
    gfx_text(5,height-15,"Press space to proceed...");
    if (allowEsc == 1) {
        gfx_text(5,15,"Press 'esc' to skip the dialogue...");
    }
    gfx_flush();
    while ((c = gfx_wait())!=32 && !(allowEsc == 1 && c == 27));
    gfx_color(0,0,0);
    gfx_fill_rectangle(0,height-90,width,90);
    if (allowEsc == 1) {
        gfx_fill_rectangle(0,0,width,20);
    }

    if (xPos < 300) { // if mario was speaking
        gfx_color(0,0,0);
        gfx_fill_rectangle(155,height-115-120,75,120);
        draw_static_mario(155,height-115,1);
    }
    else { // if peach was speaking
        gfx_color(0,0,0);
        gfx_fill_rectangle(455,height-115-120,75,120);
        draw_static_peach(455,height-115,1,-1);
    }

    return c;
}

void clear_screen() {
    int i;
    for (i=0;i<width;i+=2) {
        gfx_color(0,0,0);
        gfx_fill_rectangle(i,0,2,height);

        gfx_flush();
        usleep(pow(10,3.5));
    }
    usleep(pow(10,5.5));
}