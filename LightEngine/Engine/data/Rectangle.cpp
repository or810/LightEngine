#include "pch.h"
#include "Rectangle.h"

Light::Rectangle::Rectangle(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height) {
}

void Light::Rectangle::resize(int width, int height) {
	this->width = width;
	this->height = height;
}

void Light::Rectangle::move(int dx, int dy) {
	this->x += dx;
	this->y += dy;
}