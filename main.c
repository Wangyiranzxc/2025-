#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//比较函数
int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

//结构体定义
#define MAXSIZE 100
//结构体只是对于一个数据结构的描述，并没有实际分配空间，所以不能在结构体中直接对变量赋值
typedef struct SqList {
    int data[MAXSIZE];
    int length;
} SqList;//线性表的结构体
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;//单链表的结构体
typedef struct DNode {
    int data;
    struct DNode *prior, *next;
} DNode, *DNodeList;//双链表的结构体
typedef struct {
    int data;
    int next;
} SLinkLisk[MAXSIZE];//静态链表的结构体
typedef struct Stack {
    int data[MAXSIZE];
    int top;
} SqStack;//顺序栈的结构体
typedef struct LStack {
    struct LStack *next;
    int data;
} LiStack;//链栈的结构体
typedef struct {
    int data[MAXSIZE];
    int front, rear;
} SqQueue;//顺序队列
typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;
typedef struct {
    LinkNode *front, *rear;
} LinkQueue;//链栈的结构体
typedef struct {
    char str[MAXSIZE];
    int length;
} SString;//静态串的结构体
typedef struct {
    char *ch;
    int length;
} HString;//动态串的结构体
typedef struct BiNode {
    int data;
    struct BiNode *LeftChild, *RightChild;
} BiNode, *BiTree;//二叉树的结构体
typedef struct ThreadNode {
    int data;
    int LTag, RTag;
    struct ThreadNode *LChild, *RChild;
} ThreadNode, *ThreadTree;//线索二叉树的结构体

//线性表基本操作
void InitSqList(SqList *L) {
    L->length = 0;
}//初始化线性表，将结构体L的长度初始化为0；
bool InsertElementByIndex(SqList *L, int index, int addNumber) {
    if (index < 1 || index > L->length + 1) {
        return false;
    }
    if (L->length == MAXSIZE) {
        return false;
    }
    for (int i = L->length; i >= index; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[index - 1] = addNumber;
    L->length++;
    return true;
}//向线性表中的第index个位置插入一个值为addNumber的元素
int DeleteElementByIndex(SqList *L, int index) {
    if (index < 1 || index > L->length) {
        printf("%s\n", "索引值非法");
        return -1;
    }
    int BeDeleteNumber = 0;
    for (int i = index; i < L->length; ++i) {
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return BeDeleteNumber;
}//删去线性表的第index个元素，并将其值用BeDeleteNumber返回
int getLength(SqList L) {
    return L.length;
}//获取一个线性表的当前长度

//链表基本操作
bool InitHeadList(LinkList *L) {
    *L = (LNode *) malloc(sizeof(LNode));
    (*L)->next = NULL;
    return true;
}//初始化带头节点的链表
bool InitList(LinkList *L) {
    *L = NULL;
    return true;
}//初始化不带头节点的链表
int Length(LinkList L) {
    int length = 0;
    LNode *p = L;
    while (p->next != NULL) {
        length++;
        p = p->next;
    }
    return length;
}//计算链表表长
LNode *findByIndex(LinkList L, int index) {
    int count = 0;
    LNode *p = L;
    while (p->next != NULL && count < index) {
        count++;
        p = p->next;
    }
    return p;
}//返回第i个节点的指针
LNode *findByValue(LinkList L, int value) {
    LNode *p = L;
    while (p != NULL) {
        if (p->data == value) {
            return p;
        } else
            p = p->next;
    }
    return NULL;
}//根据链节点的值进行查找，返回指向第一个值为所要的节点的指针
bool InsertElementToList(LinkList *L, int index, int addNumber) {
    LNode *p = *L;
    int count = 0;
    while (p != NULL && count < index - 1) {
        p = p->next;
        count++;
    }
    if (p == NULL) {
        return false;
    }
    LNode *add = (LNode *) malloc(sizeof(LNode));
    add->next = p->next;
    p->next = add;
    add->data = addNumber;
    return true;
}//插入一个节点
void printList(LinkList L) {
    LNode *p = L;
    while (p->next != NULL) {
        printf("%d ", p->next->data);
        p = p->next;
    }
}//打印链表
bool DeleteElementFromList(LinkList *L, int index, int *returnNumber) {
    LNode *p = *L;
    int count = 0;
    while (p != NULL && count < index - 1) {
        count++;
        p = p->next;
    }
    if (p == NULL || p->next == NULL) {
        return false;
    } else {
        LNode *q = p->next;
        *returnNumber = q->data;
        p->next = q->next;
        free(q);
        return true;
    }
}//从链表中删除节点
LinkList HeadInsert(LinkList *L) {
    *L = (LNode *) malloc(sizeof(LNode));
    (*L)->next = NULL;
    LNode *p;
    int x = 0;
    scanf("%d", &x);
    while (x != 9999) {
        p = (LNode *) malloc(sizeof(LNode));
        p->data = x;
        p->next = (*L)->next;
        (*L)->next = p;
        scanf("%d", &x);
    }
    return *L;
}//头插法建立链表
LinkList RearInsert(LinkList *L) {
    int x = 0;
    *L = (LNode *) malloc(sizeof(LNode));
    LNode *rear = *L, *p;
    scanf("%d", &x);
    while (x != 9999) {
        p = (LNode *) malloc(sizeof(LNode));
        p->data = x;
        rear->next = p;
        rear = p;
        scanf("%d", &x);
    }
    rear->next = NULL;
    return *L;
}//尾插法建立链表

//线性表
// TODO 王道书P19应用题01
int DeleteMinElement(SqList *L) {
    if (L->length == 0) {
        printf("%s\n", "链表为空");
        return -1;
    }
    int min = L->data[0];
    int index = 0;
    for (int i = 0; i < L->length; ++i) {
        if (L->data[i] < min) {
            min = L->data[i];
            index = i;
        }
    }
    L->data[index] = L->data[L->length - 1];
    L->length--;
    return min;
}//删除线性表中值最小的元素（假设唯一），并用函数返回被删元素的值，空出的位置由最后一个元素填充，若顺序表为空，则显示出错信息，并退出运行
// TODO 王道书P19应用题02
void reverse(SqList *L) {
    if (L->length == 0) {
        return;
    }
    int left = 0;
    int right = L->length - 1;
    while (left < right) {
        int temp = 0;
        temp = L->data[left];
        L->data[left++] = L->data[right];
        L->data[right--] = temp;
    }
}//逆转顺序表，算法空间复杂度为O(1);
// TODO 王道书P19应用题03
void DeleteAllElementByValue(SqList *L, int value) {
    if (L->length == 0) {
        return;
    }
    int count = 0;
    for (int i = 0; i < L->length; ++i) {
        if (L->data[i] == value) {
            count++;
            continue;
        }
        L->data[i - count] = L->data[i];
    }
    L->length = L->length - count;
}//删除顺序表中所有值为value的元素
// TODO 王道书P19应用题04
void DeleteElementBetweenST(SqList *L, int s, int t) {
    if (s >= t) {
        printf("S值比T大");
        return;
    } else if (L->length == 0) {
        printf("顺序表为空");
        return;
    }
    int count = 0;
    for (int i = 0; i < L->length; ++i) {
        if (L->data[i] > s && L->data[i] < t) {
            count++;
            continue;
        }
        L->data[i - count] = L->data[i];
    }
    L->length = L->length - count;

}//删除顺序表中值处于s和t之间的元素，如若s>t或顺序表为空则显示错误信息并退出
// TODO 王道书P19应用题05
void DeleteElementForSole(SqList *L) {
    if (L->length == 0)
        return;
    int i = 0, j = 1;
    for (; j < L->length; ++j) {
        if (L->data[i] != L->data[j]) {
            L->data[++i] = L->data[j];
        }
    }
    L->length = i + 1;
}//去除顺序表中重复的元素，使表中所有元素的值均不同
// TODO 王道书P19应用题06
SqList mergeTwoSqList(SqList *L1, SqList *L2) {
    SqList L;
    InitSqList(&L);
    int i = 0, j = 0;
    while (i < L1->length && j < L2->length) {
        if (L1->data[i] <= L2->data[j]) {
            InsertElementByIndex(&L, L.length + 1, L1->data[i++]);
        } else {
            InsertElementByIndex(&L, L.length + 1, L2->data[j++]);
        }
    }
    while (i < L1->length) {
        InsertElementByIndex(&L, L.length + 1, L1->data[i++]);
    }
    while (j < L2->length) {
        InsertElementByIndex(&L, L.length + 1, L2->data[j++]);
    }
    return L;
}//合并两个有序顺序表（默认升序），并用函数返回合并后的顺序表
// TODO 王道书P19应用题07
void swapAddr(int arr[], int arrLength, int m, int n) {

}

// TODO 王道书P19应用题08
void findElementByValue(SqList *L, int x) {
    if (L->length == 0) {
        L->data[0] = x;
        L->length++;
        return;
    }
    int left = 0;
    int right = L->length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (L->data[mid] == x) {
            int temp = L->data[mid];
            L->data[mid] = L->data[mid + 1];
            L->data[mid + 1] = temp;
            return;
        } else if (L->data[mid] < x) {
            left = mid + 1;
        } else if (L->data[mid] > x) {
            right = mid - 1;
        }
    }
    printf("%d\n", left);
    for (int i = L->length; i > left; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[left] = x;
    L->length++;
}//给定一个有序线性表，使用最少时间查找数值为X的元素，如果没查到，就将其插入表中，并使表中元素仍递增有序
// TODO 王道书P19应用题09
void findCommonElement(SqList La, SqList Lb, SqList Lc, int n) {
    int a = 0, b = 0, c = 0;
    while (a < n && b < n && c < n) {
        if (La.data[a] == Lb.data[b] && Lb.data[b] == Lc.data[c]) {
            printf("%d", La.data[a]);
            a++, b++, c++;
        } else {
            int Max = fmax(La.data[a], fmax(Lb.data[b], Lc.data[c]));
            if (La.data[a] < Max)a++;
            if (Lb.data[b] < Max)b++;
            if (Lc.data[c] < Max)c++;
        }
    }
}//设计一个算法寻找三个给定有序序列所共有的元素
// TODO 王道书P19应用题10
//左移数组，三次逆置
// TODO 王道书P19应用题11
int findMid(SqList L1, SqList L2, int length) {
    int left1 = 0;
    int left2 = 0;
    int count = 0;
    for (int i = 0; i < length - 1; ++i) {
        if (L1.data[left1] < L2.data[left2]) {
            left1++;
        } else
            left2++;
    }
    return L1.data[left1] > L2.data[left2] ? L2.data[left2] : L1.data[left1];
}//寻找两个有序序列的中位数
// TODO 王道书P19应用题12
int findMain(SqList L1) {
    //先给data数组排好序
    //如果数组长度为奇数，主元素如果存在必定是中间的元素，在遍历计数确认是否真是主元素
    //如果数组长度为偶数，主元素如果存在那么中间两个元素必定同值，在遍历计数确认是否真是主元素
}//在一个序列中存在超过半数的相同元素称为主元素，求一个序列中是否有主元素
// TODO 王道书P19应用题13
int findMinNumber(int A[], int length) {
    int *B = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        if (A[i] >= 1 && A[i] < +length - 1)
            B[A[i] - 1] = 1;
    }
    int result = 0;
    for (int i = 0; i < length; ++i) {
        if (B[i] == 0) {
            result = i + 1;
            break;
        }
    }
    free(B);
    return result;
}
// TODO 王道书P19应用题14


//链表
// TODO 王道书P43应用题01
void DeleteElementX(LinkList *L, int x) {
    LNode *p = *L;
    while (p->next != NULL) {
        if (p->next->data == x) {
            LNode *q = p->next;
            p->next = q->next;
            free(q);
        } else
            p = p->next;
    }
}//删除链表中所有值为x的节点
// TODO 王道书P43应用题02
void DeleteElementMin(LinkList *L, int *returnNumber) {
    LNode *p = *L;
    if (p->next == NULL) {
        return;
    }
    LNode *q = p;
    int min = p->next->data;
    while (p->next != NULL) {
        if (p->next->data < min) {
            q = p;
            min = q->next->data;
        }
        p = p->next;
    }
    *returnNumber = min;
    q->next = q->next->next;
}//删除链表中最小值节点
// TODO 王道书P43应用题03
void reverseLinklist(LinkList *L) {
    if ((*L)->next == NULL) {
        return;
    }
    LNode *p = (*L)->next;
    (*L)->next = NULL;
    while (p != NULL) {
        LNode *q = p;
        p = p->next;
        q->next = (*L)->next;
        (*L)->next = q;
    }
}//翻转链表，空间复杂度为O(1)
// TODO 王道书P43应用题04
void DeleteElementBetweenSANDT(LinkList *L, int s, int t) {
    if (s > t) {
        return;
    }
    LNode *p = *L;
    while (p->next != NULL) {
        if (p->next->data >= s && p->next->data <= t) {
            LNode *q = p->next;
            p->next = q->next;
            free(q);
        } else
            p = p->next;
    }
}//删除值在st之间的节点
// TODO 王道书P43应用题05
LNode *findCommonNode(LinkList *L1, LinkList *L2) {
    LNode *p1 = *L1;
    LNode *p2 = *L2;
    while (p2->next != NULL && p1->next != NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    int Len = 0;
    int flag = 0;
    while (p1->next != NULL) {
        flag = 1;
        Len++;
        p1 = p1->next;
    }
    while (p2->next != NULL) {
        flag = 2;
        Len++;
        p2 = p2->next;
    }
    LNode *p = *L1;
    LNode *q = *L2;
    if (flag == 1) {
        for (int i = 0; i < Len; ++i) {
            p = p->next;
        }
    } else {
        for (int i = 0; i < Len; ++i) {
            q = q->next;
        }
    }
    while (p != NULL && q != NULL) {
        if (p == q) {
            return p;
        } else {
            p = p->next;
            q = q->next;
        }
    }
    return NULL;
}//如何找到两个单链表的公共节点
// TODO 王道书P43应用题06
void splitList(LinkList *A, LinkList *B) {
    *B = (LinkList) malloc(sizeof(LNode));
    LNode *p = (*A)->next;
    (*B)->next = NULL;//头插链表
    (*A)->next = NULL;//尾插链表
    int flag = 1;
    LNode *rearA = *A;
    while (p != NULL) {
        LNode *q = p->next;
        if (flag % 2 == 1) {
            //A链表尾插
            rearA->next = p;
            rearA = p;
            rearA->next = NULL;
        } else {
            //B链表头插
            p->next = (*B)->next;
            (*B)->next = p;
        }
        p = q;
        flag++;
    }
}//拆分链表
// TODO 王道书P43应用题07
void DeleteElementWithSameValue(LinkList *L) {
    LNode *p = *L;
    while (p->next != NULL && p->next->next != NULL) {
        if (p->next->data == p->next->next->data) {
            LNode *q = p->next;
            p->next = q->next;
            free(q);
        } else
            p = p->next;
    }
}//删除具有相同值的节点
// TODO 王道书P43应用题08
void MergeCommonNodeTOCLink(LinkList A, LinkList B, LinkList *C) {
    LNode *a = A;
    LNode *b = B;
    *C = (LinkList) malloc(sizeof(LNode));
    LNode *rearC = (*C);
    while (a->next != NULL && b->next != NULL) {
        if (a->data == b->data) {
            LNode *p = (LNode *) malloc(sizeof(LNode));
            p->data = a->data;
            rearC->next = p;
            rearC = p;
            a = a->next;
            b = b->next;
        } else if (a->data > b->data) {
            b = b->next;
        } else if (a->data < b->data) {
            a = a->next;
        }
    }
    rearC->next = NULL;
}//新建链表C包含两个有序链表中相同值节点
// TODO 王道书P43应用题09
void MergeSetAB(LinkList *A, LinkList B) {
    LNode *a = (*A)->next;
    LNode *b = B->next;
    (*A)->next = NULL;
    LNode *rear = (*A);
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            LNode *p = (LNode *) malloc(sizeof(LNode));
            p->data = a->data;
            rear->next = p;
            rear = p;
            a = a->next;
            b = b->next;
        } else if (a->data > b->data) {
            b = b->next;
        } else if (a->data < b->data) {
            a = a->next;
        }
    }
    rear->next = NULL;
}//合并集合AB中相同节点
// TODO 王道书P43应用题10
bool IsBSubsequenceOfA(LinkList A, LinkList B) {
    LNode *a = A->next;
    LNode *b = B->next;
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            a = a->next;
            b = b->next;
        } else {
            a = a->next;
            b = B->next;
        }
    }
    if (b == NULL) {
        return true;
    } else
        return false;
}//判断B是否是A的子序列
// TODO 王道书P43应用题11
bool IsDLinkListSymmetry(DNodeList A) {
    if (A == NULL) {
        return true;
    }
    DNode *pre = A->next;
    DNode *rear = pre->prior;
    while (pre != rear && pre->next != rear) {
        if (pre->data == rear->data) {
            pre = pre->next;
            rear = rear->prior;
        } else
            return false;
    }
    return true;
}//双向链表是否对称
// TODO 王道书P43应用题12
void MergeTwoList(LinkList *h1, LinkList h2) {
    if (*h1 == NULL || h2 == NULL) {
        return;
    }
    LNode *p = *h1;
    while (p->next != *h1) {
        p = p->next;
    }
    p->next = h2;
    p = h2;
    while (p->next != h2) {
        p = p->next;
    }
    p->next = *h1;
}//将循环单链表h1和h2链接起来
// TODO 王道书P43应用题13
typedef struct freqNode {
    struct freqNode *next, *pre;
    int data;
    int freq;
} freqNode, *freqLinkList;

freqNode *Locate(freqLinkList *L, int x) {
    freqNode *p = (*L)->next;
    while (p != NULL && p->data != x) {
        p = p->next;
    }
    if (p == NULL) {
        return NULL;
    }
    p->freq++;
    freqNode *q = p->pre;
    p->pre->next = p->next;
    p->next->pre = p->pre;
    while (p->freq >= q->freq) {
        q = q->pre;
    }
    p->next = q->next;
    p->pre = q;
    q->next = p;
    p->next->pre = p;
    return p;


}//返回查找值为x节点的地址
// TODO 王道书P44应用题14
void rightMoveLinkList(LinkList *L, int k) {
    LNode *p = *L;
    int Len = 0;
    while (p != NULL) {
        Len++;
        p = p->next;
    }
    k = k % Len;
    if (k == 0) {
        return;
    }
    p = *L;
    for (int i = 0; i < Len - k - 1; ++i) {
        p = p->next;
    }
    LNode *newHead = p->next;
    p->next = NULL;

    LNode *q = newHead;
    while (q->next != NULL) {
        q = q->next;
    }

    q->next = *L;
    *L = newHead;
}//链表右移K次
// TODO 王道书P44应用题15
bool loopInLinkList(LinkList L) {
    LNode *quick = L;
    LNode *slow = L;
    while (quick != NULL && quick->next != NULL) {
        quick = quick->next->next;
        slow = slow->next;
        if (quick == slow) {
            return true;
        }
    }
    return false;
}//判断单链表中是否有环
// TODO 王道书P44应用题16
int maxPlus(LinkList L, int n) {

}//最大孪生和
// TODO 王道书P44应用题17
int lastKNode(LinkList L, int k) {
    if (k < 0 || L == NULL) {
        return 0;
    }
    LNode *p = L;
    for (int i = 0; i < k; ++i) {
        p = p->next;
        if (p == NULL)
            return 0;
    }
    LNode *pre = L;
    while (p != NULL) {
        p = p->next;
        pre = pre->next;
    }
    printf("%d", pre->data);
    return 1;
}//输出倒数第k个节点的值
// TODO 王道书P44应用题18
//单词最长后缀，KMP算法
// TODO 王道书P44应用题19
void deleteSameABSVal(LinkList *L, int n) {
    int *arr = (int *) malloc(n * sizeof(int));
    LNode *p = *L;
    while (p->next != NULL) {
        if (arr[p->next->data] != 0) {
            p->next = p->next->next;
        } else {
            arr[p->next->data] = 1;
            p = p->next;
        }
    }
    free(arr);
}//去除链表中相同绝对值的元素
// TODO 王道书P44应用题20
//有点难☹️

//栈操作
void InitStack(SqStack *S) {
    S->top = -1;
}//初始化顺序栈
bool StackIsEmpty(SqStack S) {
    if (S.top == -1) {
        return true;
    } else
        return false;
}//判断栈是否为空
bool Push(SqStack *S, int add) {
    if (S->top == MAXSIZE - 1) {
        return false;
    } else {
        S->data[++S->top] = add;
        return true;
    }
}//压栈
bool Pop(SqStack *S, int *pop) {
    if (S->top == -1) {
        return false;
    } else {
        *pop = S->data[S->top--];
        return true;
    }
}//出栈
bool Peek(SqStack S, int *peek) {
    if (S.top == -1) {
        return false;
    } else {
        *peek = S.data[S.top];
        return true;
    }
}//查看栈顶元素

//栈应用
// TODO 王道书P70应用题03
bool operaTF(char arr[], int len) {
    int I = 0;
    int O = 0;
    for (int i = 0; i < len; ++i) {
        if (arr[i] == 'T') {
            I++;
        } else
            O++;

        if (I < O) {
            return false;
        }
    }
    return (I == O);

}//判断栈操作序列是否合法
// TODO 王道书P70应用题04
bool IsLinkSymmetry(LinkList L, int n) {
    if (n == 0 || n == 1) {
        return true;
    }
    SqStack S;
    InitStack(&S);
    int count = 0;
    LNode *p = L;
    while (count < n / 2) {
        Push(&S, p->next->data);
        p = p->next;
        count++;
    }
    if (n / 2 % 2 == 1) {
        p = p->next;
    }
    while (!StackIsEmpty(S)) {
        int peek = 0;
        Pop(&S, &peek);
        if (p->next->data != peek) {
            return false;
        }
        p = p->next;
    }
    return true;
}//判断链表的全部n个字符是否中心对称
// TODO 王道书P99应用题01
bool BracketsCheck(char *str) {
    SqStack S;
    InitStack(&S);
    int i = 0;
    while (str[i] != '\0') {
        int flag = 0;
        switch (str[i]) {
            case '(':
                Push(&S, 1);
                break;
            case '[':
                Push(&S, 2);
                break;
            case '{':
                Push(&S, 3);
                break;
            case ')':
                Pop(&S, &flag);
                if (flag != 1) {
                    return false;
                }
                break;
            case ']' :
                Pop(&S, &flag);
                if (flag != 2) {
                    return false;
                }
                break;
            case '}':
                Pop(&S, &flag);
                if (flag != 3) {
                    return false;
                }
                break;

        }
        i++;
    }
    return StackIsEmpty(S);
}//括号匹配

//队列操作
void InitSqQueue(SqQueue *Q) {
    Q->rear = Q->front = 0;
}//队列初始化操作
bool IsQueueEmpty(SqQueue Q) {
    if (Q.rear == Q.front) {
        return true;
    } else
        return false;
}//队列判空
bool EnQueue(SqQueue *Q, int addNumber) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return false;
    } else {
        Q->data[Q->rear] = addNumber;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return true;
    }
}//入队
bool DeQueue(SqQueue *Q, int *returnNumber) {
    if (Q->rear == Q->front) {
        return false;
    } else {
        *returnNumber = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return true;
    }
}//出队

//队列应用
// TODO 王道书P86应用题01
typedef struct {
    int data[MAXSIZE];
    int front, rear, tag;
} TagQueue;//带标志位的队列结构体
void InitTagQueue(TagQueue *Q) {
    Q->front = Q->rear = Q->tag = 0;
}

bool EnTagQueue(TagQueue *Q, int addNumber) {
    if (Q->rear == Q->front && Q->tag == 1) {
        //由入队导致，则为队满
        return false;
    }
    Q->data[Q->rear] = addNumber;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    Q->tag = 1;
    return true;
}

bool DeTagQueue(TagQueue *Q, int *returnNumber) {
    if (Q->rear == Q->front && Q->tag == 0) {
        //由出队导致，则为队空
        return false;
    }
    *returnNumber = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    Q->tag = 0;
    return true;
}
//通过增加tag标志位，判断rear == front是队空还是队满

//二叉树相关数据结构操作

/*
 * BiNode node1 = {1, NULL, NULL};
    BiNode node2 = {2, NULL, NULL};
    BiNode node3 = {3, NULL, NULL};
    BiNode node4 = {4, NULL, NULL};
    BiNode node5 = {5, NULL, NULL};
    BiNode node6 = {6, NULL, NULL};

    BiTree root = &node1;
    root->LeftChild = &node2;
    root->RightChild = &node3;

    node2.RightChild = &node4;

    node4.LeftChild = &node6;

    node3.RightChild = &node5;
 *///创建二叉树测试样例

//二叉树栈
typedef struct BiStack {
    BiNode data[MAXSIZE];
    int top;
} BiStack;//二叉树存二叉树节点的栈
void InitBiStack(BiStack *pStack) {
    pStack->top = -1;
}//初始化栈
bool IsEmptyBiStack(BiStack stack) {
    if (stack.top == -1) {
        return true;
    } else
        return false;
}//判空
void PushBiStack(BiStack *pStack, BiNode pNode) {
    pStack->data[++pStack->top] = pNode;
}//压栈
void PopBiStack(BiStack *pStack, BiNode *pNode) {

    *pNode = pStack->data[pStack->top--];

}//弹出

//二叉树队列
typedef struct BiQueue {
    BiNode data[MAXSIZE];
    int front, rear;
} BiQueue;//二叉树队列
void InitBiQueue(BiQueue *Q) {
    Q->front = Q->rear = 0;
}//初始化队
void EnBiQueue(BiQueue *Q, BiNode biNode) {
    Q->data[Q->rear] = biNode;
    Q->rear = (Q->rear + 1) % MAXSIZE;
}//入队
void DeBiQueue(BiQueue *Q, BiNode *biNode) {
    *biNode = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
}//出队
bool IsEmptyBiQueue(BiQueue Q) {
    if (Q.rear == Q.front) {
        return true;
    } else {
        return false;
    }
}//判队空
//二叉树操作
BiNode* createBiNode(int data) {
    BiNode* newNode = (BiNode*)malloc(sizeof(BiNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->LeftChild = NULL;
        newNode->RightChild = NULL;
    }
    return newNode;
}//动态创建二叉树节点
void visit(BiNode root) {
    printf("%d ", root.data);
}//访问二叉树节点，打印data值
void PreOrder(BiTree T) {
    if (T != NULL) {
        visit(*T);
        PreOrder(T->LeftChild);
        PreOrder(T->RightChild);
    }
}//二叉树前序遍历
void InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->LeftChild);
        visit(*T);
        InOrder(T->RightChild);
    }
}//二叉树中序遍历
void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->LeftChild);
        PostOrder(T->RightChild);
        visit(*T);
    }
}//二叉树后序遍历
void PreOrder2(BiTree T) {
    BiStack S;
    InitBiStack(&S);
    BiNode *p = T;
    while (p || !(IsEmptyBiStack(S))) {
        if (p) {
            visit(*p);
            PushBiStack(&S, *p);
            p = p->LeftChild;
        } else {
            BiNode biNode;
            PopBiStack(&S, &biNode);
            p = biNode.RightChild;
        }
    }
}//二叉树前序遍历的迭代方法
void InOrder2(BiTree T) {
    BiStack S;
    InitBiStack(&S);
    BiNode *p = T;
    while (p || !(IsEmptyBiStack(S))) {
        if (p) {
            PushBiStack(&S, *p);
            p = p->LeftChild;
        } else {
            BiNode poppedNode;
            PopBiStack(&S, &poppedNode);
            visit(poppedNode);
            p = poppedNode.RightChild;
        }
    }
}//二叉树中序遍历迭代方法
void LevelOrder(BiTree T) {
    BiQueue Q;
    InitBiQueue(&Q);
    BiNode *p = T;
    EnBiQueue(&Q, *p);
    while (!(IsEmptyBiQueue(Q))) {
        DeBiQueue(&Q, p);
        visit(*p);
        if (p->LeftChild != NULL) {
            EnBiQueue(&Q, *p->LeftChild);
        }
        if (p->RightChild != NULL) {
            EnBiQueue(&Q, *p->RightChild);
        }
    }
}//二叉树层次遍历
int CountBiTree(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    return 1 + CountBiTree(T->RightChild) + CountBiTree(T->LeftChild);
}//计算二叉树节点个数
int HeightBiTree(BiTree T) {
    if (T == NULL) {
        return 0;
    }

    int leftDepth = HeightBiTree(T->LeftChild);
    int rightDepth = HeightBiTree(T->RightChild);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}//计算二叉树树高



//二叉树应用
// TODO 王道书P140应用题05
int CommonAncestor(BiTree T, int i, int j) {
    /*
     *
     * while（i节点和j节点不为空）{
     * if(i>j){
     * i = i / 2;
     * }else if(i<j){
     * j = j / 2;
     * }else{
     * break;
     * }
     * return T[i];
     */
    return 1;
}//如果二叉树使用顺序存储，计算给定两节点最近的共同祖先
// TODO 王道书P158应用题03
//二叉树后序遍历的非递归算法
// TODO 王道书P158应用题04
void LevelReverserBiTree(BiTree T) {
    BiQueue Q;
    InitBiQueue(&Q);
    BiStack S;
    InitBiStack(&S);
    EnBiQueue(&Q, *T);
    while (!(IsEmptyBiQueue(Q))) {
        BiNode p;
        DeBiQueue(&Q, &p);
        PushBiStack(&S, p);
        if (p.LeftChild != NULL) EnBiQueue(&Q, *p.LeftChild);
        if (p.RightChild != NULL) EnBiQueue(&Q, *p.RightChild);
    }
    while (!(IsEmptyBiStack(S))) {
        BiNode p;
        PopBiStack(&S, &p);
        printf("%d ", p.data);
    }
}//二叉树的自下而上，从右到左的层次遍历算法
// TODO 王道书P158应用题05
int HeightBiTreeNonRecursion(BiTree T) {


}//非递归方法求二叉树的高度
// TODO 王道书P158应用题06
bool IsFullBiTree(BiTree T) {
    int h = HeightBiTree(T);
    int count = CountBiTree(T);
    return ((pow(2, h) - 1)) == count;
}//判断是否是满二叉树
bool IsCompleteBiTree(BiTree T) {
    if (T == NULL) {
        return true;
    }
    BiQueue Q;
    InitBiQueue(&Q);
    EnBiQueue(&Q, *T);
    int flag = 0;
    while (!(IsEmptyBiQueue(Q))) {
        BiNode p;
        DeBiQueue(&Q, &p);

        if (p.LeftChild != NULL) {
            if (flag) {
                return false;  // 如果之前遇到了非完全节点，但当前节点有左孩子，则不是完全二叉树
            }
            EnBiQueue(&Q, *p.LeftChild);
        } else {
            flag = true;//该节点是非完全节点
        }

        if (p.RightChild != NULL) {
            if (flag) {
                return false;  // 如果之前遇到了非完全节点，但当前节点有右孩子，则不是完全二叉树
            }
            EnBiQueue(&Q, *p.RightChild);
        } else {
            flag = true;//该节点是非完全节点
        }
    }
    return true;

}//判断一个二叉树是否是完全二叉树
// TODO 王道书P158应用题07
int CountNode2(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    if (T->LeftChild != NULL && T->RightChild != NULL) {
        return 1 + CountNode2(T->LeftChild) + CountNode2(T->RightChild);
    }
    return CountNode2(T->LeftChild) + CountNode2(T->RightChild);

}//计算二叉树中度为2的节点的个数
// TODO 王道书P158应用题08
void reverseBiTree(BiTree *T) {
    if (*T == NULL) {
        return;
    }

    // 交换当前节点的左右子树
    BiNode *temp = (*T)->LeftChild;
    (*T)->LeftChild = (*T)->RightChild;
    (*T)->RightChild = temp;

    // 递归处理左右子树
    reverseBiTree(&(*T)->LeftChild);
    reverseBiTree(&(*T)->RightChild);
}//写一个算法，将二叉树T中所有节点的左右子树互换
// TODO 王道书P158应用题09
int KthNodeValue(BiTree T, int k) {
    BiStack S;
    InitBiStack(&S);
    BiNode *p = T;
    int count = 0;
    while (p || !IsEmptyBiStack(S)) {
        if (p) {
            PushBiStack(&S, *p);
            count++;
            if (count == k) {
                return p->data;
            }
            p = p->LeftChild;
        } else {
            BiNode biNode;
            PopBiStack(&S, &biNode);
            p = biNode.RightChild;
        }
    }
    return -1;
}//求二叉树中先序遍历中第K个节点的值
// TODO 王道书P158应用题10
void FreeSubTree(BiTree *T){
    if ((*T)->LeftChild!=NULL){
        FreeSubTree(&(*T)->LeftChild);
    }
    if ((*T)->RightChild!=NULL){
        FreeSubTree(&(*T)->RightChild);
    }
    free(*T);
}
void DeleteXBiTree(BiTree *T, int x) {
    BiStack S;
    InitBiStack(&S);
    BiNode *p = *T;
    while (p || !IsEmptyBiStack(S)) {
        if (p) {
            PushBiStack(&S, *p);
            if (p->data == x){
                FreeSubTree(&p);
            }
            p = p->LeftChild;
        }else{
            BiNode biNode;
            PopBiStack(&S,&biNode);
            p = biNode.RightChild;
        }
    }
}//对于一个颗二叉树中的所有值为x的节点，删除它为根的子树，并释放对应的空间




//线索二叉树的构造
void inThreadTree(ThreadNode *p, ThreadNode *pre) {
    if (p != NULL) {
        inThreadTree(p->LChild, pre);
        if (p->LChild == NULL) {
            p->LChild = pre;
            p->LTag = 1;
        }
        if (pre != NULL && pre->RChild == NULL) {
            pre->RChild = p;
            pre->RTag = 1;
        }
        pre = p;
        inThreadTree(p->RChild, pre);
    }
}

void CreateThreadTree(ThreadTree *T) {
    ThreadNode *pre = NULL;
    if (T != NULL) {
        inThreadTree(*T, pre);
        pre->RChild = NULL;
        pre->RTag = 1;
    }
}

void visitThreadNode(ThreadNode p) {
    printf("%d ", p.data);
}//访问线索二叉树节点
ThreadNode *FirstNode(ThreadTree T) {
    ThreadNode *p = T;
    while (p->LTag == 0) {
        p = p->LChild;
    }
    return p;
}//寻找中序线索二叉树的第一个节点
ThreadNode *NextNode(ThreadNode *p) {
    if (p->RTag == 1) {
        return p->RChild;//RTag == 1，说明有孩子指向的即为后继节点
    } else {
        return FirstNode(p->RChild);//寻找右子树中最左下的节点
    }
}

void InOrderThreadTree(ThreadTree T) {
    for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p)) {
        visitThreadNode(*p);

    }
}//中序遍历中序线索二叉树

bool TestAndSet(bool *lock) {
    bool old;
    old = *lock;
    *lock = true;
    return old;
}//操作系统同步与互斥

int main() {

    BiNode node1 = {1, NULL, NULL};
    BiNode node2 = {2, NULL, NULL};
    BiNode node3 = {3, NULL, NULL};
    BiNode node4 = {4, NULL, NULL};
    BiNode node5 = {5, NULL, NULL};
    BiNode node6 = {6, NULL, NULL};
    BiNode *node7 = (BiNode*) malloc()
    BiTree root = &node1;
    root->LeftChild = &node2;
    root->RightChild = &node3;

    node2.RightChild = &node4;

    node4.LeftChild = &node6;


    node3.RightChild = &node5;


    // 执行前序遍历
    DeleteXBiTree(&root,1);
    LevelOrder(root);

}

