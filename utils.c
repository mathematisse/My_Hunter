/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** CSFML utils
*/

#include "hunter.h"
#include <math.h>
#include <stdio.h>

void save_score(hunter_t *h)
{
    char str[10] = "        E";
    FILE *fp;
    int i = 7;

    fp = fopen(h->maxpath, "w");
    for (; ((int) h->elapsed_time) > 0; i--) {
        str[i] = (((int)h->elapsed_time) % 10) + 48;
        h->elapsed_time /= 10;
    }
    for (; i >= 0; i--)
        str[i] = 48;
    fwrite(str, 1, sizeof(str), fp);
    fclose(fp);
}

void init_music(sfMusic **m, char *path, float vol)
{
    *m = sfMusic_createFromFile(path);
    sfMusic_setVolume(*m, vol);
    sfMusic_setLoop(*m, sfTrue);
}

void init_text(sfFont *f, char *str, sfText **t, int size)
{
    *t = sfText_create();
    sfText_setString(*t, str);
    sfText_setFont(*t, f);
    sfText_setCharacterSize(*t, size);
}

int load_texture(char *str, sfTexture **texture, sfIntRect *rect)
{
    *texture = sfTexture_createFromFile(str, rect);
    if (!*texture)
        return 84;
    return 0;
}

void make_sprite(sfSprite **sprite, sfTexture *texture)
{
    *sprite = sfSprite_create();
    sfSprite_setTexture(*sprite, texture, sfTrue);
}
