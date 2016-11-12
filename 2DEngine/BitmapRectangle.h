#pragma once

class BitmapRectangle
{
	public :
		int GetX();
		int GetY();
		int GetHeight();
		int GetWidth();
		void SetX(int);
		void SetY(int);
		void SetHeight(int);
		void SetWidth(int);
		BitmapRectangle::BitmapRectangle(int, int, int, int);
		BitmapRectangle::BitmapRectangle();
	private:
		int x;
		int y;
		int width;
		int height;
};