#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_ROW 10
#define MAX_COL 10
#define MAX_QUEUE 1000000
#define RATE 2
#define MAX_DIRECTION 4
#define OBSTACLE '#'
#define EMPTY_POS ' '
#define MY_CHARACTER '*'
#define LEFT 4
#define RIGHT 3
#define UP 2
#define DOWN 1

typedef struct Node {
  int x,y;
}Node;

void set_input_mode() {
    struct termios tattr;


    tcgetattr(STDIN_FILENO, &tattr);  // 获取当前终端属性


    tattr.c_lflag &= ~(ICANON | ECHO);  // 关闭缓冲和回显


    tcsetattr(STDIN_FILENO, TCSANOW, &tattr);  // 设置新的终端属性
}

int is_outlet(Node pos_now) {
    return (pos_now.x==MAX_ROW && pos_now.y==MAX_COL);
}

static char map[MAX_COL+1][MAX_ROW+1];
static Node queue[MAX_QUEUE];
static int queue_head=1,queue_tail=1;
static int visited[MAX_COL+1][MAX_ROW+1];
static int step_x[MAX_DIRECTION+1]={0,1,-1,0, 0};
static int step_y[MAX_DIRECTION+1]={0,0, 0,1,-1};
int is_obstacle() {
    return !(rand()%RATE);
}
int is_inmap(int x,int y) {
    return ((x>0) && (x<=MAX_ROW) && (y>0) && (y<=MAX_COL));
}
void make_map() {
    for (int i = 1; i <= MAX_ROW; i++) {
        for (int j = 1; j <= MAX_COL; j++) {
            if(is_obstacle()) {
                map[i][j] = OBSTACLE;
            }
            else {
                map[i][j] = EMPTY_POS;
            }
        }
    }
    map[1][1]=' ';//单独处理起点
}

int is_access(int x,int y) {
    return map[x][y] == ' ';
}

//c没有bool！！！
int bfs_checker_valid() {
    memset(visited,0,sizeof(visited));
    memset(queue,0,sizeof(queue));
    Node now;
    now.x=1,now.y=1;
    queue[queue_tail++]=now;
    visited[now.x][now.y]=1;
    while (queue_head != queue_tail) {
        now=queue[queue_head++];
        if (is_outlet(now)) {
            return 1;
        }
        for (int i=1;i<=MAX_DIRECTION;i++) {
            int tmp_x=now.x+step_x[i],tmp_y=now.y+step_y[i];
            if (is_inmap(tmp_x,tmp_y)
                && !visited[tmp_x][tmp_y]
                && is_access(now.x + step_x[i], now.y + step_y[i])) {
                queue[queue_tail++]=(Node){tmp_x,tmp_y};
                visited[tmp_x][tmp_y]=1;
            }
        }
    }
    return 0;
}
void put_now_map(Node pos) {
    for (int i=1;i<+MAX_COL;i++) {
        putchar('_');
    }//围墙
    puts("");
    for (int i = 1; i <= MAX_ROW; i++) {
        for (int j = 1; j <= MAX_COL; j++) {
            if (pos.x==i && pos.y==j) {
                putchar(MY_CHARACTER);
            }
            else {
                putchar(map[i][j]);
            }
        }
        puts("|");//围墙
    }
}
void input_direction(int *direct) {
    *direct=getchar();
    if (*direct=='w') {
        *direct=UP;
    }
    else if (*direct=='s') {
        *direct=DOWN;
    }
    else if (*direct=='a') {
        *direct=LEFT;
    }
    else if (*direct=='d') {
        *direct=RIGHT;
    }
}
int main() {
    srand(time(NULL));
    set_input_mode();
    do {
        make_map();
    }while (!bfs_checker_valid());
    Node position;
    position.x=1,position.y=1;
    int direction;
    while (!is_outlet(position)) {
        system("clear");
        put_now_map(position);
        input_direction(&direction);
        int tmp_x=position.x+step_x[direction],tmp_y=position.y+step_y[direction];
        if (is_inmap(tmp_x,tmp_y)
            && is_access(tmp_x,tmp_y)) {
            position.x=tmp_x;
            position.y=tmp_y;
        }

    }
    put_now_map(position);
    puts("YOU WIN!");
    return 0;
}