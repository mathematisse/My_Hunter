/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** Header for my_hunter
*/

#ifndef HUNTER
    #define HUNTER
    #include <SFML/System/Export.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
enum duck_state {
    Unused,
    Dead,
    Waiting,
    Starting,
    Flying,
    Taking_Off,
    Restarting
};
enum hunter_state {
    Menu,
    Playing,
    Paused,
    End,
    Quit
};
typedef struct Duck {
    sfTransform transform;
    enum duck_state dstate;
    int state;
    float timer;
    float ptimer;
    float sectostart;
    float sectopoop;
    sfTransform poosition;
    int colorchg;
    float speed;
    float crusey;
} duck_t;
typedef struct Master_Duck {
    sfSprite *sprites[24];
    sfSprite *shit;
    sfRenderStates renderer;
    duck_t *duck;
    int dcount;
    float timer;
    sfSoundBuffer *sbuf;
    sfSound *sound;
    sfSoundBuffer *qsbuf;
    sfSound *qsound;
    float secfornew;
    int donew;
} master_duck_t;
typedef struct Cursor {
    sfSoundBuffer *sbuf;
    sfSound *sound;
    sfSprite *crosshair;
    sfSprite *cannon;
    sfSprite *base;
    sfSprite *beam;
    sfSprite *pixel;
    sfTransform beamt;
    int beam_active;
    float timer;
    sfTransform cannont;
    sfRenderStates renderer;
    int x, y;
    float range;
    float secfor_reload;
} cursor_t;
typedef struct Props {
    sfSprite *tree;
    sfSprite *panel;
    sfSprite *grass;
    int tcount, pcount;
    sfRenderStates renderer;
} props_t;
typedef struct Hunter {
    sfRenderWindow* window;
    sfEvent event;
    sfClock *clock;
    float elapsed_time;
    master_duck_t master_d;
    cursor_t cursor;
    props_t props;
    int is_shooting;
    int killed, spent;
    float nrj, dmg;
    sfMusic *music;
    sfFont* font;
    sfText* text;
    enum hunter_state hstate;
    sfRenderStates brenderer;
    sfRenderStates trenderer;
    sfSprite *bsprite;
    sfSprite *rpixel;
    sfSprite *gpixel;
    sfSprite *opixel;
    sfText *itext;
    sfText *stext;
    sfText *mtext;
    sfRenderStates istates;
    float dt;
    int highest;
    char *maxpath;
} hunter_t;
void save_score(hunter_t *);
void copyhstr(char **, char *);
void handle_click(hunter_t *, sfMouseButtonEvent);
int shoot(hunter_t *, int, int);
void draw_loop(hunter_t *);
void handle_barmove(hunter_t *, int, int);
int get_barbutindex(int, int);
void set_infotext(hunter_t *, char *, int, int);
int get_tcost(int);
int get_pcost(int);
int get_rcost(float);
int get_acost(float);
int get_menubut(int, int);
void handle_menuclick(hunter_t *, int, int);
void changestr(char *, int);
void init_music(sfMusic **, char *, float);
void init_text(sfFont *, char *, sfText **, int);
float get_canangle(int, int);
void init_renderer(sfRenderStates *);
int load_texture(char *, sfTexture **, sfIntRect *);
void make_sprite(sfSprite **, sfTexture *);
void make_sprite_path(sfSprite **, char *);
int init_master_duck(master_duck_t *);
int loop_master_duck(sfRenderWindow *, master_duck_t *, float);
void terminate_master_duck(master_duck_t *);
int init_cursor(cursor_t *);
int make_beam(cursor_t *, int, int);
void loop_cursor(sfRenderWindow *, cursor_t *, float);
void terminate_cursor(cursor_t *);
int init_props(props_t *);
void draw_back_props(sfRenderWindow *, props_t *);
void draw_front_props(sfRenderWindow *, props_t *);
void terminate_props(props_t *);
int init_hunt(hunter_t *);
int launch_hunt(hunter_t *);
void loop_hunt(hunter_t *);
int terminate_hunt(hunter_t *);
void restart_duck(duck_t *, unsigned);
void spawn_duck(duck_t *, unsigned);
int duck_is_out(sfTransform *);
void dead_duck(duck_t *, float);
void fly_duck(duck_t *, float);
void taking_off_duck(duck_t *, float);
void loop_menu(hunter_t *);
void wait_duck(duck_t *);
#endif
