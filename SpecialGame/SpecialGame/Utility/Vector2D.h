#pragma once

class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D() :x(0.0f), y(0.0f) {};
	Vector2D(float scalar) :x(scalar), y(scalar) {};
	Vector2D(float mx, float my) :x(mx), y(my) {};
	~Vector2D() = default;

	void operator=(const Vector2D& location);
	void operator+=(const Vector2D& location);
	void operator-=(const Vector2D& location);
	void operator*=(const Vector2D& location);

	void operator=(float scalar);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);

	const Vector2D operator+(const Vector2D& location);
	const Vector2D operator-(const Vector2D& location);
	const Vector2D operator*(const Vector2D& location);

	void ToInt(int* x, int* y);
};