#include <stdio.h>
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
    scanf("%d",&n);
    printf(nopr[n]?"不是":"是");
    printf("质数\n");
    return 0;
}
