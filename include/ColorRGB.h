#pragma once

class ColorRGB {
 public:
  double r, g, b;

  ColorRGB(double red, double green, double blue);
  ColorRGB();

  ColorRGB& operator+=(const ColorRGB& other);
  ColorRGB operator+(const ColorRGB& other) const;

  ColorRGB& operator-=(const ColorRGB& other);
  ColorRGB operator-(const ColorRGB& other) const;

  ColorRGB& operator*=(const ColorRGB& other);
  ColorRGB operator*(const ColorRGB& other) const;

  ColorRGB& operator*=(double scalar);
  ColorRGB operator*(double scalar) const;

  ColorRGB& operator/=(double scalar);
  ColorRGB operator/(double scalar) const;

  friend ColorRGB operator*(double scalar, const ColorRGB& color);
};
