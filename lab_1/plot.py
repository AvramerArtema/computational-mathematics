import numpy as np
import matplotlib.pyplot as plt

# Чтение данных из файла
data = np.loadtxt('errors.txt')
log_h = data[:, 0]
log_errors_2 = data[:, 1]
log_errors_3 = data[:, 2]

# Построение графиков
plt.figure(figsize=(10, 6))
plt.plot(log_h, log_errors_2, label='2 узла', marker='o')
plt.plot(log_h, log_errors_3, label='3 узла', marker='o')
plt.xlabel('log(h)')
plt.ylabel('log(Ошибка)')
plt.title('Зависимость ошибки интегрирования от шага h')
plt.legend()
plt.grid()
plt.show()

# Определение коэффициента наклона
slope_2, _ = np.polyfit(log_h, log_errors_2, 1)
slope_3, _ = np.polyfit(log_h, log_errors_3, 1)

print(f'Коэффициент наклона для 2 узлов: {slope_2}')
print(f'Коэффициент наклона для 3 узлов: {slope_3}')