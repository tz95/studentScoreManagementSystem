#define STUNODESIZE sizeof(stuNode)
#define STUSIZE sizeof(student)
#define STUNODETOTAL(str) str->data->chineseScore + str->data->mathScore + str->data->englishScore

typedef struct student
{
    int id;
    char name[14];
    int chineseScore;
    int mathScore;
    int englishScore;
    int totalScore;
}student;

typedef struct stuNode
{
    student *data;
    struct stuNode *prev;
    struct stuNode *next;
}stuNode;

stuNode *newHeadNode(void);
void delectStuNode(int id);
stuNode *searchById(int);
stuNode *searchByName(char *name,void (*f)(stuNode *));
void changeStudent(stuNode *node,char *name,int ch,int math,int en);
void clearNode(stuNode *);
void clearHeadAllNode(void);
stuNode *sortMerge(stuNode *node,int condi);
void EOFclose();

extern stuNode* head;
extern int idNum;
extern int stuTotalNum;