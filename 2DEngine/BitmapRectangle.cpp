#include "stdafx.h"

BitmapRectangle::BitmapRectangle()
{
	this->x = 0;
	this->y = 0;
	this->height = 0;
	this->width = 0;
}

BitmapRectangle::BitmapRectangle(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}

int BitmapRectangle::GetX()
{
	return this->x;
}

int BitmapRectangle::GetY()
{
	return this->y;
}

int BitmapRectangle::GetHeight()
{
	return this->height;
}

int BitmapRectangle::GetWidth()
{
	return this->width;
}

void BitmapRectangle::SetX(int x)
{
	this->x = x;
}
void BitmapRectangle::SetY(int y)
{
	this->y = y;
}

void BitmapRectangle::SetHeight(int height)
{
	this->height = height;
}

void BitmapRectangle::SetWidth(int width)
{
	this->width = width;
}
