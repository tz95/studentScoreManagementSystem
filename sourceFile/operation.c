#include <stdio.h>
#include "../include/student.h"
#include "../include/operation.h"

void addStu(){
    stuNode *node = newStuNode();
    if(node == NULL)
        printf("没有足够的内存空间,请稍后重试\n");
    else{
        student *stu = node->data;
        stu->id = idNum++;
        printf("请输入学生姓名:");
        scanf("%s",stu->name);
        printf("请输入学生语文成绩:");
        scanf("%d",&stu->chineseScore);
        printf("请输入学生数学成绩:");
        scanf("%d",&stu->mathScore);
        printf("请输入学生英语成绩:");
        scanf("%d",&stu->englishScore);
        while(getchar()!='\n');
        printf("新增成功\n\n");
    }
}

void delectStu(){
    int id;
    printf("请输入要删除学生的ID:");
    scanf("%d",&id);
    delectStuNode(id);
    while (getchar()!='\n');
}

void showStu(){
    printf("| 编号 | 姓 名 | 语文 | 数学 | 英语 | 总分 |\n");

    for (stuNode *i = head->next; i != head; i=i->next)
    {
        student *stu = i->data; // 获取学生结构体指针
        printf("| %4d | %.*s | %4d | %4d | %4d | %4d |\n", stu->id, 10, stu->name, stu->chineseScore, stu->mathScore, stu->englishScore, stu->chineseScore + stu->mathScore + stu->englishScore);
    }
    printf("\n\n");
}