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
    if(n&1){
        printf("Not Even!");
        return 0;
    }
    if(n==2){
        printf("Are you kidding me?");
        return 0;
    }
    for(int i=1;pr[i]<n;i++){
        for(int j=1;j<=i;j++){
            if(pr[i]+pr[j]==n){
                printf("%d+%d\n",pr[i],pr[j]);
                return 0;
            }
        }
    }
    return 0;
}
