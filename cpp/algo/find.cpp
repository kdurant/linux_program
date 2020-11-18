/*
find: 在指定范围内查找和目标元素值相等的第一个元素
 */

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> nums{1, 20, 3, 4, 4, 3, 7, 8, 9, 10};
    auto             res = std::find(nums.begin(), std::end(nums), 20);
    std::cout << *res << std::endl;

    res = std::find_if(std::begin(nums), std::end(nums), [](int i) { return i == 4; });
    std::cout << *res << std::endl;

    return 0;
}
