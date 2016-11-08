#include <iostream>

const int SIZE = 1000;int tape[ SIZE ];
int *dp = tape;

int main()
{
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    while (*dp) {
        dp++;
        ++*dp;
        ++*dp;
        ++*dp;
        ++*dp;
        while (*dp) {
            dp++;
            ++*dp;
            ++*dp;
            dp++;
            ++*dp;
            ++*dp;
            ++*dp;
            dp++;
            ++*dp;
            ++*dp;
            ++*dp;
            dp++;
            ++*dp;
            dp--;
            dp--;
            dp--;
            dp--;
            --*dp;
            }
        dp++;
        ++*dp;
        dp++;
        ++*dp;
        dp++;
        --*dp;
        dp++;
        dp++;
        ++*dp;
        while (*dp) {
            dp--;
            }
        dp--;
        --*dp;
        }
    dp++;
    dp++;
    std::cout << static_cast<char>(*dp);
    dp++;
    --*dp;
    --*dp;
    --*dp;
    std::cout << static_cast<char>(*dp);
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    ++*dp;
    std::cout << static_cast<char>(*dp);
    std::cout << static_cast<char>(*dp);
    ++*dp;
    ++*dp;
    ++*dp;
    std::cout << static_cast<char>(*dp);
    dp++;
    dp++;
    std::cout << static_cast<char>(*dp);
    dp--;
    --*dp;
    std::cout << static_cast<char>(*dp);
    dp--;
    std::cout << static_cast<char>(*dp);
    ++*dp;
    ++*dp;
    ++*dp;
    std::cout << static_cast<char>(*dp);
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    std::cout << static_cast<char>(*dp);
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    --*dp;
    std::cout << static_cast<char>(*dp);
    dp++;
    dp++;
    ++*dp;
    std::cout << static_cast<char>(*dp);
    dp++;
    ++*dp;
    ++*dp;
    std::cout << static_cast<char>(*dp);
}
