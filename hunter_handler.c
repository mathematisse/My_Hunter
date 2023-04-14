/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** Handling funcs for hunter struct
*/

#include "hunter.h"
#include <stdio.h>

void init_hunter_vars(hunter_t *h)
{
    h->highest = 0;
    h->dt = 0;
    h->hstate = Menu;
    h->nrj = 10;
    h->brenderer.transform.matrix[2] = 0;
    h->brenderer.transform.matrix[5] = 1010;
    h->trenderer.transform.matrix[2] = 1500;
    h->trenderer.transform.matrix[5] = 1010;
    h->dmg = 0;
    h->killed = 0;
    h->spent = 0;
    h->elapsed_time = 0;
    h->is_shooting = sfFalse;
}

void init_hunter_objs(hunter_t *h)
{
    h->maxpath = malloc(sizeof(char) * 20);
    h->font = sfFont_createFromFile("ressources/comicate.ttf");
    init_renderer(&(h->istates));
    init_text(h->font, "Score Text", &(h->stext), 50);
    init_text(h->font, "Info Text", &(h->itext), 40);
    init_text(
        h->font,
        "MY HUNTER\n\n\nEasy\n\n\n\nMedium\n\n\n\nHard\n\n\n\nQuit",
        &(h->mtext),
        50);
    init_text(h->font, "My Hunter", &(h->text), 40);
    make_sprite_path(&(h->rpixel), "ressources/rpixel.png");
    make_sprite_path(&(h->gpixel), "ressources/gpixel.png");
    make_sprite_path(&(h->opixel), "ressources/opixel.png");
    make_sprite_path(&(h->bsprite), "ressources/bottombar.png");
    init_renderer(&(h->brenderer));
    init_renderer(&(h->trenderer));
    init_music(&(h->music), "ressources/flufaduck.ogg", 30);
}

int init_hunt(hunter_t *h)
{
    init_hunter_objs(h);
    init_hunter_vars(h);
    if (init_cursor(&(h->cursor)) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (init_master_duck(&(h->master_d)) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (init_props(&(h->props)) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int launch_hunt(hunter_t *h)
{
    sfVideoMode mode = {1920, 1080, 32};

    h->clock = sfClock_create();
    h->window =
        sfRenderWindow_create(
            mode,
            "My Duck Hunt",
            sfClose | sfTitlebar,
            NULL);
    if (!(h->window))
        return EXIT_FAILURE;
    sfRenderWindow_setFramerateLimit(h->window, 60);
    sfRenderWindow_setMouseCursorVisible(h->window, 0);
    sfRenderWindow_setKeyRepeatEnabled(h->window, sfTrue);
    sfMusic_play(h->music);
    return EXIT_SUCCESS;
}

int terminate_hunt(hunter_t *h)
{
    if (h->elapsed_time > h->highest)
        save_score(h);
    sfText_destroy(h->stext);
    sfText_destroy(h->itext);
    sfSprite_destroy(h->opixel);
    sfSprite_destroy(h->rpixel);
    sfSprite_destroy(h->gpixel);
    sfSprite_destroy(h->bsprite);
    sfText_destroy(h->text);
    sfFont_destroy(h->font);
    sfMusic_destroy(h->music);
    terminate_cursor(&(h->cursor));
    terminate_master_duck(&(h->master_d));
    terminate_props(&(h->props));
    sfRenderWindow_destroy(h->window);
    sfClock_destroy(h->clock);
    return EXIT_SUCCESS;
}
