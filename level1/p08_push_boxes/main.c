#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_ROW 10
#define MAX_COL 10
#define MAX_NAME 20
#define MAX_DIRECTION 4

#define OBSTACLE '#'
#define EMPTY_POS ' '
#define MY_CHARACTER '*'
#define BOX 'O'
#define FINAL_POS 'X'

#define LEFT 4
#define RIGHT 3
#define UP 2
#define DOWN 1

typedef struct Node {
    int x,y;
}Node;

static char map[MAX_COL+1][MAX_ROW+1];
static char map_copy[MAX_COL+1][MAX_ROW+1];
static int step_x[MAX_DIRECTION+1]={0,1,-1,0, 0};
static int step_y[MAX_DIRECTION+1]={0,0, 0,1,-1};

void set_input_mode() {
    struct termios tattr;


    tcgetattr(STDIN_FILENO, &tattr);  // 获取当前终端属性


    tattr.c_lflag &= ~(ICANON | ECHO);  // 关闭缓冲和回显


    tcsetattr(STDIN_FILENO, TCSANOW, &tattr);  // 设置新的终端属性
}

void init_map() {
    int choice;
    const int name_positon=9;
    char operation_name[MAX_NAME]="operation0";
    puts("输入数字选择关卡（1 2 3）：");
    scanf("%d",&choice);
    operation_name[name_positon]+=(choice);
    FILE * file = fopen(operation_name,"r");
    for (int i=0;i<MAX_ROW;i++) {
        fgets(map[i],MAX_COL*2,file);
        strcpy(map_copy[i],map[i]);
        //getchar();
    }
    fclose(file);
}
int all_boxes_checked() {
    int flag=1;
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            if (map_copy[i][j]==FINAL_POS && map[i][j]!=BOX) {
                map[i][j]=FINAL_POS;
            }
            if (map[i][j]==FINAL_POS) {
                flag=0;
            }
        }
    }
    return flag;
}
void put_now_map(Node pos) {
    system("clear");
    for (int i=1;i<=MAX_COL;i++) {
        putchar('_');
    }//围墙
    puts("");
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
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
    else {
        *direct=0;
    }
}
int is_inmap(int x,int y) {
    return ((x>=0) && (x<MAX_ROW) && (y>=0) && (y<MAX_COL));
}
int is_access_box(int x,int y) {
    return map[x][y] == EMPTY_POS || map[x][y] == FINAL_POS;
}
int is_access_person(int x,int y,int direct) {
    if (map[x][y] == EMPTY_POS || map[x][y] == FINAL_POS) {
        return 1;
    }
    if (map[x][y]==BOX) {
        int tmp_x=x+step_x[direct];
        int tmp_y=y+step_y[direct];
        if (is_inmap(tmp_x,tmp_y) && is_access_box(tmp_x,tmp_y)) {
            map[x][y]=EMPTY_POS;
            map[tmp_x][tmp_y]=BOX;
            return 1;
        }
    }
    return 0;
}
int main() {
    init_map();
    set_input_mode();
    Node position;
    position.x=0,position.y=0;
    int direction,steps=0;
    while (!all_boxes_checked()) {
        system("clear");
        put_now_map(position);
        input_direction(&direction);
        int tmp_x=position.x+step_x[direction],tmp_y=position.y+step_y[direction];
        if (is_inmap(tmp_x,tmp_y) && (is_access_person(tmp_x,tmp_y,direction))) {
            position.x=tmp_x;
            position.y=tmp_y;
            steps++;
        }
    }
    put_now_map(position);
    int score=(int)((1.0)/(steps)*10000);
    printf("YOU WIN!\nyour score:%d",score);
    FILE * file=fopen("game_record.txt","w");
    printf("%d\n",score);
    fclose(file);
    return 0;
}