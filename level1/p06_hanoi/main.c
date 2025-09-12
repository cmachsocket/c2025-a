#include <endian.h>
#include <stdio.h>
#define MAX_PILLAR 3
#define MAX_STEP 10000000
static int pillar[MAX_PILLAR+1]={0};
static int step_x[MAX_STEP],step_y[MAX_STEP],total_step;
void record_add(int x,int y) {
    pillar[x]--,pillar[y]++;
    step_x[++total_step]=x;
    step_y[total_step]=y;
}
void dfs(int sum,int chief,int middle,int final) {
    if (sum==1) {
        record_add(chief,final);
        return;
    }
    dfs(sum-1,chief,final,middle);
    record_add(chief,final);
    dfs(sum-1,middle,chief,final);
}
int main() {
    int n;
    scanf("%d",&n);
    const int start =1;
    pillar[start]=n;
    dfs(n,1,2,3);
    for (int i=1;i<=total_step;i++) {
        printf("%d -> %d\n",step_x[i],step_y[i]);
    }
    return 0;
}

//你怎么知道我基础算法学的最烂的就是分治

/* 我们可以考虑：将A柱最大的一个搬到C柱上面去，最大的并不影响操作，实际上柱子底部自身能够看成无穷大的盘子（符合地板的定义了属于是）
 *这有两个要求：A只有最大柱，C是空柱，那么剩下（n-1）的个柱子必须在B柱。
 *将最大盘移动到C柱后，这时候的A柱与之前的B柱等价。
 *这就完成了分治的边界条件。
 *实际迭代中，我们可以借助C柱来完成完整的操作，毕竟你得让（n-1）个柱子到B柱去，总不能只有一根柱子吧。边界条件限定了至少要两根柱子才能完成边界操作。
 */