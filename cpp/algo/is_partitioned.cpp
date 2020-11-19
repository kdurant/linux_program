/*
is_partitioned: 
partition: 
 */
#include <algorithm>
#include <array>
#include <ios>
#include <iostream>

int main(void)
{
    //std::array<int, 9> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 9> v;
    std::generate(v.begin(), v.end(), [n = 1]() mutable { return n++; });

    auto is_even = [](int i) { return i % 2 == 0; };

    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << std::endl;

    std::partition(v.begin(), v.end(), is_even);
    for(auto i : v)
        std::cout << i << "\t";
    std::cout << "\n";
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << std::endl;

    return 0;
}
