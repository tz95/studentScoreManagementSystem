#include <stdio.h>
#include "../include/student.h"
#include "../include/operation.h"

void showStu(stuNode *);

void addStu(){
    stuNode *node = newHeadNode();
    if(node == NULL)
        printf("没有足够的内存空间,请稍后重试\n");
    else{
        student *stu = node->data;
        stu->id = idNum-1;
        printf("请输入学生姓名(限制三个汉字及以下):");
        scanf("%14s",stu->name);
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

void changeStu(){
    int id;
    printf("\n请输入要更改学生的ID:");
    scanf("%d",&id);
    stuNode *node = searchById(id);
    if (node == NULL)
    {
        printf("不存在该学生");
        return;
    }else{
        showStu(node);
        int ch,math,en;
        char name[14];
        printf("请输入姓名:");
        scanf("%14s",name);
        printf("请输入语文成绩:");
        scanf("%d",&ch);
        printf("请输入数学成绩:");
        scanf("%d",&math);
        printf("请输入英语成绩:");
        scanf("%d",&en);
        changeStudent(node,name,ch,math,en);
    }
}

void searchStu(){
    printf("\n\n请问需要通过什么查找对象\n\
            \t1.ID\n\
            \t2.姓名\n\n");
    while(getchar() != '\n');
    switch (getchar())
    {
    case '1':
        int id;
        printf("请输入需要查找学生的ID:");
        scanf("%d",&id);
        printf("\n\n");
        printf("| 编号 | 姓 名 | 语文 | 数学 | 英语 | 总分 |\n");
        showStu(searchById(id));
        printf("\n\n");
        break;

    case '2':
        char name[14];
        printf("请输入需要查找学生的姓名:");
        scanf("%14s",name);
        printf("\n\n");
        printf("| 编号 | 姓 名 | 语文 | 数学 | 英语 | 总分 |\n");
        searchByName(name,showStu);
        printf("\n\n");
        break;
    default:
        printf("无效值!\n\n");
        break;
    }
}

void loadStu(){
    if (head != NULL)
    {
        clearHeadAllNode();
    }
    
    int num;
    FILE *fp = fopen("./data/stu.data","rb");
    if(fp == NULL){
        printf("无访问权限，请检查文件状态后重试\n");
        return;
    }
    fread(&num,sizeof(num),1,fp);
    for (int i = 0; i < num; i++)
    {
        student *stu = newHeadNode()->data;
        fread(&stu->id,sizeof(stu->id),1,fp);
        fread(stu->name,sizeof(stu->name),1,fp);
        fread(&stu->chineseScore,sizeof(stu->chineseScore),1,fp);
        fread(&stu->mathScore,sizeof(stu->mathScore),1,fp);
        fread(&stu->englishScore,sizeof(stu->englishScore),1,fp);
    }
    printf("读取成功! 按Enter继续\n\n\n");
    printf("\r");
    idNum = stuTotalNum;
    fclose(fp);
    getchar();
    getchar();
}

void saveStu(){
    // 文件为当前目录data文件夹下的stu.data 可根据自己需求自定义
    FILE *fp = fopen("./data/stu.data","wb");
    if(fp == NULL){
        printf("无访问权限，请检查文件状态后重试");
        EOFclose();
    }
    fwrite(&stuTotalNum,sizeof(stuTotalNum),1,fp);
    stuNode *p = head->next;
    for (int i = 0; i < stuTotalNum; i++)
    {
        student *stu = p->data;
        fwrite(&stu->id,sizeof(stu->id),1,fp);
        fwrite(stu->name,sizeof(stu->name),1,fp);
        fwrite(&stu->chineseScore,sizeof(stu->chineseScore),1,fp);
        fwrite(&stu->mathScore,sizeof(stu->mathScore),1,fp);
        fwrite(&stu->englishScore,sizeof(stu->englishScore),1,fp);
        p = p->next;
    }
    printf("保存成功！\n");
    fclose(fp);
}

void sortStu(void){
    int n;
    char end;
    saveStu();
    printf("要根据什么排序?\n"
           "1.语文成绩\n"
           "2.数学成绩\n"
           "3.英语成绩\n"
           "4.总分\n");
    scanf("%d",&n);
    stuNode *node;
    head->prev->next = NULL;
    switch (n) {
        case 1:
            node = sortMerge(head->next,n);
            break;
        case 2:
            node = sortMerge(head->next,n);
            break;
        case 3:
            node = sortMerge(head->next,n);
            break;
        case 4:
            node = sortMerge(head->next,n);
            break;
        default:
            printf("无效值!\n\n");
            break;
    }
    showAllStu(node);
    printf("\n\n接下来将会还原学生顺序，请输入Y并回车确认(大小写皆可)");
    scanf("%c",&end);
    clearHeadAllNode();
    loadStu();
}

void showStu(stuNode *node){
    if(node == NULL){
        printf("不存在学生！\n");
        return;
    }
    student *stu = node->data;
    printf("| %4d | %.*s | %4d | %4d | %4d | %4d |\n", stu->id, 14, stu->name, stu->chineseScore, stu->mathScore, stu->englishScore, stu->chineseScore + stu->mathScore + stu->englishScore);
}

void showAllStu(stuNode *node){
    if (node == NULL)
    {
        if (head == NULL)
        {
            printf("当前没有记录学生！\n\n");
            return;
        }
        
        printf("| 编号 | 姓 名 | 语文 | 数学 | 英语 | 总分 |\n");

        for (stuNode *i = head->next; i != head && i != NULL; i=i->next)
        {
            student *stu = i->data; // 获取学生结构体指针
            printf("| %4d | %.*s | %4d | %4d | %4d | %4d |\n", stu->id, 14, stu->name, stu->chineseScore, stu->mathScore, stu->englishScore, stu->chineseScore + stu->mathScore + stu->englishScore);
        }
        printf("\n\n");
    }else{
        printf("\n");
        printf("| 编号 | 姓 名 | 语文 | 数学 | 英语 | 总分 |\n");

        for (stuNode *i = node; i != NULL; i=i->next)
        {
            student *stu = i->data; // 获取学生结构体指针
            printf("| %4d | %.*s | %4d | %4d | %4d | %4d |\n", stu->id, 14, stu->name, stu->chineseScore, stu->mathScore, stu->englishScore, stu->chineseScore + stu->mathScore + stu->englishScore);
        }
        getchar();
        getchar();
    }
}