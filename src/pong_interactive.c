#include <ncurses.h>
#include <stdio.h>

//ДЛЯ КОМПИЛЯТОРА
// gcc -Wall -Werror -Wextra -Xlinker -lncurses

int racket_engine(char button, int coord);
char user_input(int user_id);
void draw_field(int y_racket_1, int y_racket_2, int x_ball, int y_ball, int user_score_1, int user_score_2);
int ball_engine(int x_ball, int y_ball, int vector_x_ball, int vector_y_ball, int y_racket_1, int y_racket_2);
void win_draw_field(int winner);
void quit_draw_field();

int main(void) {
    initscr();
    noecho();
    halfdelay(2);

    int x_ball = 40;
    int y_ball = 13;
    int vector_x_ball = -1;
    int vector_y_ball = -1;
    int y_racket_1 = 11;
    int y_racket_2 = 11;
    int user_score_1 = 0;
    int user_score_2 = 0;
    int winner;
    char button = 'H';

    while (user_score_1 < 21 && user_score_2 < 21) {
        clear();
        draw_field(y_racket_1, y_racket_2, x_ball, y_ball, user_score_1, user_score_2);
        button = getch();
        if ((button == 'A' || button == 'a') && y_racket_1 > 0)
            y_racket_1--;
        else if ((button == 'Z' || button == 'z') && y_racket_1 < 23)
            y_racket_1++;
        else if ((button == 'K' || button == 'k') && y_racket_2 > 0)
            y_racket_2--;
        else if ((button == 'M' || button == 'm') && y_racket_2 < 23)
            y_racket_2++;

        if (button == 'Q' || button == 'q') break;

        int data = ball_engine(x_ball, y_ball, vector_x_ball, vector_y_ball, y_racket_1, y_racket_2);

        if (data < 3) {
            (data == 1) ? user_score_1++ : user_score_2++;
            x_ball = 40;
            y_ball = 13;
            y_racket_1 = 11;
            y_racket_2 = 11;
        } else {
            x_ball = data / 10000 % 100;
            y_ball = data / 100 % 100;
            vector_x_ball = (data / 10 % 10 == 2) ? -1 : 1;
            vector_y_ball = (data % 10 == 2) ? -1 : 1;
        }
    }

    winner = (user_score_1 > user_score_2) ? 1 : 2;
    clear();
    if (button == 'Q' || button == 'q') {
        quit_draw_field();
    } else {
        win_draw_field(winner);
    }
    halfdelay(30);
    getch();

    endwin();
    return 0;
}

int ball_engine(int x_ball, int y_ball, int vector_x_ball, int vector_y_ball, int y_racket_1,
                int y_racket_2) {
    if (y_ball == 0 || y_ball == 25) {
        vector_y_ball *= -1;
    }

    if (x_ball == 1) {
        if (y_ball >= y_racket_1 && y_ball <= y_racket_1 + 2)
            vector_x_ball *= -1;
        else
            return 2;
    }

    if (x_ball == 79) {
        if (y_ball >= y_racket_2 && y_ball <= y_racket_2 + 2)
            vector_x_ball *= -1;
        else
            return 1;
    }

    x_ball = x_ball + vector_x_ball;
    y_ball = y_ball + vector_y_ball;

    if (vector_x_ball < 0) {
        vector_x_ball = 2;
    }
    if (vector_y_ball < 0) {
        vector_y_ball = 2;
    }

    int returned_value = 1000000 + x_ball * 10000 + y_ball * 100 + vector_x_ball * 10 + vector_y_ball;
    return returned_value;
}

// DRAW FUNCTIONS

void draw_field(int y_racket_1, int y_racket_2, int x_ball, int y_ball, int user_score_1, int user_score_2) {
    for (int i = -2; i <= 26; i++) {
        for (int j = -1; j <= 81; j++)
            if (i == -2 && j == 36) {
                printw("%d", user_score_1);
                if (user_score_1 > 9) j++;
            } else if (i == -2 && j == 45) {
                printw("%d", user_score_2);
                if (user_score_2 > 9) j++;
            } else if (i == -1 || i == 26 || j == -1 || j == 81)
                printw("*");
            else if (j == 0 && i >= y_racket_1 && i < (y_racket_1 + 3))
                printw("|");
            else if (j == 80 && i >= y_racket_2 && i < (y_racket_2 + 3))
                printw("|");
            else if (i == y_ball && j == x_ball)
                printw("0");
            else if (j == 40 && i > 2 && i < 23)
                printw("|");
            else
                printw(" ");
        printw("\n");
    }
}

void win_draw_field(int winner) {
    for (int i = -2; i <= 26; i++) {
        for (int j = -1; j <= 81; j++)
            if (i == -1 || i == 26 || j == -1 || j == 81)
                printw("*");
            else if (i == 13 && j == 34) {
                printw("PLAYER %d WIN!", winner);
                j = j + 12;
            } else
                printw(" ");
        printw("\n");
    }
}

void quit_draw_field() {
    for (int i = -2; i <= 26; i++) {
        for (int j = -1; j <= 81; j++)
            if (i == -1 || i == 26 || j == -1 || j == 81)
                printw("*");
            else if (i == 13 && j == 34) {
                printw("GOOD BYE!");
                j = j + 8;
            } else
                printw(" ");
        printw("\n");
    }
}
