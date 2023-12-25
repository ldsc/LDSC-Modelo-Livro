//https://en.cppreference.com/w/cpp/ranges
#include <ranges>
#include <iostream>

int main() {
    auto const ints = {0,1,2,3,4,5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    // Uso de | "pipe" com views para filtrar e transformar os dados
    for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    // Uso tradicional sem uso de pipe
    for (int i : std::views::transform(std::views::filter(ints, even), square)) {
        std::cout << i << ' ';
    }
}
