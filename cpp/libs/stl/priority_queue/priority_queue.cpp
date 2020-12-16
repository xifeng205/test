#include <queue>
#include <iostream>

using namespace std;

int main()
{
    priority_queue<double> pq1;
    pq1.push(3.2); pq1.push(9.8); pq1.push(9.8); pq1.push(5.4);
    while(!pq1.empty()) {
        cout << pq1.top() << " ";
        pq1.pop();
    } //上面输出 9.8 9.8 5.4 3.2
    cout << endl;
    priority_queue<double,vector<double>,greater<double> > pq2;
    pq2.push(3.2); pq2.push(9.8); pq2.push(9.8); pq2.push(5.4);
    while(!pq2.empty()) {
        cout << pq2.top() << " ";
        pq2.pop();
    }
    //上面输出 3.2 5.4 9.8 9.8
    return 0;
}
