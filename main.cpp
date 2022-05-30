#include <iostream>
#include <cmath>
#include <../fparser.hh>
#include <complex>
#include<vector>
#define _USE_MATH_DEFINES

const double pi = 4 * atan(1), dt = 0.005;
FunctionParser_cd fp;

int curves_order(double x0, double y0, double a)
{
	double angle_temp, sum = 0, p;
	std::complex<double>z, f, temp;
	for (double t = dt; t < 2 * pi; t += dt) {
		p = std::max(abs(cos(t)), abs(sin(t)));
		z = { x0 + a * cos(t) / p, y0 + a * sin(t) / p };
		f = fp.Eval(&z);
		angle_temp = abs(std::arg(f) - std::arg(temp));
		if (angle_temp > pi) {
			angle_temp = 2 * pi - angle_temp;
		}
		if (temp.imag() * f.real() > temp.real() * f.imag()) {
			angle_temp *= -1;
		}
		sum += angle_temp;
		temp = f;
	}
	return round(sum / (2 * pi));
}
void FindRoots(double a, double eps, double x0, double y0, std::vector<std::complex<double>> &roots)
{
	double sum = 0;
	if (curves_order(x0, y0, a) >= 1)
	{
		if (a < eps)
		{
			bool is_find = false;
			for (auto el : roots)
			{
				if (fabsl(real(el) - x0) <= 2 * eps && fabsl(imag(el) - y0) <= 2 * eps)
				{
					is_find = true;
					break;
				}
			}
			if (!is_find)
				roots.emplace_back(round(x0 / eps) * eps, round(y0 / eps) * eps);
		}
		else
		{
			FindRoots(a / 2 + eps / 4, eps, x0 + a / 2, y0 + a / 2, roots);
			FindRoots(a / 2 + eps / 4, eps, x0 + a / 2, y0 - a / 2, roots);
			FindRoots(a / 2 + eps / 4, eps, x0 - a / 2, y0 + a / 2, roots);
			FindRoots(a / 2 + eps / 4, eps, x0 - a / 2, y0 - a / 2, roots);
		}
	}
}

void find_complex_roots(double a, double x0, double y0, double eps, std::string function)
{
	fp.Parse(function, "z");
	std::complex<double>z = { x0, y0 };
	std::vector<std::complex<double>> roots;
	FindRoots(a, eps, x0, y0, roots);
	for (int i = 0; i < roots.size(); i++) {
		std::cout << roots[i]<<std::endl;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, x0, y0, eps;
	std::string function;
	std::cout << "Радиус ";
	std::cin >> a;
	std::cout <<"Начальная координата ";
	std::cin >> x0 >> y0;
	std::cout << "Точность ";
	std::cin >> eps;
	std::cout << "Функция F(z) = ";
	std::cin >> function;
	find_complex_roots(a, x0, y0, eps, function);
	return 0;
}
