#include<iostream>
#include<cstdio>
using namespace std;

struct node{
    int dis = 0;
    int fa = 0;
}arr[50010];
int num = 0;

void init(int& n)
{
    for(int i = 1;i <= n;i++) arr[i].fa = i;
}

int find(int& x)
{
    if(x != arr[x].fa) 
    {
        int k = arr[x].fa;
        arr[x].fa = find(arr[x].fa);
        arr[x].dis = (arr[k].dis + arr[x].dis) % 3;
    }
    return arr[x].fa;
}

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
        else if(p == 2 && x == y) {num++;}
        else {merge(p,x,y);}
    }
    printf("%d",num);
}