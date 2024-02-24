#ifndef PONG_ENGINE_H
#define PONG_ENGINE_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define P1_PADDLE_X_POS 2
#define P2_PADDLE_X_POS 77
#define BALL_SPEED 2
#define SCORE_TO_WIN 21

int draw(int p1_y, int p2_y, int ball_x, int ball_y, int p1_score, int p2_score);
void draw_winner(int winner);
int check_collisions(int ball_x, int ball_y, int vec_x, int vec_y, int p1_y, int p2_y);
void clear_screen();

#endif