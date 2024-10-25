#include "func.h"
#include <iostream>
#include <cstdlib>

// Функция для интегрирования
double my_function(double x) {
    return std::sin(x);
}

// Точное значение интеграла
double exact_integral(double start, double end) {
    return -std::cos(end) + std::cos(start); // Интеграл от sin(x) = -cos(x)
}

int main() {


    // Команда для запуска Python-скрипта
    const char* command = "C:\\Users\\Acer\\AppData\\Local\\Programs\\Python\\Python39\\python.exe plot.py"; // Убедитесь, что указали правильный путь к вашему скрипту

    // Запуск команды
    int result = system(command);

    // Проверка результата выполнения
    if (result == 0) {
        std::cout << "Скрипт успешно выполнен." << std::endl;
    } else {
        std::cout << "Ошибка при выполнении скрипта. Код ошибки: " << result << std::endl;
    }

    const std::vector<double> hs = { 0.1, 0.05, 0.01, 0.005, 0.001 }; // Значения h
    std::vector<double> errors_2, errors_3;

    double exact_value = exact_integral(0.0, 10.0);

    // Вычисление ошибок для квадратур с 2 и 3 узлами
    for (double h : hs) {
        double total_error_2 = std::abs(integrate<decltype(my_function), 2>(my_function, 0.0, 10.0, h) - exact_value);
        double total_error_3 = std::abs(integrate<decltype(my_function), 3>(my_function, 0.0, 10.0, h) - exact_value);

        errors_2.push_back(total_error_2);
        errors_3.push_back(total_error_3);
    }

    // Запись ошибок в файл для построения графика
    std::ofstream file("errors.txt");
    for (size_t i = 0; i < hs.size(); ++i) {
        file << std::log(hs[i]) << " " << std::log(errors_2[i]) << " " << std::log(errors_3[i]) << "\n";
    }
    file.close();

    // Вывод ошибок
    std::cout << "Ошибки для квадратур Гаусса:\n";
    for (size_t i = 0; i < hs.size(); ++i) {
        std::cout << "h: " << hs[i] << ", Ошибка (2 узла): " << errors_2[i] << ", Ошибка (3 узла): " << errors_3[i] << "\n";
    }

    return 0;
}