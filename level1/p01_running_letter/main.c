// 基于ANSI转义来实现跨平台兼容,仅在linux下测试过
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct rc {
  int r, c;
} size;
int x = 1, count;
struct rc GetTerminalSize() {
  char buf[32], che[] = "\033[18t", c_tmp;
  struct rc tmp;
  int i = 0;
  printf("\033[18t");
  fflush(stdout);
  sleep(1);
  printf("\n按下Enter开始：");
  fgets(buf, sizeof(buf), stdin);
  sscanf(buf, "\033[8;%d;%dt", &tmp.r, &tmp.c);
  printf("\033[2J");
  return tmp;
  // 解析响应：\033[8;{rows};{cols}t
}
int main() {
  size = GetTerminalSize();
  for (int i = 1; i <= size.r; i++)
    puts("");
  int i = 1;
  while (1) {
    for (; i <= size.c - 6 && i > 0; i += x) {
      // fseek(stdout,0,SEEK_SET);
      // fseek(stdin,0,SEEK_SET);
      puts("");
      // printf("%d s\n",x);
      for (int j = 1; j < i; j++)
        putchar(' ');
      if (x > 0) {
        printf("(д) ﾟﾟ");
      } else
        printf(" ﾟﾟ(д)");
      fflush(stdout);
      usleep(100000);
      // 清除控制台屏幕
      printf("\033[2J");
      fflush(stdout);
    }
    x = -x;
    if (i > size.c - 6) {
      i--;
    }

    else {
      i++;
    }

    // puts("F");
  }

  return 0;
}
