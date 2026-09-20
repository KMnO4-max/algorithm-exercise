#include<iostream>
#include<cstdio>
using namespace std;

int arr[100000];
void quick_sort(int begin,int end)
{
    if(end <= begin)
    {
        return;
    }
    int i = begin,j = end;
    int get = arr[(i + j)/2];
    while(i <= j)
    {
        while(arr[i] < get) {i++;}
        while(arr[j] > get) {j--;}
        if(i <= j) 
        {
            swap(arr[i],arr[j]);
            i++;
            j--;
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