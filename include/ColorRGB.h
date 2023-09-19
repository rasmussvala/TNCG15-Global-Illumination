#pragma once

class ColorRGB {
public:
	double r, g, b;

	ColorRGB(double red, double green, double blue)
		: r(red), g(green), b(blue) {}

	ColorRGB() {
		r = 0.0;
		g = 0.0;
		b = 0.0;
	}
};


