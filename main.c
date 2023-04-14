/*
** EPITECH PROJECT, 2022
** B-MUL-100-TLS-1-1-myhunter-lucien.pineau
** File description:
** main functions for my_hunter
*/

#include <stdio.h>
#include "hunter.h"
#include <unistd.h>

void loop_game(hunter_t *h)
{
    switch (h->hstate) {
    case Menu: loop_menu(h); break;
    case Playing: loop_hunt(h); break;
    case Paused: break;
    case End: h->hstate = Quit; break;
    case Quit: sfRenderWindow_close(h->window); break;
    default: ;
    }
}

int do_hunt(void)
{
    hunter_t hunter;

    if (init_hunt(&hunter))
        return EXIT_FAILURE;
    if (launch_hunt(&hunter))
        return EXIT_FAILURE;
    while (sfRenderWindow_isOpen(hunter.window))
        loop_game(&hunter);
    if (terminate_hunt(&hunter))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int show_help(void)
{
    write(1, "\nSHOOT OR GET SHITTED !!\n\n\n", 27);
    write(1, "Pick a difficulty and click to shoot\n", 37);
    write(1, "Buy trees to recycle guam\n", 27);
    write(1, "Buy solar panels to recharge faster\n", 36);
    write(1, "Upgrade the shooting speed or angle\n", 36);
    write(1, "Avoid the guam (red line) to fill!!\n\n", 37);
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h')
            return show_help();
        return 84;
    }
    return do_hunt();
}
