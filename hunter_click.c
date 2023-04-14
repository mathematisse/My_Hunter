/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

void handle_barmove(hunter_t *h, int x, int y)
{
    char tstr[20] = "Tree,              ";
    char pstr[20] = "Panel,             ";
    char rstr[20] = "Speed,             ";
    char astr[20] = "Angle,             ";
    int index = get_barbutindex(x, y);

    if (index == -1)
        return;
    init_renderer(&(h->istates));
    switch (index) {
    case 0: set_infotext(h, tstr, get_tcost(h->props.tcount), 6); break;
    case 1: set_infotext(h, pstr, get_pcost(h->props.pcount), 7); break;
    case 2: set_infotext(h, rstr, get_rcost(h->cursor.secfor_reload), 7); break;
    case 3: set_infotext(h, astr, get_acost(h->cursor.range), 7); break;
    default: return;
    }
    sfTransform_translate(&(h->istates.transform), (index * 53) + 22, 985);
    sfRenderWindow_drawText(h->window, h->itext, &(h->istates));
}

void handle_barclick(hunter_t *h, int x, int y)
{
    int index = get_barbutindex(x, y);
    int av = h->killed - h->spent, cost = 0;

    switch (index) {
    case 0: cost = get_tcost(h->props.tcount); break;
    case 1: cost = get_pcost(h->props.pcount); break;
    case 2: cost = get_rcost(h->cursor.secfor_reload); break;
    case 3: cost = get_acost(h->cursor.range); break;
    default: return;
    }
    if (av < cost)
        return;
    switch (index) {
    case 0: h->props.tcount++; break;
    case 1: h->props.pcount++; break;
    case 2: h->cursor.secfor_reload *= 0.8; break;
    case 3: h->cursor.range += 0.2; break;
    default: return;
    }
    h->spent += cost;
}

void set_huntlevel(hunter_t *h, int lvl)
{
    FILE *fp;
    char c = 0;

    switch (lvl) {
    case 0: copyhstr(&(h->maxpath), "easymax.txt"); break;
    case 1: copyhstr(&(h->maxpath), "mediummax.txt"); break;
    case 2: copyhstr(&(h->maxpath), "hardmax.txt"); break;
    }
    fp = fopen(h->maxpath, "r");
    c = fgetc(fp);
    while (c != 69) {
        h->highest *= 10;
        h->highest += c - 48;
        c = fgetc(fp);
    }
    h->master_d.secfornew = (3 - lvl) * 2;
    if (lvl == 2)
        h->master_d.secfornew = 0.001;
    fclose(fp);
}

void handle_menuclick(hunter_t *h, int x, int y)
{
    int index = get_menubut(x, y);

    if (index == -1)
        return;
    if (index == 3) {
        h->hstate = Quit;
        return;
    }
    set_huntlevel(h, index);
    h->hstate = Playing;
}

void handle_click(hunter_t *h, sfMouseButtonEvent e)
{
    if (e.button == sfMouseLeft) {
        if (e.y < 900)
            h->is_shooting = sfTrue;
        else
            handle_barclick(h, e.x, e.y);
    }
}
