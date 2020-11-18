#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> v1{0, 1, 2, 3, 40, 40, 41, 41, 5};
    auto             i1 = std::adjacent_find(v1.begin(), v1.end());
    if(i1 == v1.end())
        std::cout << "no matching adjacent elements\n";
    else
    {
        std::cout << "the first adjacent pair of equal elements at:" << std::distance(v1.begin(), i1) << std::endl;
        std::cout << *i1 << std::endl;
    }

    return 0;
}
