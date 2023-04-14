/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** kill functions for my_hunter
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

int kill_duck(duck_t *d, int x, int y, float range)
{
    float deltangle = 0;
    float chg = d->transform.matrix[0] == -1 ? -32 : 32;
    float dx = d->transform.matrix[2] + chg;
    float dy = d->transform.matrix[5] + 16;

    deltangle = get_canangle(x, y);
    deltangle -= get_canangle(dx, dy);
    if (deltangle > range || deltangle < -range)
        return 0;
    d->dstate = Dead;
    d->state = 6;
    d->timer = 0;
    return 1;
}

int kill_ducks(master_duck_t *m_d, int x, int y, float range)
{
    int sum = 0;

    for (int i = 0; i < m_d->dcount; i++)
        if (m_d->duck[i].dstate == Flying || m_d->duck[i].dstate == Taking_Off)
            sum += kill_duck(m_d->duck + i, x, y, range);
    return sum;
}

int shoot(hunter_t *h, int x, int y)
{
    if (h->nrj < 1)
        return 0;
    if (make_beam(&(h->cursor), x, y) == 0)
        return 0;
    h->nrj -= 1;
    return kill_ducks(&(h->master_d), x, y, h->cursor.range);
}
