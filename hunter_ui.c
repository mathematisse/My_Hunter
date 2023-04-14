/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

int switch_menu_event(hunter_t *h)
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
        if (e.mouseButton.button == sfMouseLeft) {
            handle_menuclick(h, e.mouseButton.x, e.mouseButton.y);
        }
        break;
    default: ;
    }
    return 0;
}

void loop_menu(hunter_t *h)
{
    int xbutsize = 400, ybutsize = 200;
    sfRenderStates temp;

    while (sfRenderWindow_pollEvent(h->window, &(h->event)))
        if (switch_menu_event(h) == -1)
            return;
    sfRenderWindow_clear(h->window, sfColor_fromRGB(93, 182, 233));
    init_renderer(&temp);
    sfTransform_translate(&(temp.transform), 790, 200);
    sfTransform_scale(&(temp.transform), xbutsize, ybutsize);
    sfRenderWindow_drawSprite(h->window, h->gpixel, &temp);
    temp.transform.matrix[5] += 200;
    sfRenderWindow_drawSprite(h->window, h->opixel, &temp);
    temp.transform.matrix[5] += 200;
    sfRenderWindow_drawSprite(h->window, h->rpixel, &temp);
    loop_cursor(h->window, &(h->cursor), h->dt);
    init_renderer(&temp);
    sfTransform_translate(&(temp.transform), 890, 100);
    sfRenderWindow_drawText(h->window, h->mtext, &temp);
    sfRenderWindow_display(h->window);
}
