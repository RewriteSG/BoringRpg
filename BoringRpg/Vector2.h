#pragma once
class Vector2
{
	int x, y;
public:
	Vector2();
	Vector2(int _x, int _y);
	int GetX() const;
	int GetY() const;
	void SetXandY(int _x, int _y);
	static int Distance(const Vector2& pos1, const Vector2& pos2);
	static void Clamp(int& value, const int& max, const int& min);
	static void Clamp(Vector2& value, const Vector2& max, const Vector2& min);
	Vector2& operator-=(const Vector2& scalar);
	Vector2 operator-(const Vector2& scalar) const;
	Vector2& operator+=(const Vector2& scalar);
	Vector2& operator/=(const Vector2& scalar);
	Vector2& operator*=(const Vector2& scalar);
	Vector2& operator*=(const int& scalar);
	Vector2& operator=(const Vector2& scalar);
	Vector2 operator+ (const Vector2& scalar)const;
	bool operator==(const Vector2& scalar);
	bool operator!=(const Vector2& scalar);
	//bool operator!=(const Vector2 scalar);

};

