#include <math>
#include <cmath>
#pragma once
namespace Light {

	//struct Vec2
	//{
 //       float X, Y, Z;

 //       inline Vec2(void) { X = 0; Y = 0; Z = 0; }
 //       inline Vec2(const float x, const float y)
 //       {
 //           X = x; Y = y; Z = z;
 //       }

 //       inline Vec2 operator + (Vec2& A) {
 //           return Vec2(X + A.X, Y + A.Y, Z + A.Z);
 //       }

 //       inline Vec2 operator + (const Vec2& A) const
 //       {
 //           return Vec2(X + A.X, Y + A.Y, Z + A.Z);
 //       }

 //       inline Vec2 operator + (const float A) const
 //       {
 //           return Vec2(X + A, Y + A, Z + A);
 //       }

 //       inline float Dot(const Vec2& A) const
 //       {
 //           return A.X * X + A.Y * Y + A.Z * Z;
 //       }
	//};


	template <class T>
	class vec2 {
	public:
		T x, y;

		vec2() :x(0), y(0) {}
		vec2(T x, T y) : x(x), y(y) {}
		vec2(const vec2& v) : x(v.x), y(v.y) {}

		vec2& operator=(const vec2& v) {
			x = v.x;
			y = v.y;
			return *this;
		}

		vec2 operator+(vec2& v) {
			return vec2(x + v.x, y + v.y);
		}
		vec2 operator-(vec2& v) {
			return vec2(x - v.x, y - v.y);
		}

		vec2& operator+=(vec2& v) {
			x += v.x;
			y += v.y;
			return *this;
		}
		vec2& operator-=(vec2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		vec2 operator+(double s) {
			return vec2(x + s, y + s);
		}
		vec2 operator-(double s) {
			return vec2(x - s, y - s);
		}
		vec2 operator*(double s) {
			return vec2(x * s, y * s);
		}
		vec2 operator/(double s) {
			return vec2(x / s, y / s);
		}


		vec2& operator+=(double s) {
			x += s;
			y += s;
			return *this;
		}
		vec2& operator-=(double s) {
			x -= s;
			y -= s;
			return *this;
		}
		vec2& operator*=(double s) {
			x *= s;
			y *= s;
			return *this;
		}
		vec2& operator/=(double s) {
			x /= s;
			y /= s;
			return *this;
		}

		void set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		void rotate(double deg) {
			double theta = deg / 180.0 * M_PI;
			double c = cos(theta);
			double s = sin(theta);
			double tx = x * c - y * s;
			
			double ty = x * s + y * c;
			x = tx;
			y = ty;
		}

		vec2& normalize() {
			if (length() == 0) return *this;
			*this *= (1.0 / length());
			return *this;
		}

		float dist(vec2 v) const {
			vec2 d(v.x - x, v.y - y);
			return d.length();
		}
		float length() const {
			return std::sqrt(x * x + y * y);
		}
		void truncate(double length) {
			double angle = atan2f(y, x);
			x = length * cos(angle);
			y = length * sin(angle);
		}

		vec2 ortho() const {
			return vec2(y, -x);
		}

		static float dot(vec2 v1, vec2 v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}
		static float cross(vec2 v1, vec2 v2) {
			return (v1.x * v2.y) - (v1.y * v2.x);
		}

	};

	typedef vec2<float> vec2f;
	typedef vec2<double> vec2d;


}

