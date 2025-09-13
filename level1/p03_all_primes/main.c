//需要用宏来支持跨平台毫秒时间查询。这里懒了；因为时间复杂度很低O（n）,CPU快了就是0
#include <stdio.h>
#include <time.h>
#define MAXN 10000005
static int prime[MAXN],not_prime[MAXN],total;
void oula_sifter(){
    for(int i=2;i<MAXN;i++){
        if(!not_prime[i]) {
            prime[++total]=i;
        };
        for(int j=1;j<=total && i*prime[j]<MAXN;j++){
            not_prime[i*prime[j]]=1;
            if(!(i%prime[j])) {
                break;//欧拉筛法最关键的一步：保证是最小的质数筛掉这个合数
            }
        }
    }
}
int main() {
    int start_time_int=0,start_time_end=0,n;
    time_t start_time,end_time;
    start_time_int=time(&start_time);
    oula_sifter();
    for(int i=2;i<=1000;i++){
        if(!not_prime[i])printf("%d ",i);
    }
    start_time_end=time(&end_time);
    printf("\ntotal time:%d\n",start_time_end-start_time_int);
    return 0;
}
