#include "funcs.h"
#include<fstream>
#include<cmath>

int main()
{
    const double first = 0;
    const double last = 10;

    std::ofstream data("data.txt");
    data.precision(15);

    for (unsigned int N = 5; N < 160; N++)
    {
        std::vector<double> points = grid<double>(first, last, N);
        std::vector<double> values;
        for (unsigned int i = 0; i < N; i++)
        {
            values.push_back(exp(points[i]));
        }

        CubicSpline<double, double> sp(points, values);

        double epsilon = 0;
        for (double x = first; x < last; x += last / 1000)
        {

            double delta = abs(sp.interpolate(x) - exp(x));
            if (delta > epsilon)
            {
                epsilon = delta;
            }
        }

        data << log(N) << "    " << log(epsilon) << std::endl;
    }
    data.close();

    return 0;
}