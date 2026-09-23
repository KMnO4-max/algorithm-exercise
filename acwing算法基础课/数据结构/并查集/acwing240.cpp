#include<iostream>
#include<cstdio>
using namespace std;
//这道题也是相当经典带权并查集的题目，这道题的难点有几个：一，如何设计节点的权值，也就是如何表示子节点与父节点的关系
//二，设计权值后如何计算相差几个节点或根本不在一颗树上的节点之间的关系，这是本题判断对错和合并集合的关键
//三，带权的路径压缩，这其实算不上是一个难点，但对没有看过模板的人来说，还是有些困难

//本体的权值设计：我们不妨假设有两个节点x、y,x为y的父节点，我们令x->y为0，则为同类；为1，表示y被x吃；为2，表示y吃x.
//节点间的运算；1，x->y为1，y->z为1，我们可以发现x与z的关系为x吃z(x->z为2),同时有x->z == x->y + y->z;
//2，x->y为2，y->z为2，x与z的关系为x被z吃(x->z为1),同时有（x->y + y->z）%3 == x->z；
//3，已知x->y,如何求y->x:当x->y为0，y->x为0；当x->y为1，y->x为2；当x->y为2，y->x为1；
//我们发现x->y为1或2时，x->y + y->x为3；当x->y为0时，y->x为0可看作(3 - 0)%3;
//所以我们可认为已知x->y，y->x可看作(3 - x->y) % 3
struct node{
    int dis = 0;
    int fa = 0;
}arr[50010];//节点设计；有价值的是节点的父节点和与父节点的关系（也就是权值），故整合成一个结构体（也可以分成两个数组，但可能不够直观）
int num = 0;//错误的信息数量，也就最终的答案

void init(int& n)
{
    for(int i = 1;i <= n;i++) arr[i].fa = i;//初始化
}

int find(int& x)//带权合并
{
    //带权合并，我们要求节点到根节点的权值，但我们只知道节点到它父节点的权值，但我们可以想到在进行递归时是从根节点步步返回，因此可以在返回时对节点进行累加修改
    //因为在递归同时会更改节点的父节点，所以要记录原来的父节点
    //注意：要先递归再累加，不然无法正确更改节点的权值
    if(x != arr[x].fa) 
    {
        int k = arr[x].fa;//记录父节点
        arr[x].fa = find(arr[x].fa);
        arr[x].dis = (arr[k].dis + arr[x].dis) % 3;
    }
    return arr[x].fa;
}

//本函数的运行逻辑：要先确定x与y的根节点。根节点不相同，说明两个节点间先前不存在关系，需要把所在集合合并
//如根节点相同，则二者的关系已经确定，要判断节点的关系是否正确，也是本题答案的主要来源
void merge(int& p,int& x,int& y)
{
    int rootx = find(x),rooty = find(y);
    if(rootx == rooty && (p - 1 + arr[y].dis) % 3 != arr[x].dis) num++;
    else if(rootx != rooty)
    {
        arr[rooty].fa = x;
        arr[rooty].dis = (3 - (p - 1 + arr[y].dis) % 3) % 3;
    }
}

int main()
{
    int n = 0,k = 0;
    scanf("%d %d",&n,&k);
    init(n);
    for(int i = 0;i < k;i++)
    {
        int p = 0,x = 0,y = 0;
        scanf("%d %d %d",&p,&x,&y);
        if(x > n || y > n) {num++;}
        else if(p == 2 && x == y) {num++;}//在主函数中先行判断两种错误情况（x,y超出题目范围和自己吃自己）
        else {merge(p,x,y);}
    }
    printf("%d",num);
}
