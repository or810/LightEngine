#pragma once
namespace Light {

	struct Vec2
	{
        float X, Y, Z;

        inline Vec2(void) { X = 0; Y = 0; Z = 0; }
        inline Vec2(const float x, const float y, const float z)
        {
            X = x; Y = y; Z = z;
        }

        inline Vec2 operator + (Vec2& A) {
            return Vec2(X + A.X, Y + A.Y, Z + A.Z);
        }

        inline Vec2 operator + (const Vec2& A) const
        {
            return Vec2(X + A.X, Y + A.Y, Z + A.Z);
        }

        inline Vec2 operator + (const float A) const
        {
            return Vec2(X + A, Y + A, Z + A);
        }

        inline float Dot(const Vec2& A) const
        {
            return A.X * X + A.Y * Y + A.Z * Z;
        }
	};
}

