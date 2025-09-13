#include <stdio.h>
#define MAXN 10000005
static int prime[MAXN],total,not_prime[MAXN];
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
    printf(not_prime[n]?"不是":"是");
    printf("质数\n");
    return 0;
}
