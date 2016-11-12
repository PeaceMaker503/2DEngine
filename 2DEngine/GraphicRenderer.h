#pragma once

#include "stdafx.h"
#include "BitmapRectangle.h"

class GraphicRenderer
{
	public :
		void GraphicRenderer::InitBackbuffer(int width, int height);
		void GraphicRenderer::Draw(HBITMAP, BitmapRectangle rect);
		HBITMAP GraphicRenderer::GetBackbuffer();
		GraphicRenderer::GraphicRenderer();
		static void WriteBMP(HBITMAP bitmap, LPTSTR filename);
	private :
		HBITMAP backbuffer;
};