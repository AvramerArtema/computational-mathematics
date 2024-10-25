#pragma once
#include <vector>
#include<iostream>
#include <type_traits>

template <typename RealType>
std::vector<RealType> grid(const RealType first, const RealType last, const unsigned int N)
{
    std::vector<RealType> grid_points;
    double h = (last - first) / (N - 1);

    grid_points.push_back(first);
    for (unsigned int i = 0; i < N - 1; i++)
    {
        grid_points.push_back(grid_points[i] + h);
    }
    return grid_points;
};

template<typename Type>
class ThreeDiagonalMatrix
{
private:
    std::vector<Type>up_diag;
    std::vector<Type>diag;
    std::vector<Type>down_diag;
public:
    ThreeDiagonalMatrix(const std::vector<Type> h)
    {
        const unsigned int N = h.size();

        diag.push_back(2);
        up_diag.push_back(h[1] / (h[0] + h[1]));
        for (unsigned int i = 1; i < N - 2; i++)
        {
            diag.push_back(2);
            up_diag.push_back(h[i + 1] / (h[i] + h[i + 1]));
            down_diag.push_back(h[i] / (h[i] + h[i + 1]));
        }
        diag.push_back(2);
        down_diag.push_back(h[N - 2] / (3 * (h[N - 2] + h[N - 1])));
    }

    Type operator() (const unsigned int i, const unsigned int j) const
    {
        if (i - j == 0)
        {
            return diag[i];
        }
        else if (i - j == 1)
        {
            return up_diag[j];
        }
        else if (i - j == -1)
        {
            return down_diag[i];
        }
        else
        {
            throw "Element is out of daiogonals";
            return 42;
        };
    };
};

template<typename xType, typename yType>
std::vector<yType> devided_diffrences(const std::vector<xType>& h, const std::vector<yType>& values)
{
    const unsigned int N = h.size();
    std::vector<yType> dev_dif;

    for (unsigned int i = 1; i < N; i++)
    {
        dev_dif.push_back(6 * (values[i + 1] * h[i - 1] - values[i] * (h[i] + h[i - 1]) + values[i - 1] * h[i]) / (h[i] * h[i - 1] * (h[i] + h[i - 1])));
    }

    return dev_dif;
}

template<typename numeratorType, typename denominatorType>
using DivisType = decltype(std::declval<numeratorType>() / std::declval<denominatorType>());

template<typename Type>
using DiffType = decltype(std::declval<Type>() - std::declval<Type>());

template<typename mType, typename cType>
std::vector<DivisType<cType, mType>> solve(const ThreeDiagonalMatrix<mType>& matrix, const std::vector<cType>& column)
{
    const unsigned int N = column.size();

    std::vector<mType> p{ (-1) * matrix(0, 1) / matrix(0,0) };
    std::vector<mType> q{ column[0] / matrix(0, 0) };

    std::vector<DivisType<cType, mType>> c_vector(N + 2);

    for (unsigned int i = 1; i < N - 1; i++)
    {
        p.push_back((-1) * matrix(i, i + 1) / (matrix(i, i - 1) * p[i - 1] + matrix(i, i)));
        q.push_back((column[i] - matrix(i, i - 1) * q[i - 1]) / (matrix(i, i - 1) * p[i - 1] + matrix(i, i)));
    }

    c_vector[0] = 0;
    c_vector[N + 1] = 0;
    c_vector[N] = (column[N - 1] - matrix(N - 1, N - 2) * q[N - 2]) / (matrix(N - 1, N - 2) * p[N - 2] + matrix(N - 1, N - 1));
    for (unsigned int i = N - 1; i > 0; i--)
    {
        c_vector[i] = c_vector[i + 1] * p[i - 1] + q[i - 1];
    }

    return c_vector;
};

template<typename xType, typename yType>
class CubicSpline
{
private:
    std::vector<xType> points;
    std::vector<yType> a;
    std::vector<yType> b;
    std::vector<yType> c;
    std::vector<yType> d;

public:
    CubicSpline(const std::vector<xType>& points, const std::vector<yType>& values) :
        points{ points }
    {
        const unsigned int N = points.size() - 1;

        std::vector<xType>h;

        for (unsigned int i = 0; i < points.size() - 1; i++)
        {
            h.push_back(points[i + 1] - points[i]);
        }

        std::vector<yType> column = devided_diffrences<double, double>(h, values);
        c = solve(ThreeDiagonalMatrix<double>(h), column);

        for (unsigned int i = 0; i < N; i++)
        {
            a.push_back(values[i + 1]);
            b.push_back(c[i + 1] * h[i] / 3 + c[i] * h[i] / 6 + (values[i + 1] - values[i]) / h[i]);
            d.push_back((c[i + 1] - c[i]) / h[i]);
        }
    };

    yType interpolate(const xType& x) const noexcept
    {

        yType y;
        unsigned int k = 1;
        while (x - points[k] > 0.001)
        {
            k++;
        }

        y = a[k - 1] + b[k - 1] * (x - points[k]) + c[k] * (x - points[k]) / 2 * (x - points[k]) + d[k - 1] * (x - points[k]) * (x - points[k]) * (x - points[k]) / 6;
        return y;
    };
};