// 基于ANSI转义来实现跨平台兼容,仅在linux下测试过
#include <stdio.h>
#include <unistd.h>

#define LEFT 1
#define RIGHT (-1)
#define WORD_LEFT "(д) ﾟﾟ"
#define WORD_RIGHT " ﾟﾟ(д)"
#define WORD_LENGTH 6
#define SLEEP_TIME 100000

struct row_and_col {
    int r, c;
} size;

int direction = LEFT, count;

void clean_console(void) {
    printf("\033[2J");
    fflush(stdout);
}

struct row_and_col GetTerminalSize() {
    char buf[32];
    struct row_and_col tmp;
    clean_console();
    sleep(1);
    printf("\n按下Enter开始：");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "\033[8;%d;%dt", &tmp.r, &tmp.c);
    clean_console();
    return tmp;
    // 解析响应：\033[8;{rows};{cols}t
}

void reverse_direction(void) {
    direction = -direction;
}

void put_front_char(int pos) {
    puts("");
    for (int j = 1; j < pos; j++)
        putchar(' ');
}

void clean_all_row(void) {
    for (int i = 1; i <= size.r; i++)
        puts("");
}

int main() {
    size = GetTerminalSize();
    int i = 1;
    while (1) {
        for (; i <= size.c - WORD_LENGTH && i > 0; i += direction) {
            put_front_char(i);
            fflush(stdout);

            if (direction > 0) {
                printf(WORD_LEFT);
            } else
                printf(WORD_RIGHT);
            fflush(stdout);
            usleep(SLEEP_TIME);
            clean_console();
        }
        reverse_direction();
        if (i > size.c - WORD_LENGTH) {
            i--;
        } else {
            i++;
        }
        //对越界迭代器进行归位
    }
    return 0;
}
