#include <stdio.h>
#define MAXN 1000005
char pt[4]={0,'A','B','C'};
int n,a[MAXN],fr[MAXN],to[MAXN],tot;
//好不容易才封装了一个栈
struct stack{
    int st[MAXN],pos;

}st[5];
int top(struct stack * s){
    return (*s).st[(*s).pos];
}
void pop(struct stack * s){
    (*s).pos--;
}
void push(struct stack * s,int x){
    (*s).st[++(*s).pos]=x;
}
int size(struct stack * s){
    return (*s).pos;
}
void dfs(){
    if(size(&st[3])==n){
        for(int i=1;i<=tot;i++){
            printf("%c -> %c\n",pt[fr[i]],pt[to[i]]);
        }
        return ;
    }
    for(int i=1;i<=tot;i++){
        printf("%c -> %c\n",pt[fr[i]],pt[to[i]]);
    }
    puts("FFF");
    for(int i=1;i<=2;i++){
        for(int j=i+1;j<=3;j++){
            if(top(&st[i])<top(&st[j])){
                ++tot;
                fr[tot]=i,to[tot]=j;
                push(&st[j],top(&st[i]));
                pop(&st[i]);
                dfs();
                push(&st[i],top(&st[j]));
                pop(&st[j]);
                tot--;
            }
        }

    }

}


int main() {
    scanf("%d",&n);
    for(int i=1;i<=3;i++)st[i].st[0]=MAXN;
    for(int i=n;i>=1;i--)push(&st[1],i);
    dfs();

    return 0;
}
