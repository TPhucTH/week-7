#include <iostream>
using namespace std;
int find(int a[],int start,int end,int guess)
{
    int x = (start + end)/2;
    if(a[start] == guess)    return start;
    if(a[end] == guess)    return end;
    if(a[x] == guess)     return x;
    if(a[x] > guess)   return find(a,start+1,x,guess);
    if(start == x && end == x) return -1;
    return find(a,x,end-1,guess);
    
}

int main()
{ 
    int n;
    cin >> n;
    int a[n];
    int guess;
    for(int i = 0;i < n;i++)
    {
         cin >> a[i];
    }
    cout << 5/2 << endl;
    cin >> guess;
    cout << find(a,0,n-1,guess);
    return 0;
}
