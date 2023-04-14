/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** Handlers for duck struct
*/

#include "hunter.h"
#include <time.h>

void init_duck(duck_t *d, unsigned seed)
{
    srand(seed);
    d->sectostart = ((float) (rand() % 10000)) / 1000;
    d->transform = sfTransform_Identity;
    sfTransform_translate(&(d->transform), 0, 0);
    d->dstate = Unused;
    d->state = 0;
    d->timer = 0;
    d->ptimer = 0;
    d->sectopoop = 1 + ((float) (rand() % 2000)) / 1000;
    d->poosition = sfTransform_Identity;
    d->poosition.matrix[5] = -1;
}

void init_sprites(master_duck_t *m_d)
{
    sfImage *img = NULL;
    sfTexture *texture;
    sfIntRect area = {.left = 0, .top = 0, .width = 64, .height = 32};

    img = sfImage_createFromFile("ressources/ducks.png");
    for (int i = 0; i < 24; i++) {
        texture = sfTexture_createFromImage(img, &area);
        make_sprite(m_d->sprites + i, texture);
        area.left += 64;
        if (area.left == 512) {
            area.left = 0;
            area.top += 32;
        }
    }
}

int init_master_duck(master_duck_t *m_d)
{
    unsigned seed = time(NULL);

    m_d->sbuf = sfSoundBuffer_createFromFile("ressources/splash.ogg");
    m_d->sound = sfSound_create();
    sfSound_setBuffer(m_d->sound, m_d->sbuf);
    m_d->qsbuf = sfSoundBuffer_createFromFile("ressources/quack.ogg");
    m_d->qsound = sfSound_create();
    sfSound_setBuffer(m_d->qsound, m_d->qsbuf);
    sfSound_setVolume(m_d->qsound, 30);
    sfSound_setVolume(m_d->sound, 20);
    m_d->dcount = 10000;
    m_d->donew = 0;
    m_d->secfornew = 1;
    m_d->duck = malloc(sizeof(duck_t) * m_d->dcount);
    for (int i = 0; i < m_d->dcount; i++)
        init_duck(m_d->duck + i, ++seed);
    make_sprite_path(&(m_d->shit), "ressources/shit.png");
    init_sprites(m_d);
    init_renderer(&(m_d->renderer));
    return EXIT_SUCCESS;
}

void terminate_master_duck(master_duck_t *m_d)
{
    sfSoundBuffer_destroy(m_d->sbuf);
    sfSound_destroy(m_d->sound);
    sfSoundBuffer_destroy(m_d->qsbuf);
    sfSound_destroy(m_d->qsound);
    for (int i = 0; i < 24; i++)
        sfSprite_destroy(m_d->sprites[i]);
    sfSprite_destroy(m_d->shit);
}
