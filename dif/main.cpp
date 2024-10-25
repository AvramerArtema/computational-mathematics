#include "funcs.h"
#include<fstream>



int main() {

	const double x0 = 1;
	const std::array< double, 16> step = { 1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15 };
	const double e = exp(1);

	// Task 1

	std::ofstream data0("data0.txt");

	if (!data0) {
		return -1;
	}
	data0.precision(10);

	for (int i = 0; i < 16; i++) {
		data0 << step[i] << "		" << d_e<double, 2>(x0, step[i], { -1, 1 }) << std::endl;
	}

	data0.close();

	std::array<double, 100000> ln_step;
	ln_step[0] = -35;

	for (int i = 1; i < 100000; i++) {
		double delta = 0.00035;
		ln_step[i] = ln_step[i - 1] + delta;
	}

	std::ofstream data3("data3.txt");

	if (!data3) {
		return -1;
	}
	data3.precision(10);

	for (double x : ln_step) {
		data3 << x << " " << log(abs(d_e<double, 3>(x0, exp(x), { -1, 1, 2 }) - e)) << std::endl;
	}

	data3.close();

	std::ofstream data4("data4.txt");

	if (!data4) {
		return -1;
	}
	data4.precision(10);

	for (double x : ln_step) {
		data4 << x << " " << log(abs(d_e<double, 4>(x0, exp(x), { -2, -1, 1, 2 }) - e)) << std::endl;
	}

	data4.close();

	std::ofstream data5("data5.txt");

	if (!data5) {
		return -1;
	}
	data5.precision(10);

	for (double x : ln_step) {
		data5 << x << " " << log(abs(d_e<double, 5>(x0, exp(x), { -2, -1, 1, 2, 3 }) - e)) << std::endl;
	}

	data5.close();
	
	return 0;
}