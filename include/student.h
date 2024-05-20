#define STUNODESIZE sizeof(stuNode)
#define STUSIZE sizeof(student)

typedef struct student
{
    int id;
    char *name;
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

stuNode *newStuNode(void);
void delectStuNode(int id);
stuNode *searchById(int);
stuNode *searchByName(char *name,void (*f)(stuNode *));
void changeStudent(stuNode *node,char *name,int ch,int math,int en);
void clearNode(void);

extern stuNode* head;
extern int idNum;
extern int stuTotalNum;