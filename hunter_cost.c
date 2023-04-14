/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

void set_infotext(hunter_t *h, char *str, int cost, int len)
{
    int av = h->killed - h->spent;
    changestr(str + len, cost);
    sfText_setString(h->itext, str);
    sfText_setFont(h->itext, h->font);
    sfText_setCharacterSize(h->itext, 30);
    sfText_setColor(h->itext, (av >= cost ? sfGreen : sfRed));
}

int get_pcost(int p)
{
    int cost = 0;
    cost = (1 + p) * 2;
    cost *= cost / 2;
    cost += 5;
    return cost;
}

int get_tcost(int t)
{
    int cost = 0;
    cost = (1 + t) * 2;
    cost *= cost / 2;
    cost += 5;
    return cost;
}

int get_rcost(float r)
{
    int cost = 0;
    cost = (1 / (r / 2)) * 3;
    cost *= cost / 2;
    cost += 5;
    return cost;
}

int get_acost(float a)
{
    int cost = 0;
    cost = a * 2;
    cost *= cost / 2;
    cost += 5;
    return cost;
}
