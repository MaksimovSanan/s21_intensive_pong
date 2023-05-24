#include <stdio.h>

int racket_engine(char button, int coord);
char user_input(int user_id);
void draw_field(int y_racket_1, int y_racket_2, int x_ball, int y_ball, int user_score_1, int user_score_2);
int ball_engine(int x_ball, int y_ball, int vector_x_ball, int vector_y_ball, int y_racket_1, int y_racket_2);
void win_draw_field(int winner);
void quit_draw_field();

int main(void) {
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
    char trash;

    while (user_score_1 < 21 && user_score_2 < 21) {
        do {
            printf("\e[H\e[2J\e[3J");  // \e[H\e[2J\e[3J
            draw_field(y_racket_1, y_racket_2, x_ball, y_ball, user_score_1, user_score_2);
            scanf("%1c", &button);
            if (getchar() != '\n') {
                do {
                    trash = getchar();
                } while (trash != '\n');
                continue;
            }
            switch (button) {
                case 'a':
                    button = 'A';
                    break;
                case 'z':
                    button = 'Z';
                    break;
                case 'k':
                    button = 'K';
                    break;
                case 'm':
                    button = 'M';
                    break;
                case 'q':
                    button = 'Q';
            }
            if (button == 'A' && y_racket_1 > 0)
                y_racket_1--;
            else if (button == 'Z' && y_racket_1 < 23)
                y_racket_1++;
            else if (button == 'K' && y_racket_2 > 0)
                y_racket_2--;
            else if (button == 'M' && y_racket_2 < 23)
                y_racket_2++;
        } while (button != 'A' && button != 'Z' && button != 'K' && button != 'M' && button != ' ' &&
                 button != 'Q');
        if (button == 'Q') break;

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
    if (button == 'Q') {
        printf("\e[H\e[2J\e[3J");  // \033[0;0f\033[2J
        quit_draw_field();

    } else {
        printf("\e[H\e[2J\e[3J");  // \033[0;0f\033[2J
        win_draw_field(winner);
    }
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
                printf("%d", user_score_1);
                if (user_score_1 > 9) j++;
            } else if (i == -2 && j == 45) {
                printf("%d", user_score_2);
                if (user_score_2 > 9) j++;
            } else if (i == -1 || i == 26 || j == -1 || j == 81)
                printf("*");
            else if (j == 0 && i >= y_racket_1 && i < (y_racket_1 + 3))
                printf("|");
            else if (j == 80 && i >= y_racket_2 && i < (y_racket_2 + 3))
                printf("|");
            else if (i == y_ball && j == x_ball)
                printf("0");
            else if (j == 40 && i > 2 && i < 23)
                printf("|");
            else
                printf(" ");
        printf("\n");
    }
}

void win_draw_field(int winner) {
    for (int i = -2; i <= 26; i++) {
        for (int j = -1; j <= 81; j++)
            if (i == -1 || i == 26 || j == -1 || j == 81)
                printf("*");
            else if (i == 13 && j == 34) {
                printf("PLAYER %d WIN!", winner);
                j = j + 12;
            } else
                printf(" ");
        printf("\n");
    }
}

void quit_draw_field() {
    for (int i = -2; i <= 26; i++) {
        for (int j = -1; j <= 81; j++)
            if (i == -1 || i == 26 || j == -1 || j == 81)
                printf("*");
            else if (i == 13 && j == 34) {
                printf("GOOD BYE!");
                j = j + 8;
            } else
                printf(" ");
        printf("\n");
    }
}
