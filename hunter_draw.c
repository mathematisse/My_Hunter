/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

void draw_bstats(hunter_t *h)
{
    sfRenderStates temp;

    sfRenderWindow_drawSprite(h->window, h->bsprite, &(h->brenderer));
    temp = h->brenderer;
    sfTransform_translate(&(temp.transform), 643, 3);
    sfTransform_scale(
        &(temp.transform),
        634 * (h->cursor.timer / h->cursor.secfor_reload),
        11);
    sfRenderWindow_drawSprite(h->window, h->opixel, &temp);
    temp = h->brenderer;
    sfTransform_translate(&(temp.transform), 643, 17);
    sfTransform_scale(&(temp.transform), h->nrj * 63.4, 11);
    sfRenderWindow_drawSprite(h->window, h->gpixel, &temp);
    temp = h->brenderer;
    sfTransform_translate(&(temp.transform), 643, 31);
    sfTransform_scale(&(temp.transform), h->dmg, 11);
    sfRenderWindow_drawSprite(h->window, h->rpixel, &temp);
}

void removezero(char *str)
{
    int i = 0;

    while (str[i] != 0)
        i++;
    str[i] = '\n';
}

void draw_loop(hunter_t *h)
{
    sfRenderStates temp;
    char istr[20] = "Dead Ducks:        ";
    char sstr[40] = "Longest :          \nScore :           ";

    sfRenderWindow_drawSprite(h->window, h->bsprite, &(h->brenderer));
    draw_bstats(h);
    changestr(istr + 12, h->killed - h->spent);
    sfText_setString(h->text, istr);
    sfText_setFont(h->text, h->font);
    sfText_setCharacterSize(h->text, 40);
    sfRenderWindow_drawText(h->window, h->text, &(h->trenderer));
    init_renderer(&temp);
    changestr(sstr + 10, h->highest);
    removezero(sstr);
    changestr(sstr + 30, h->elapsed_time);
    sfText_setString(h->stext, sstr);
    sfText_setFont(h->stext, h->font);
    sfText_setCharacterSize(h->stext, 40);
    sfRenderWindow_drawText(h->window, h->stext, &temp);
}
