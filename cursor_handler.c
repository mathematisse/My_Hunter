/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** Handlers for cursor struct
*/

#include "hunter.h"

int init_cursor(cursor_t *c)
{
    c->range = 1.5;
    c->secfor_reload = 2;
    c->timer = c->secfor_reload;
    c->beam_active = 0;
    c->x = 0;
    c->y = 0;
    c->sbuf = sfSoundBuffer_createFromFile("ressources/beam.ogg");
    c->sound = sfSound_create();
    sfSound_setBuffer(c->sound, c->sbuf);
    sfSound_setVolume(c->sound, 20);
    make_sprite_path(&(c->crosshair), "ressources/crosshair.png");
    make_sprite_path(&(c->cannon), "ressources/cannon.png");
    make_sprite_path(&(c->base), "ressources/cbase.png");
    make_sprite_path(&(c->beam), "ressources/beam.png");
    make_sprite_path(&(c->pixel), "ressources/pixel.png");
    init_renderer(&(c->renderer));
    c->cannont = sfTransform_Identity;
    c->beamt = sfTransform_Identity;
    sfTransform_translate(&(c->cannont), 960 - 64, 925 - 64);
    return EXIT_SUCCESS;
}

int make_beam(cursor_t *c, int x, int y)
{
    float angle = 0;

    if (c->beam_active || c->timer < c->secfor_reload)
        return 0;
    sfSound_play(c->sound);
    c->timer = 0;
    c->beam_active = 1;
    c->beamt = sfTransform_Identity;
    sfTransform_translate(&(c->beamt), 960 - 4, 925 - 64);
    angle = get_canangle(x, y);
    sfTransform_rotateWithCenter(&(c->beamt), angle, 4, 64);
    return 1;
}

void loop_beam(sfRenderWindow *w, cursor_t *c, float dt)
{
    c->timer += dt;
    if (c->timer > c->secfor_reload)
        c->timer = c->secfor_reload;
    if (!c->beam_active)
        return;
    c->renderer.transform = c->beamt;
    sfRenderWindow_drawSprite(w, c->beam, &(c->renderer));
    sfTransform_translate(&(c->beamt), 0, -10000 * dt);
    if (c->beamt.matrix[2] < -130)
        c->beam_active = 0;
    if (c->beamt.matrix[2] > 2050)
        c->beam_active = 0;
    if (c->beamt.matrix[5] < -130)
        c->beam_active = 0;
}

void loop_cursor(sfRenderWindow *w, cursor_t *c, float dt)
{
    float angle = 0;
    sfTransform *transform = &(c->renderer.transform);

    loop_beam(w, c, dt);
    angle = get_canangle(c->x, c->y);
    *transform = sfTransform_Identity;
    transform->matrix[2] = c->x - 16;
    transform->matrix[5] = c->y - 16;
    sfRenderWindow_drawSprite(w, c->crosshair, &(c->renderer));
    *transform = c->cannont;
    sfTransform_translate(transform, 63, 64);
    sfTransform_rotateWithCenter(transform, (angle - c->range) + 180, 1, 0);
    sfRenderWindow_drawSprite(w, c->pixel, &(c->renderer));
    sfTransform_rotateWithCenter(transform, c->range * 2, 1, 0);
    sfRenderWindow_drawSprite(w, c->pixel, &(c->renderer));
    *transform = c->cannont;
    sfTransform_rotateWithCenter(transform, angle, 64, 64);
    sfRenderWindow_drawSprite(w, c->cannon, &(c->renderer));
    c->renderer.transform = c->cannont;
    sfRenderWindow_drawSprite(w, c->base, &(c->renderer));
}

void terminate_cursor(cursor_t *c)
{
    sfSprite_destroy(c->pixel);
    sfSoundBuffer_destroy(c->sbuf);
    sfSound_destroy(c->sound);
    sfSprite_destroy(c->crosshair);
    sfSprite_destroy(c->cannon);
    sfSprite_destroy(c->base);
}
