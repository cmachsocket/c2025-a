//对称密码,强度弱爆了，update:支持所有格式
#include <stdio.h>
#include<string.h>
#define MAXN 114514
char enp[10]={'!','@','#','$','%','^','&','*','(',')'};
char s1[MAXN],s2[MAXN];
int opt;
void enc(char s[],char * p){
    int len=strlen(s);
    //printf("%d\n",len);
    for(int i=0;i<len;i++){
        int tmp=s[i]+256;
        //printf("%d 1\n",tmp);

        for(int j=0;j<3;j++){

            *p=enp[tmp%10];
            p++;
            tmp/=10;
        }
    }
}
void dec(char s[],char * p){
    int len=strlen(s);
    for(int i=0;i<len;i+=3){
        int tmp=0;
        for(int k=0;k<10;k++){
            if(enp[k]==s[i+2]){
                tmp+=k;
                break;
            }
        }
        tmp*=10;
        for(int k=0;k<10;k++){
            if(enp[k]==s[i+1]){
                tmp+=k;
                break;
            }
        }
        tmp*=10;
        for(int k=0;k<10;k++){
            if(enp[k]==s[i]){
                tmp+=k;
                break;
            }
        }
        //printf("%d 2\n",tmp);
        tmp-=256;
        (*p)=tmp;
        p++;
    }
}
int main() {
    printf("1.加密 2.解密\n");
    scanf("%d",&opt);
    scanf("%s",s1);
    if(opt&1){
        enc(s1,s2);
    }
    else{
        dec(s1,s2);
    }
    puts(s2);
    return 0;
}
