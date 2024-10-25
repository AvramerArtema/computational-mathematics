#include "funcs.h"
#include<fstream>
#include<string>
#include<cmath>

int main()
{
	const unsigned int NUMBER_OF_POINTS = 1000;
	const double start = 0;
	
	const std::array<double, 6> data_final = { 2.0, 1.0, 0.5, 0.25, 0.125, 0.0625 };

	//N = 3

	std::string name1 = "data3-0.txt";

	std::ofstream data1(name1);
	if (!data1) {
		std::cout << "error in " << name1 << std::endl;
		return -1;
	}
	data1.precision(10);

	std::string name2 = "data3-1.txt";

	std::ofstream data2(name2);
	if (!data2) {
		std::cout << "error in " << name2 << std::endl;
		return -1;
	}
	data2.precision(10);

	for (double len = 0.0001; len < 2; len += 0.0001)
	{
		std::array<double, 3> x_lin =
			linear_grid<double, 3>(start, start + len);

		std::array<double, 3> y_lin;
		for (unsigned int i = 0; i < 3; i++) {
			y_lin[i] = exp(x_lin[i]);
		}

		NewtonInterpolator<double, double, 3> lin_interp3(x_lin, y_lin);

		double err = 0;

		for (double x = start; x < len; x += len / NUMBER_OF_POINTS)
		{
			double delta = abs(lin_interp3.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data1 << len << "		" << err << std::endl;

		std::array<double, 3> x_ch =
			chebyshev_grid<double, 3>(start, start + len);

		std::array<double, 3> y_ch;
		for (unsigned int i = 0; i < 3; i++) {
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 3> ch_interp3(x_ch, y_ch);

		err = 0;

		for (double x = start; x < len; x += len / NUMBER_OF_POINTS)
		{
			double delta = abs(ch_interp3.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data2 << len << "		" << err << std::endl;
	}

	data1.close();
	data2.close();

	//N = 4

	std::string name3 = "data4-0.txt";

	std::ofstream data3(name3);
	if (!data3) {
		std::cout << "error in " << name3 << std::endl;
		return -1;
	}
	data3.precision(10);

	std::string name4 = "data4-1.txt";

	std::ofstream data4(name4);
	if (!data4) {
		std::cout << "error in " << name4 << std::endl;
		return -1;
	}
	data4.precision(10);

	for (double len = 0.0001; len < 2; len += 0.0001)
	{
		std::array<double, 4> x_lin =
			linear_grid<double, 4>(start, start + len);

		std::array<double, 4> y_lin;
		for (unsigned int i = 0; i < 4; i++) {
			y_lin[i] = exp(x_lin[i]);
		}

		NewtonInterpolator<double, double, 4> lin_interp4(x_lin, y_lin);

		double err = 0;

		for (double x = start; x < len; x += len / NUMBER_OF_POINTS)
		{
			double delta = abs(lin_interp4.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data3 << len << "		" << err << std::endl;

		std::array<double, 4> x_ch =
			chebyshev_grid<double, 4>(start, start + len);

		std::array<double, 4> y_ch;
		for (unsigned int i = 0; i < 4; i++) {
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 4> ch_interp4(x_ch, y_ch);

		err = 0;

		for (double x = start; x < len; x += len / NUMBER_OF_POINTS)
		{
			double delta = abs(ch_interp4.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data4 << len << "		" << err << std::endl;
	}

	data3.close();
	data4.close();


	//N = 5

	std::string name5 = "data5-0.txt";

	std::ofstream data5(name5);
	if (!data5) {
		std::cout << "error in " << name5 << std::endl;
		return -1;
	}
	data5.precision(10);

	std::string name6 = "data5-1.txt";

	std::ofstream data6(name6);
	if (!data6) {
		std::cout << "error in " << name6 << std::endl;
		return -1;
	}
	data6.precision(10);

	for (double len = 0.0001; len < 2; len += 0.0001)
	{
		std::array<double, 5> x_lin =
			linear_grid<double, 5>(start, start + len);

		std::array<double, 5> y_lin;
		for (unsigned int i = 0; i < 5; i++) {
			y_lin[i] = exp(x_lin[i]);
		}

		NewtonInterpolator<double, double, 5> lin_interp5(x_lin, y_lin);

		double err = 0;

		for (double x = start; x < len; x += len / NUMBER_OF_POINTS)
		{
			double delta = abs(lin_interp5.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data5 << len << "		" << err << std::endl;

		std::array<double, 5> x_ch =
			chebyshev_grid<double, 5>(start, start + len);

		std::array<double, 5> y_ch;
		for (unsigned int i = 0; i < 5; i++) {
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 5> ch_interp5(x_ch, y_ch);

		err = 0;

		for (double x = start; x < len; x += len /NUMBER_OF_POINTS)
		{
			double delta = abs(ch_interp5.interpolate(x) - exp(x));
			err = delta > err ? delta : err;
		}

		data6 << len << "		" << err << std::endl;
	}

	data5.close();
	data6.close();
	
	return 0;
}