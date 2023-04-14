/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** CSFML utils
*/

#include "hunter.h"
#include <math.h>

void copyhstr(char **trgt, char *src)
{
    int i = 0;

    for (; src[i] != 0; i++)
        (*trgt)[i] = src[i];
    (*trgt)[i] = 0;
}

void changestr(char *str, int c)
{
    int i = 0;
    int ct = c;
    char t[8];

    for (; ct > 0; i++) {
        t[i] = (ct % 10) + 48;
        ct /= 10;
    }
    i--;
    for (; i >= 0; i--){
        *str = t[i];
        str++;
    }
    *str = 0;
}

float get_canangle(int px, int py)
{
    int y = py > 924 ? 924 : py;
    float xangle = (float) px - 960;
    float yangle = (float) y - 925;
    float angle = atan(xangle / yangle);

    return angle * -57.2958;
}

void init_renderer(sfRenderStates *rs)
{
    rs->blendMode = sfBlendAlpha;
    rs->transform = sfTransform_Identity;
    rs->texture = NULL;
    rs->shader = NULL;
}

void make_sprite_path(sfSprite **sprite, char *path)
{
    sfTexture *temp = NULL;

    load_texture(path, &(temp), NULL);
    *sprite = sfSprite_create();
    sfSprite_setTexture(*sprite, temp, sfTrue);
}
