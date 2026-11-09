#include <iostream>
#include <string>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#endif

int find_substring_light_rabin_karp(std::string source, std::string substring)
{
    if (substring.empty()) return 0;
    if (substring.size() > source.size()) return -1;

    const uint64_t p = 29;
    const uint64_t n = 1000000007ULL;

    size_t m = substring.size();
    size_t len = source.size();

    uint64_t sub_hash = 0;
    uint64_t win_hash = 0;
    uint64_t p_pow = 1;

    for (size_t i = 0; i < m; i++)
    {
        sub_hash = (sub_hash * p + static_cast<unsigned char>(substring[i])) % n;
        win_hash = (win_hash * p + static_cast<unsigned char>(source[i])) % n;
        if (i < m - 1)
            p_pow = (p_pow * p) % n;
    }

    for (size_t i = 0; i + m <= len; i++)
    {
        if (win_hash == sub_hash)
        {
            bool match = true;
            for (size_t j = 0; j < m; j++)
            {
                if (source[i + j] != substring[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
                return static_cast<int>(i);
        }

        if (i + m < len)
        {
            win_hash = (win_hash + n - (static_cast<unsigned char>(source[i]) * p_pow) % n) % n;
            win_hash = (win_hash * p + static_cast<unsigned char>(source[i + m])) % n;
        }
    }

    return -1;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::string source;
    std::cout << "Введите строку, в которой будет осуществляться поиск: ";
    std::getline(std::cin, source);

    std::string substring;
    do
    {
        std::cout << "Введите подстроку, которую нужно найти: ";
        std::getline(std::cin, substring);

        int index = find_substring_light_rabin_karp(source, substring);

        if (index == -1)
            std::cout << "Подстрока " << substring << " не найдена" << std::endl;
        else
            std::cout << "Подстрока " << substring << " найдена по индексу " << index << std::endl;
    }
    while (substring != "exit");

    return 0;
}