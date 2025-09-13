#include <stdio.h>
#define MAXN 10000005
int prime[MAXN],total,not_prime[MAXN];
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
    int n;
    oula_sifter();
    scanf("%d",&n);
    if(n&1){
        printf("Not Even!");
        return 0;
    }
    if(n==2){
        printf("Are you kidding me?");
        return 0;
    }
    for(int i=1;prime[i]<n;i++){
        for(int j=1;j<=i;j++){
            if(prime[i]+prime[j]==n){
                printf("%d+%d\n",prime[i],prime[j]);
                return 0;
            }
        }
    }
    return 0;
}
