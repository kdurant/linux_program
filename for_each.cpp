#include <iostream>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::for_each(nums.begin(), nums.end(), [](int &item) { item += 1; });

    for(auto i : nums)
        std::cout << i << "\t";
    std::cout << std::endl;

    return 0;
}
