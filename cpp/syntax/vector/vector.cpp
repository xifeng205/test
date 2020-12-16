/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-06-14 14:26
 * Last modified : 2020-06-14 14:26
 * Filename      : vector.cpp
 * Description   : 
*********************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    std::vector<vector<int>> v(3);

    for (int i=0; i<v.size(); ++i) {
        for (int j=0; j<4; ++j) {
            v[i].push_back(j);
        } 
    }
    for (int i=0; i<v.size(); ++i) {
        for (int j=0; j<4; ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
