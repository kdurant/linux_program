/*
search:  查找子序列[s_first, s_last)在序列[first, last)中第一次出现的位置
和find_end相反
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

    result = std::search(v.begin(), v.end(), std::begin(t1), std::end(t1));
    if(result == v.end())
        std::cout << "sequence not found\n";
    else
        std::cout << "last occurrence is at : " << std::distance(v.begin(), result) << "\n";
    return 0;
}

