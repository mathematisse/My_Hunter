/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for duck struct
*/

#include "hunter.h"
#include <stdio.h>
#include <time.h>

void loop_poop(duck_t *d, float dt)
{
    if (d->dstate == Flying && d->poosition.matrix[5] < 0) {
        d->ptimer += dt;
        if (d->ptimer > d->sectopoop) {
            d->poosition = d->transform;
            d->poosition.matrix[2] += d->poosition.matrix[0] == -1 ? -32 : 32;
            d->poosition.matrix[5] += 16;
            d->ptimer = 0;
        }
    } else if (d->poosition.matrix[5] > 0) {
        sfTransform_translate(&(d->poosition), 0, dt * 300);
    }
}

void loop_duck(duck_t *d, float dt, unsigned seed)
{
    loop_poop(d, dt);
    d->timer += dt;
    switch (d->dstate) {
    case Starting: spawn_duck(d, seed); break;
    case Restarting: restart_duck(d, seed); break;
    case Flying: fly_duck(d, dt); break;
    case Dead: dead_duck(d, dt); break;
    case Taking_Off :taking_off_duck(d, dt); break;
    case Waiting: wait_duck(d); break;
    default: return;
    }
}

int master_loop_duck(sfRenderWindow *w, master_duck_t *m_d, duck_t *d)
{
    int pooplanded = 0;

    if (d->dstate == Unused && m_d->donew) {
        m_d->donew = 0;
        d->dstate = Starting;
        sfSound_play(m_d->qsound);
    }
    if (d->dstate == Taking_Off || d->dstate == Flying || d->dstate == Dead) {
        m_d->renderer.transform = d->transform;
        sfRenderWindow_drawSprite
            (w, m_d->sprites[d->state + d->colorchg], &(m_d->renderer));
    }
    if (d->poosition.matrix[5] > 1000) {
        d->poosition.matrix[5] = -1;
        pooplanded++;
    } else if (d->poosition.matrix[5] > 0) {
        m_d->renderer.transform = d->poosition;
        sfRenderWindow_drawSprite(w, m_d->shit, &(m_d->renderer));
    }
    return pooplanded;
}

int loop_master_duck(sfRenderWindow *w, master_duck_t *m_d, float dt)
{
    int dmg = 0;
    unsigned seed = time(NULL);

    m_d->timer += dt;
    if (m_d->timer > m_d->secfornew) {
        m_d->donew = 1;
        m_d->timer = 0;
    }
    for (int i = 0; i < m_d->dcount; i++) {
        loop_duck(m_d->duck + i, dt, ++seed);
        dmg += master_loop_duck(w, m_d, m_d->duck + i);
    }
    if (dmg > 0)
        sfSound_play(m_d->sound);
    return dmg;
}
