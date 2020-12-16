/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 16:46
 * Last modified : 2020-08-19 16:46
 * Filename      : test96.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {
  template <typename T> 
    int  bsearch1(T &arr, T x, int l, int h) {
      int mid = (l + h) / 2;
      if (arr[mid] == x) return mid;
      if (arr[mid] < x) return bsearch1(arr, x, mid, h);
      if (arr[mid] > x) return bsearch1(arr, x, l, mid);
      return -1; 
    } 
  template <typename T>
  int bsearch(T &a,T x,int n)
    {
      int low,high,mid;
      low=0;high=n-1;
      while(low<=high)
      {
        mid=(low+high)/2;
        if(a[mid].key==key) return mid;
        else if(a[mid].key<key) low=mid+1;
        else high=mid-1;
      }
      return -1;
    }
int main(int argc, char **argv) {
  long arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int index = test::bsearch1(arr, 7, 0, 9);
  std::cout << index << std::endl;
  return 0;
}
