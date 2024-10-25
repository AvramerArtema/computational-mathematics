#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <type_traits>

// Определяем узлы и веса для квадратур Гаусса
constexpr std::array<double, 2> gauss_nodes_2 = { -1.0 / std::sqrt(3), 1.0 / std::sqrt(3) };
constexpr std::array<double, 2> gauss_weights_2 = { 1.0, 1.0 };

constexpr std::array<double, 3> gauss_nodes_3 = { -std::sqrt(3.0 / 5.0), 0.0, std::sqrt(3.0 / 5.0) };
constexpr std::array<double, 3> gauss_weights_3 = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };

// Получение аргумента функции
template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

// Разность типов
template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

// Интегрирование на одном отрезке
template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable& func,
        const typename ArgumentGetter<Callable>::Argument& start,
        const typename ArgumentGetter<Callable>::Argument& end
) {
    using ArgType = typename ArgumentGetter<Callable>::Argument;
    double midpoint = (start + end) / 2.0;
    double half_length = (end - start) / 2.0;
    double result = 0.0;

    for (std::size_t i = 0; i < N; ++i) {
        if (N == 2) {
            result += gauss_weights_2[i] * func(midpoint + half_length * gauss_nodes_2[i]);
        } else {
            result += gauss_weights_3[i] * func(midpoint + half_length * gauss_nodes_3[i]);
        }
    }

    return result * half_length;
}

// Интегрирование с разбивкой на подтрезки
template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable& func,
        const typename ArgumentGetter<Callable>::Argument& start,
        const typename ArgumentGetter<Callable>::Argument& end,
        const Dif<typename ArgumentGetter<Callable>::Argument>& dx
) {
    double total = 0.0;
    for (double current = start; current < end; current += dx) {
        double next = std::min(current + dx, end);
        total += integrate<Callable, N>(func, current, next);
    }
    return total;
}