#include <iostream>
#include <cmath>
#include <../fparser.hh>
#include <complex>
#include <math.h>
#define _USE_MATH_DEFINES

const double pi = 4 * atan(1), dt = 0.005;
FunctionParser_cd fp;

std::complex<double> change(std::complex<double> temp, double a, int place) {
	double x, y;
	if (place == 1) {
		x = temp.real() - a;
		y = temp.imag() + a;
	}
	else if (place == 2) {
		x = temp.real() + a;
		y = temp.imag() + a;
	}
	else if (place == 3) {
		x = temp.real() + a;
		y = temp.imag() - a;
	}
	else {
		x = temp.real() - a;
		y = temp.imag() - a;
	}
	temp = { x, y };
	return(temp);
}

int curves_order(std::complex<double> z0, double a)
{
	double x0 = z0.real();
	double y0 = z0.imag();
	double angle_temp, sum = 0;
	std::complex<double>z, f, temp = 0;
	for (double t = dt; t < 2 * pi; t += dt) {
		z = { x0 + a / 2 * cos(t), y0 + a / 2 * sin(t) };
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
	return(round(sum / (2 * pi)));
}
int main()
{
	double a, x0, y0, eps;
	std::string function;
	std::complex<double>z;

	std::cout << "a, x0, y0, eps" << std::endl;
	std::cin >> a >> x0 >> y0 >> eps;
	std::cout << "f(z)=";
	std::cin >> function;
	fp.Parse(function, "z");

	for (int i = 1; a > 2 * eps; i %= 4) {
		a /= 2;
		if (curves_order(change(z, a, i), a) >= 1) {
			x0 = z.real();
			y0 = z.imag();
		}
	}
	std::cout << z;

	return 0;
}
