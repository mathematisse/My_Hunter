/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** Handlers for props struct
*/

#include "hunter.h"

int init_props(props_t *p)
{
    p->tcount = 0;
    p->pcount = 0;
    make_sprite_path(&(p->tree), "ressources/tree.png");
    make_sprite_path(&(p->panel), "ressources/panel.png");
    make_sprite_path(&(p->grass), "ressources/grass.png");
    init_renderer(&(p->renderer));
    return EXIT_SUCCESS;
}

void draw_back_props(sfRenderWindow *w, props_t *p)
{
    sfTransform *t = &(p->renderer.transform);

    (*t).matrix[0] = 2;
    (*t).matrix[4] = 2;
    (*t).matrix[5] = 700;
    for (int i = 0; i < p->tcount; i++) {
        (*t).matrix[2] = 30 + (80 * i);
        sfRenderWindow_drawSprite(w, p->tree, &(p->renderer));
    }
}

void draw_front_props(sfRenderWindow *w, props_t *p)
{
    sfTransform *t = &(p->renderer.transform);

    (*t).matrix[5] = 900;
    (*t).matrix[2] = 0;
    (*t).matrix[0] = 2;
    (*t).matrix[4] = 2;
    sfRenderWindow_drawSprite(w, p->grass, &(p->renderer));
    (*t).matrix[2] = 512 * 2;
    sfRenderWindow_drawSprite(w, p->grass, &(p->renderer));
    (*t) = sfTransform_Identity;
    (*t).matrix[5] = 920;
    for (int i = 0; i < p->pcount; i++) {
        (*t).matrix[2] = 30 + (100 * i);
        sfRenderWindow_drawSprite(w, p->panel, &(p->renderer));
    }
}

void terminate_props(props_t *p)
{
    sfSprite_destroy(p->tree);
    sfSprite_destroy(p->panel);
}
