/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

int switch_game_event(hunter_t *h)
{
    sfEvent e = h->event;
    switch (e.type) {
    case sfEvtClosed:
        sfRenderWindow_close(h->window);
        return -1;
    case sfEvtMouseMoved:
        h->cursor.x = e.mouseMove.x;
        h->cursor.y = e.mouseMove.y;
        break;
    case sfEvtMouseButtonPressed:
        handle_click(h, e.mouseButton);
        break;
    case sfEvtMouseButtonReleased:
        if (e.mouseButton.button == sfMouseLeft)
            h->is_shooting = sfFalse;
        break;
    default: ;
    }
    return 0;
}

void loop_clock(hunter_t *h)
{
    float dt = 0;
    dt = sfTime_asSeconds(sfClock_getElapsedTime(h->clock));
    dt -= h->elapsed_time;
    h->elapsed_time += dt;
    h->dt = dt;
}

void loop_data(hunter_t *h)
{
    h->nrj += h->dt * 0.25 * (h->props.pcount + 1);
    if (h->nrj > 10)
        h->nrj = 10;
    h->dmg -= h->props.tcount * h->dt;
    if (h->dmg < 0)
        h->dmg = 0;
    if (h->dmg > 634)
        h->hstate = End;
}

void loop_hunt(hunter_t *h)
{
    while (sfRenderWindow_pollEvent(h->window, &(h->event)))
        if (switch_game_event(h) == -1)
            return;
    if (h->is_shooting)
        h->killed += shoot(h, h->cursor.x, h->cursor.y);
    sfRenderWindow_clear(h->window, sfColor_fromRGB(93, 182, 233));
    loop_clock(h);
    draw_back_props(h->window, &(h->props));
    h->dmg += loop_master_duck(h->window, &(h->master_d), h->dt);
    loop_data(h);
    draw_front_props(h->window, &(h->props));
    draw_loop(h);
    loop_cursor(h->window, &(h->cursor), h->dt);
    if (h->cursor.y > 900)
            handle_barmove(h, h->cursor.x, h->cursor.y);
    sfRenderWindow_display(h->window);
}
