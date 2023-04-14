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
int duck_is_out(sfTransform *t)
{
    int x = t->matrix[2];
    int y = t->matrix[5];
    if (x < -70 || x > 1990)
        return 1;
    if (y > 1000)
        return 1;
    return 0;
}

void wait_duck(duck_t *d)
{
    const float seconds_waiting = 10;

    if (d->timer > seconds_waiting) {
        d->dstate = Starting;
        d->timer = 0;
    }
}

void dead_duck(duck_t *d, float dt)
{
    const float seconds_to_fall = 0.3;
    float deltax = dt * 300;

    if (d->state != 7) {
        if (d->timer > seconds_to_fall)
            d->state++;
    } else {
        sfTransform_translate(&(d->transform), 0, deltax);
        if (duck_is_out(&(d->transform)))
            d->dstate = Waiting;
    }
}

void fly_duck(duck_t *d, float dt)
{
    const float seconds_per_texture = 0.2;
    float deltax = dt * 100 * d->speed;

    if (d->timer > seconds_per_texture) {
        d->state += (d->state == 2 ? -2 : 1);
        d->timer -= seconds_per_texture;
    }
    sfTransform_translate(&(d->transform), deltax, 0);
    if (duck_is_out(&(d->transform))) {
        d->dstate = Restarting;
        return;
    }
}

void taking_off_duck(duck_t *d, float dt)
{
    float seconds_per_texture = 0.2 / d->speed;
    float deltax = dt * 100 * d->speed;

    deltax *= deltax;
    deltax = sqrt(deltax / 2);
    if (d->timer > seconds_per_texture) {
        d->state += (d->state == 5 ? -2 : 1);
        d->timer -= seconds_per_texture;
    }
    sfTransform_translate(&(d->transform), deltax, - deltax);
    if (duck_is_out(&(d->transform))) {
        d->dstate = Restarting;
        return;
    }
    if (d->transform.matrix[5] < d->crusey){
        d->dstate = Flying;
        d->state = 0;
    }
}
