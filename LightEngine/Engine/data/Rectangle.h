#pragma once

namespace Light {
	struct Rectangle
	{
		int x, y, width, height;

		Rectangle(int x, int y, int width, int height);

		void resize(int width, int height);

		void move(int dx, int dy);
	};
}

