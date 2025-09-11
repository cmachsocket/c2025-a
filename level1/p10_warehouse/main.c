#include <stdio.h>
#include<string.h>
#define MAX_NAME_LEN 1000
#define MAX_GOODS_SUM 10000
#define INPUT_MODE 1
#define OUTPUT_MODE 2
#define CANNOT_MATCH (-1)

typedef struct {
    char name[MAX_NAME_LEN];
    int sum;
} Pair;

static Pair goods[MAX_GOODS_SUM];
static int total_goods = 0;

void put_all_goods() {
    for (int i = 1; i <= total_goods; i++) {
        printf("%d:%s %d\n", i, goods[i].name, goods[i].sum);
    }
}

void exit_app() {
    FILE * file=fopen("warehouse.txt","w");
    for (int i = 1; i <=total_goods; i++) {
        fprintf(file, "%s %d\n", goods[i].name, goods[i].sum);
    }
    fclose(file);
}
int compare_goods(const char * name) {
    for (int i=1;i<=total_goods;i++) {
        if (!strcmp(name, goods[i].name)) {
            return i;
        }
    }
    return CANNOT_MATCH;
}
void creat_new_goods(char * input_name, int input_sum) {
    strcpy(goods[++total_goods].name, input_name);
    goods[total_goods].sum=input_sum;
}
void goods_io(int mode) {
    char name[MAX_NAME_LEN];
    int sum,position;
    printf("输入货物名称，%s数量（以空格分隔）:",mode==INPUT_MODE?"入库":"出库");

    scanf("%s%d",name,&sum);
    if (sum<0) {
        puts("数量非法！");
        return ;
    }
    if ((position= compare_goods(name)) == CANNOT_MATCH) {
        if (mode==INPUT_MODE) {
            creat_new_goods(name,sum);
        }
        else {
            puts("未找到货物！");
            return;
        }
    }
    else {
        if (mode==INPUT_MODE) {
            goods[position].sum+=sum;
        }
        else {
            goods[position].sum-=sum;
            if (goods[position].sum<0) {
                goods[position].sum=0;
            }
        }
    }
}



int main() {
    FILE *file =fopen("warehouse.txt","a");;
    fclose(file);//防止文件不存在
    file =fopen("warehouse.txt", "r");
    char input_name[MAX_NAME_LEN];
    int input_sum;
    while (fscanf(file, "%s%d", input_name,&input_sum) != EOF) {
        creat_new_goods(input_name, input_sum);
    };
    fclose(file);
    while (1) {
        int option;
        put_all_goods(total_goods);
        puts("1.入库\n2.出库\n3.退出程序");
        scanf("%d", &option);
        if (option == 1) {
            goods_io(INPUT_MODE);
        } else if (option == 2) {
            goods_io(OUTPUT_MODE);
        } else if (option == 3) {
            exit_app();
            break;
        }
    }
    return 0;
}

/*
显示存货列表
    - 入库
    - 出库
    - 退出程序
 实现菜单对应功能（需记录货物的型号、数量等信息）；
 程序启动时从文件中读取当前库存数据，退出时保存库存数据；
 */
