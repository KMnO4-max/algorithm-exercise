#include<iostream>
#include<cstdio>
using namespace std;

int arr[100000];
//快排的核心部分在于quick_sort函数以及比较复杂的边界条件
//快排的主要思想是在输入的数据中任取一个数（一般为数据居中的数，可以有效避免一些特殊数据情况），把小于它的数放在左边或右边（由从小到大或从大到小决定），把大于它的数放在右边或左边（同理）
//再把数据分成两部分，不断递归（这里提供的交换数据为双指针优化，不是简单的暴力做法，对重复的数据本做法也有特殊处理）
void quick_sort(int begin,int end)
{
    if(end <= begin)//递归结束判定，当数据只有一个或边界错误时，递归结束，这里不能写等于
    {
        return;
    }
    int i = begin,j = end;//这里对begin和end变量进行备份，不能在原有begin和end变量上进行更改，之后递归会用到原有变量
    int get = arr[(i + j)/2];//取数据居中的数
    while(i <= j)//这里<=和<都可以，主要区别在于对i==j时的处理，对结果影响不大
    {
        while(arr[i] < get) {i++;}//这里不能改为<=，当get为最大值时，会数组越界
        while(arr[j] > get) {j--;}//这里不能改为>=，当get为最小至时，会数组越界
        //有人可能会提议改为arr[i] <= get && i <= end以及arr[j] >= get && j >= begin，我们来看一组数据49 59 88 37 98 97 68 54 31 3，第一次递归时get为98
        //i为9，j为9，无论做不做数值替换，arr[9]均不改变，若循环条件为i<=j则发生死循环
        //若循环条件为i<j,我们会发现下面的递归分别为quick_sort(0,9)和quick_sort(9,9),quick_sort(9,9)递归结束，quick_sort(0,9)出现死递归
        if(i <= j) //这里不能为<.举数据1 2，此时get为1，i为0，j为0.若为i<j，下面递归为quick_sort(0,0),quick_sort(0,1),会发现又出现死递归
                   //若为i<=j,则不会有问题，交换后i为1，j为-1，递归为quick_sort(0,-1)(与上文的不能去等对应），quick_sort(1,1)，二者均结束
        {
            swap(arr[i],arr[j]);
            i++;
            j--;
            //i++与j--都不可去，循环条件为arr[i]<get和arr[j]>get，当arr[i]与arr[j]都为get时，交换二者不影响取值，若无i++与j--，下一步循环会重复以上步骤，出现死循环
        }
    }
    quick_sort(begin,j);
    quick_sort(i,end);
}

int main()
{
    int n = 0;
    scanf("%d",&n);
    for(int i = 0;i < n;i++) {scanf("%d",&arr[i]);}
    quick_sort(0,n - 1);
    for(int i = 0;i < n;i++) {printf("%d ",arr[i]);}
}
//以上都为我自己练习时出现的问题，欢迎大家补充
//acwing786核心部分与本题相同，故不再赘述
