#include<iostream>
#include<cmath>
#include<iomanip>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;


double myabs(double x)
{
	if (x < 0)
		return -x;
	else
		return x;
}


double mysqrt(double A)
{
	double x0 = A + 0.25;
	double x1;
	double xx = x0;
	for (;;) {
		x1 = (x0 * x0 + A) / (2 * x0);
		if (myabs(x1 - x0) <= DBL_EPSILON) break;
		if (xx == x1) 
			return x0;
		xx = x0;
		x0 = x1;
	}
	return x1;
}

double Taylor(double x, int m)
{
	double x1;
	x1 = myabs(x);
	x1 = x1 - (int)(x1 / 2 / M_PI) * 2 * M_PI;
	if (x < 0)
		x = -x1;
	else
		x = x1;

	double num = x;
	double den = 1.0;
	double result = num;
	for (int i = 1; ; i++)
	{
		double tmp;
		num *= x * x;
		tmp = double(i);
		den *= -2 * tmp * (2 * tmp + 1.0);
		result += num / den;
		if (myabs(num / den) < 5e-6)
			break;
	}
	return result;
}

double Euler(double x)
{
	double x1, y_, y, y1, ylast, y2;
	double theta, theta1, theta2;
	double N = 1000;
	double h;

	theta = myabs(x) * 360/ (2 * M_PI);
	theta -= int(theta / 360) * 360;
	if (theta >= 270)
	{
		theta1 = 360 - theta;
	}
	else if (theta >= 180)
	{
		theta1 = theta - 180;
	}
	else if (theta >= 90)
		theta1 = 180 - theta;
	else
		theta1 = theta;

	if (theta1 >= 45)
		theta2 = 90 - theta1;
	else
		theta2 = theta1;


	x1 = theta2 / 360 * 2 * M_PI;

	ylast = 0.0;
	y = ylast;
	h = x1 / N;
	for (int i = 0; i < N; i++)
	{
		y_ = ylast + h * mysqrt(1 - ylast * ylast);
		y = ylast + h / 2 * (mysqrt(1 - ylast * ylast) + mysqrt(1 - y_ * y_));
		ylast = y;
	}
	
	if (theta1 >= 45)
		y2 = mysqrt(1 - y * y);
	else
		y2 = y;
	
	if (theta >= 180)
		y1 = -y2;
	else
		y1 = y2;

	if (x > 0)
		return y1;
	else
		return -y1;
}


int main()
{
	int m = 4;
	int c;
	string ans = "y";
	double x;

	while (ans == "y")
	{
		cout << "please enter x:" << endl;
		cin >> x;
		cout << "please choose mode, 1 for Taylor and 2 for Euler :" << endl;
		cin >> c;

		if (c == 1)
			cout << std::fixed << std::setprecision(m) << Taylor(x, m) << endl;
		else if(c == 2)
			cout << std::fixed << std::setprecision(m) << Euler(x) << endl;
		else
			cout << "wrong choice!" << endl;

		cout << "want to try again? y for yes and n for no" << endl;
		cin >> ans;
	}
	cout << "bye" << endl;

	return 0;

}