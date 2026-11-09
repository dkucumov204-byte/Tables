#include <iostream>
#include <string>
#include <cstdint>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

int real_string_hash(const std::string& s, int p, int n)
{
    if (n <= 0) return 0;

    uint64_t hash = 0;
    uint64_t p_pow = 1;

    for (char c : s)
    {
        uint64_t code = static_cast<unsigned char>(c);
        hash = (hash + (code * p_pow) % n) % n;
        p_pow = (p_pow * static_cast<uint64_t>(p)) % n;
    }

    return static_cast<int>(hash);
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    int p, n;
    std::cout << "Введите p: ";
    std::cin >> p;
    std::cout << "Введите n: ";
    std::cin >> n;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string input;
    do
    {
        std::cout << "Введите строку: ";
        std::getline(std::cin, input);

        int hash = real_string_hash(input, p, n);
        std::cout << "Хэш строки " << input << " = " << hash << std::endl;
    }
    while (input != "exit");

    return 0;
}