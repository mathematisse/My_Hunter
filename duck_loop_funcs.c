/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for duck struct
*/

#include "hunter.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

void restart_duck(duck_t *d, unsigned seed)
{
    const int miny = 50;
    const int maxy = 500;
    int x = -64;
    int y = 0;

    if (d->timer < d->sectostart)
        return;
    d->state = 0;
    d->transform = sfTransform_Identity;
    d->timer = 0;
    srand(seed);
    if (rand() % 100 < 50) {
        x = (1920 + 64) * -1;
        sfTransform_scale(&(d->transform), -1, 1);
    }
    y = miny + (rand() % (maxy - miny));
    sfTransform_translate(&(d->transform), x, y);
    d->dstate = Flying;
}

void spawn_duck(duck_t *d, unsigned seed)
{
    const int miny = 50;
    const int maxy = 500;
    int x = -64, y = 1000;

    srand(seed);
    x = (rand() % 1500);
    if (d->timer < d->sectostart)
        return;
    d->colorchg = 8 * (rand() % 3);
    d->speed = 1 + (((float)(rand() % 10000)) / 10000);
    d->state = 0;
    d->transform = sfTransform_Identity;
    d->timer = 0;
    if (rand() % 100 < 50) {
        x = ((rand() % 1500) * -1) - 480;
        sfTransform_scale(&(d->transform), -1, 1);
    }
    d->crusey = miny + (rand() % (maxy - miny));
    sfTransform_translate(&(d->transform), x, y);
    d->dstate = Taking_Off;
}
