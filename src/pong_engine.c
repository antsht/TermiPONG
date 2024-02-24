#include "pong_engine.h"

#include <stdio.h>

int draw(int p1_y, int p2_y, int ball_x, int ball_y, int p1_score, int p2_score) {
    clear_screen();
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printf("-");
    printf("\n");
    /* draw field */
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        printf(">");
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (ball_x == x && ball_y == y) {
                printf("@");
            } else if (x == SCREEN_WIDTH / 2) {
                printf("|");
            } else if (x == SCREEN_WIDTH / 2 + 1) {
                printf("|");
            } else if (y == 0 && x == SCREEN_WIDTH / 4) {
                printf("%2d", p1_score);
                x++;
            } else if (y == 0 && x == SCREEN_WIDTH - SCREEN_WIDTH / 4) {
                printf("%2d", p2_score);
                x++;
            } else if (p1_y - 1 <= y && y <= p1_y + 1 && x == P1_PADDLE_X_POS) {
                printf("]");
            } else if (p2_y - 1 <= y && y <= p2_y + 1 && x == P2_PADDLE_X_POS) {
                printf("[");
            } else
                printf(" ");
        }
        printf("<");
        printf("\n");
    }
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printf("-");
    printf("\n");
    printf("\nPONGWARE (c)\n");
    return 0;
}

void draw_winner(int winner) {
    clear_screen();
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printf("-");
    printf("\n");
    /* draw field */
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y == SCREEN_HEIGHT / 2) {
            for (int x = 0; x < SCREEN_WIDTH / 2 - 12; x++) {
                printf(" ");
            }
            printf("Player %d WIN!!!!!!!!!!!!", winner);
        }
        printf("\n");
    }
    for (int i = 0; i < SCREEN_WIDTH + 2; i++) printf("-");
    printf("\n");
    printf("\nPONGWARE (c)\n");
}

int check_collisions(int ball_x, int ball_y, int vec_x, int vec_y, int p1_y, int p2_y) {
    /* Проверка на соприкосновение с ракеткой первого игрока */
    if (ball_x + vec_x == P1_PADDLE_X_POS && p1_y - 1 <= ball_y + vec_y && ball_y + vec_y <= p1_y + 1) {
        return -1;
    }
    /* Проверка на соприкосновение с ракеткой второго игрока */
    else if (ball_x + vec_x == P2_PADDLE_X_POS && p2_y - 1 <= ball_y + vec_y && ball_y + vec_y <= p2_y + 1) {
        return -1;
    }
    /* Проверка на соприкосновение верхней или нижней границей */
    else if (ball_y + vec_y == -1 || ball_y + vec_y == SCREEN_HEIGHT - 1) {
        return 1;
    }
    /* Проверка на гол первому игроку */
    else if (ball_x + vec_x == P1_PADDLE_X_POS) {
        return -100;
    }
    /* Проверка на гол второму игроку */
    else if (ball_x + vec_x == P2_PADDLE_X_POS) {
        return 100;
    }
    return 0;
}

void clear_screen() { printf("\033[2J\033[1;1H"); }
