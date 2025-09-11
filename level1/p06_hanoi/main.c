#include <stdio.h>
#define MAXN 1000005

int main() {
    scanf("%d",&n);
    for(int i=1;i<=3;i++)st[i].st[0]=MAXN;
    for(int i=n;i>=1;i--)push(&st[1],i);
    dfs();

    return 0;
}
