#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello conrrency world\n";
}

int main(int argc, char *argv[])
{
    std::thread t(hello);
    t.join();

    std::cout << "main function\n";

    return 0;
}
