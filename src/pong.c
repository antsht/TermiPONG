#include <stdio.h>

#include "pong_engine.h"

int main(void) {
    int p1_score = 0;
    int p2_score = 0;
    int p_start = 1;

    while (p1_score < SCORE_TO_WIN && p2_score < SCORE_TO_WIN) {
        /* Initialization */
        int p1_y = SCREEN_HEIGHT / 2;
        int p2_y = SCREEN_HEIGHT / 2;

        /* Ball init */
        int ball_x = 0;
        int ball_y = 0;
        int ball_mov_x = 0;
        int ball_mov_y = 0;

        if (p_start == 1) {
            ball_x = SCREEN_WIDTH / 2 - 5;
            ball_y = SCREEN_HEIGHT / 2;
            ball_mov_x = 1;
            ball_mov_y = 1;
        } else {
            ball_x = SCREEN_WIDTH / 2 + 5;
            ball_y = SCREEN_HEIGHT / 2;
            ball_mov_x = -1;
            ball_mov_y = -1;
        }
        while (1) {
            draw(p1_y, p2_y, ball_x, ball_y, p1_score, p2_score);
            char p1_turn = 0;
            char p2_turn = 0;
            /* get user input */
            while (p1_turn != 'a' && p1_turn != 'z' && p1_turn != 'A' && p1_turn != 'Z' && p1_turn != ' ') {
                printf("Player 1 turn: ");
                scanf("%c", &p1_turn);
                draw(p1_y, p2_y, ball_x, ball_y, p1_score, p2_score);
            }
            while (p2_turn != 'k' && p2_turn != 'm' && p2_turn != 'K' && p2_turn != 'M' && p2_turn != ' ') {
                printf("Player 2 turn: ");
                scanf("%c", &p2_turn);
                draw(p1_y, p2_y, ball_x, ball_y, p1_score, p2_score);
            }
            /* Player 1 movement */
            if ((p1_turn == 'A' || p1_turn == 'a') && p1_y > 1) {
                p1_y--;
            }
            if ((p1_turn == 'Z' || p1_turn == 'z') && p1_y < SCREEN_HEIGHT - 1) {
                p1_y++;
            }

            /* Player 2 movement */
            if ((p2_turn == 'K' || p2_turn == 'k') && p2_y > 1) {
                p2_y--;
            }
            if ((p2_turn == 'M' || p2_turn == 'm') && p2_y < SCREEN_HEIGHT - 1) {
                p2_y++;
            }
            int collision_check_result = -1000;
            for (int moves = 0;
                 moves < BALL_SPEED && collision_check_result != 100 && collision_check_result != -100;
                 moves++) {
                collision_check_result = check_collisions(ball_x, ball_y, ball_mov_x, ball_mov_y, p1_y, p2_y);
                if (collision_check_result == 1) {
                    ball_mov_y *= -1;
                } else if (collision_check_result == -1) {
                    ball_mov_x *= -1;
                } else if (collision_check_result == 100) {
                    p1_score++;
                    p_start = 2;
                    break;
                } else if (collision_check_result == -100) {
                    p2_score++;
                    p_start = 1;
                    break;
                }

                ball_x += ball_mov_x;
                ball_y += ball_mov_y;
            }
            if (collision_check_result == -100 || collision_check_result == 100) break;
            p1_turn = 0;
            p2_turn = 0;

            printf("\n%d%d", ball_mov_x, ball_mov_y);
        }
    }

    draw_winner(p1_score > p2_score ? 1 : 2);
    return 0;
}
