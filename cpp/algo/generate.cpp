#include <iostream>
#include <iterator>
#include <system_error>
#include <vector>
#include <algorithm>
#include <string>

int main(void)
{
    std::vector<int> v(5);
    // mutable 表示以传值方式捕获的值可以被改变
    //std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });

    int  m = 1;
    int &n = m;
    std::generate(v.begin(), v.end(), [&n]() { return n++; });

    for(auto item : v)
        std::cout << item << "\t";

    return 0;
}
