#include <ncurses.h>
#include <stdio.h>

#include "pong_interactive_engine.h"

int main(void) {
    /*  Start curses mode */
    init_ncurses();

    int p1_score = 0;
    int p2_score = 0;
    int p_start = 1;

    int frame_counter = 0;

    while (p1_score < SCORE_TO_WIN && p2_score < SCORE_TO_WIN) {
        /* Initialization */
        int p1_y = SCREEN_HEIGHT / 2;
        int p2_y = SCREEN_HEIGHT / 2;

        /* Ball init */
        int ball_x = 0;
        int ball_y = 0;
        int ball_mov_x = 0;
        int ball_mov_y = 0;
        /* Ball init */
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

            char key_pressed = 0;
            /* Wait for user input */
            key_pressed = getch();
            napms(10);

            /* Player 1 movement */
            if ((key_pressed == 'A' || key_pressed == 'a') && p1_y > 1) p1_y--;
            if ((key_pressed == 'Z' || key_pressed == 'z') && p1_y < SCREEN_HEIGHT - 2) p1_y++;

            /* Player 2 movement */
            if ((key_pressed == 'K' || key_pressed == 'k') && p2_y > 1) p2_y--;
            if ((key_pressed == 'M' || key_pressed == 'm') && p2_y < SCREEN_HEIGHT - 2) p2_y++;
            frame_counter = (frame_counter + 1) % 10; /* Reduce input lag */
            if (frame_counter == 0) {
                /* Ball movement */
                int collision_check_result = 0;
                int exit_flag = 0;
                for (int moves = 0;
                     moves < BALL_SPEED && collision_check_result != 100 && collision_check_result != -100;
                     moves++) {
                    collision_check_result =
                        check_collisions(ball_x, ball_y, ball_mov_x, ball_mov_y, p1_y, p2_y);
                    if (collision_check_result == 1)
                        ball_mov_y *= -1;
                    else if (collision_check_result == -1)
                        ball_mov_x *= -1;
                    else if (collision_check_result == 100) {
                        p1_score++;
                        p_start = 2;
                        exit_flag = 1;
                    } else if (collision_check_result == -100) {
                        p2_score++;
                        p_start = 1;
                        exit_flag = 1;
                    }
                    ball_x += ball_mov_x;
                    ball_y += ball_mov_y;
                    if (exit_flag == 1) break;
                }
                if (collision_check_result == -100 || collision_check_result == 100) break;
            }
        }
    }
    draw_winner(p1_score > p2_score ? 1 : 2);
    napms(3000);
    endwin(); /* End curses mode */
    return 0;
}
