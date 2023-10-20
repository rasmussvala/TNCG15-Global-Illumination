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

	// Overloaded += 
	ColorRGB& operator+=(const ColorRGB& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}

	// Overloaded + 
	ColorRGB& operator+(const ColorRGB& other) {
		r + other.r;
		g + other.g;
		b + other.b;
		return *this;
	}

	// Overloaded *= 
	ColorRGB& operator*=(const ColorRGB& other) {
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}

	// Overloaded *: ColorRGB * scalar
	ColorRGB operator*(double scalar) const {
		return ColorRGB(r * scalar, g * scalar, b * scalar);
	}

	// Overloaded *: scalar * ColorRGB
	friend ColorRGB operator*(double scalar, const ColorRGB& color) {
		return ColorRGB(color.r * scalar, color.g * scalar, color.b * scalar);
	}
};


