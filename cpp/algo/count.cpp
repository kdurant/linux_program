/*
count: 统计数组中有多少个数与要查询的数相同
count_if: 统计满足条件的计数
 */
#include <iostream>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> nums{1, 2, 3, 4, 4, 3, 7, 8, 9, 10};

    std::cout << std::count(nums.begin(), nums.end(), 3) << std::endl;
    std::cout << std::count_if(nums.begin(), nums.end(), [](int i) { return i > 4; });

    return 0;
}

