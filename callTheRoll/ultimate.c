#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define STRLEN 20


typedef char (*P)[20];             //设置存储的每个成员的大小
int PAX = 0;                       // 统计人的数量 people acount x

/*  打开文件  */
FILE *__OPENFILE(const char *argv)
{
    FILE *fp = fopen(argv, "r");

    if (NULL == fp)
    {
        perror("error!");
        return 0;
    }

    return fp;
}


/*  将从.txt文件读取的数据写入到堆区中  */
P __STORAGE(FILE *fp)
{
    bool fix = true;
    int i = 0, j = 0;
    P names = (P)calloc(100, 20);

    while (fix)
    {
        for (i = 0; i < 100; i++)
        {
            if ((NULL != fgets(names[i], STRLEN, fp)) && ++j)
            {
                *(names[i] + strlen(names[i]) - 2) = '\0';
            }
            else
            {
                fix = false;
                PAX = j;
                break;
            }
        }
        // printf("i = %d\n", i);
    }
    // printf(" i = %d j = %d PAX = %d \n", i, j, PAX);
    return names;
}

/*  输出堆区内的人员信息  */
void __test(const P names)
{

    for (int initial = 0; initial < PAX ; initial++)
    {
        printf("%d ", initial);
        printf("%s", names[initial]);
    }
    return;
}

/*   随机点名  */
void __RAND_NAME(const P names){

    int i, j;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 40; i++)
    {

        usleep(10000 * (i + 1));
        j = 1 + (int)((float)(PAX - 1) * rand() / (RAND_MAX + 1.0));
        // printf("\r%d %s      ",j, names[j]);
        printf("\r %s      ", names[j]);
        fflush(stdout);
    }
    printf("\n");
    return;
}

int main(int argc, char const *argv[])
{
    
    FILE *fp = __OPENFILE(argv[1]);
    P names = __STORAGE(fp);
    __RAND_NAME(names);



    memset(names, 0, STRLEN * 100);   //将堆区数据清空
    //释放堆空间
    if (NULL != names)
    {
        free(names);
        names = NULL;
    }
    fclose(fp);
    return 0;
}
