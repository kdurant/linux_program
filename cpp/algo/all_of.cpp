/*
all_of() 算法会返回 true，前提是序列中的所有元素都可以使谓词返回 true。
any_of() 算法会返回 true，前提是序列中的任意一个元素都可以使谓词返回 true。
none_of() 算法会返回 true，前提是序列中没有元素可以使谓词返回 true。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    vector<int> a{10, 2, 1};
    cout << all_of(a.begin(), a.end(), [](int i) { return i % 2 == 0; }) << endl;
    cout << any_of(a.begin(), a.end(), [](int i) { return i % 2 == 0; }) << endl;
    cout << none_of(a.begin(), a.end(), [](int i) { return i % 2 == 0; }) << endl;

    return 0;
}
