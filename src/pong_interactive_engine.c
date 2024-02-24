#include "pong_interactive_engine.h"

#include <ncurses.h>
#include <stdio.h>

void init_ncurses() {
    initscr();
    savetty();
    cbreak();
    noecho();
    timeout(0);
    curs_set(0);
}

int check_collisions(int ball_x, int ball_y, int vec_x, int vec_y, int p1_y, int p2_y) {
    int collision_status = 0;
    /* Проверка на соприкосновение с ракеткой первого игрока */
    if (ball_x + vec_x == P1_PADDLE_X_POS && p1_y - 2 <= ball_y + vec_y && ball_y + vec_y <= p1_y + 2)
        collision_status = -1;
    /* Проверка на соприкосновение с ракеткой второго игрока */
    else if (ball_x + vec_x == P2_PADDLE_X_POS && p2_y - 2 <= ball_y + vec_y && ball_y + vec_y <= p2_y + 2)
        collision_status = -1;
    /* Проверка на соприкосновение верхней или нижней границей */
    else if (ball_y + vec_y == -1 || ball_y + vec_y == SCREEN_HEIGHT)
        collision_status = 1;
    /* Проверка на гол первому игроку */
    else if (ball_x + vec_x == P1_PADDLE_X_POS)
        collision_status = -100;
    /* Проверка на гол второму игроку */
    else if (ball_x + vec_x == P2_PADDLE_X_POS)
        collision_status = 100;
    return collision_status;
}

int draw(int p1_y, int p2_y, int ball_x, int ball_y, int p1_score, int p2_score) {
    erase();
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printw("-");
    printw("\n");
    /* draw field */
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        printw(">");
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (ball_x == x && ball_y == y) {
                printw("o");
            } else if (x == SCREEN_WIDTH / 2) {
                printw("|");
            } else if (x == SCREEN_WIDTH / 2 + 1) {
                printw("|");
            } else if (y == 0 && x == SCREEN_WIDTH / 4) {
                printw("%2d", p1_score);
                x++;
            } else if (y == 0 && x == SCREEN_WIDTH - SCREEN_WIDTH / 4) {
                printw("%2d", p2_score);
                x++;
            } else if (p1_y - 1 <= y && y <= p1_y + 1 && x == P1_PADDLE_X_POS) {
                printw("]");
            } else if (p2_y - 1 <= y && y <= p2_y + 1 && x == P2_PADDLE_X_POS) {
                printw("[");
            } else
                printw(" ");
        }
        printw("<");
        printw("\n");
    }
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printw("-");
    printw("\n");
    printw("\nPongWare (c)\n");
    refresh();
    return 0;
}

void draw_winner(int winner) {
    erase();
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printw("-");
    printw("\n");
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y == SCREEN_HEIGHT / 2) {
            for (int x = 0; x < SCREEN_WIDTH / 2 - 12; x++) {
                printw(" ");
            }
            printw("Player %d WIN!!!!!!!!!!!!", winner);
        }
        printw("\n");
    }
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printw("-");
    printw("\n");
    printw("\nPongWare (c)\n");
    refresh();
}