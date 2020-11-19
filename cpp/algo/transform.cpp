#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>

int main(void)
{
    std::string s("hello");
    std::string s1;
    s1.resize(5);

    std::transform(s.begin(), s.end(), s1.begin(), [](unsigned char c) -> unsigned char { return std::toupper(c); });
    std::cout << s1 << std::endl;

    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{5, 4, 3, 2, 1};
    std::vector<int> v3;
    v3.resize(5);
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int a, int b) { return a + b; });
    for(auto item : v3)
        std::cout << item << "\t";
    std::cout << "\n";
    return 0;
}
