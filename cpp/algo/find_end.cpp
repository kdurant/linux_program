/*
find_end:  查找子序列[s_first, s_last)在序列[first, last)中最后一次出现的位置
 */
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int>           v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int>::iterator result;
    std::vector<int>           t1{1, 2, 3};

    result = std::find_end(v.begin(), v.end(), std::begin(t1), std::end(t1));
    if(result == v.end())
        std::cout << "sequence not found\n";
    else
        std::cout << "last occurrence is at : " << std::distance(v.begin(), result) << "\n";
    return 0;
}
