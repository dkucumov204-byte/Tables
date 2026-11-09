#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

int simple_string_hash(std::string s)
{
    int hash = 0;
    for (char c : s)
    {
        hash += static_cast<int>(c);
    }
    return hash;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::string input;
    do
    {
        std::cout << "Введите строку: ";
        std::getline(std::cin, input);

        int hash = simple_string_hash(input);
        std::cout << "Наивный хэш строки " << input << " = " << hash << std::endl;
    }
    while (input != "exit");

    return 0;
}