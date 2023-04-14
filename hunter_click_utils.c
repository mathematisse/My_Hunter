/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** loop functions for hunter struct
*/

#include "hunter.h"
#include <stdio.h>
#include <math.h>

int get_barbutindex(int x, int y)
{
    if (y > 1010 + 5 + 37 || y < 1010 + 5)
        return -1;
    if (x > 181 + 37)
        return -1;
    for (int i = 0; i < 4; i++)
        if (x > (i * 53) + 22 && x < (i * 53) + 22 + 37)
            return i;
    return -1;
}

int get_menubut(int x, int y)
{
    int butstartx = 790;
    int butstarty = 200;
    int butxsize = 400;
    int butysize = 200;
    int butcount = 4;

    if (x < butstartx || x - butstartx > (butcount * butxsize))
        return -1;
    if (y < butstarty || y - butstarty > (butcount * butysize))
        return -1;
    for (int i = 0; i < 4; i++) {
        if ( y - butstarty < butysize * (1 + i))
            return i;
    }
    return -1;
}
