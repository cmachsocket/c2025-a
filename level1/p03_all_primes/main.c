//需要用宏来支持跨平台毫秒时间查询。这里懒了,CPU快了就是0
#include <stdio.h>
#include <time.h>
#define MAXN 10000005
int pr[MAXN],tot,nopr[MAXN],n;
void oula(){
    for(int i=2;i<=MAXN;i++){
        if(!nopr[i])pr[++tot]=i;
        for(int j=1;j<=tot && i*pr[j]<=MAXN;j++){
            nopr[i*pr[j]]=1;
            if(!(i%pr[j]))break;
        }
    }
}
int main() {
    oula();
    int set1=0,set2=0;
    time_t timep1,timep2;
    set1=time(&timep1);
    for(int i=2;i<=1000;i++){
        if(!nopr[i])printf("%d ",i);
    }
    set2=time(&timep2);
    printf("\ntotal time:%d\n",set2-set1);
    return 0;
}
