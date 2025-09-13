//对称密码,强度弱爆了，update:支持所有格式
#include <stdio.h>
#include<string.h>
#define MAX_LEN 114514
#define MAX_ACSII 256
#define MAX_UTF8 3
#define MOD 10
const char encrypt_char[MOD]={'!','@','#','$','%','^','&','*','(',')'};
void encrypt(const char source[],char * destination){
    int len=strlen(source);
    for(int i=0;i<len;i++){
        int tmp=source[i]+MAX_ACSII;
        for(int j=0;j<MAX_UTF8;j++){

            *destination=encrypt_char[tmp%MOD];
            destination++;
            tmp/=MOD;
        }
    }
}

void decry_single(const char source[], int i, int *tmp_char,int seek) {
    for(int k=0;k<MOD;k++){
        //正向编码，反向解码
        if(encrypt_char[k]==source[i+seek]){
            *tmp_char+=k;
            break;
        }
    }
}

void deccrypt(const char source[],char * destination){
    int len=strlen(source);
    for(int i=0;i<len;i+=3){
        int tmp_char=0;
        for (int seek=MAX_UTF8-1;seek>=0;seek--) {
            decry_single(source, i, &tmp_char,seek);
            if (tmp_char) {
                tmp_char*=10;//挪至高位
            }
        }
        tmp_char-=MAX_ACSII;
        (*destination)=(char)tmp_char;
        destination++;
    }
}
int main() {
    char string_start[MAX_LEN],string_end[MAX_LEN];
    int opt;
    printf("1.加密 2.解密\n");
    scanf("%d",&opt);
    scanf("%s",string_start);
    if(opt&1){
        encrypt(string_start,string_end);
    }
    else{
        deccrypt(string_start,string_end);
    }
    puts(string_end);
    return 0;
}
