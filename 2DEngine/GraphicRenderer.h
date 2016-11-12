#pragma once

#include "stdafx.h"

class GraphicRenderer
{
	public :
		void GraphicRenderer::InitBackbuffer(int width, int height);
		void GraphicRenderer::Draw(HBITMAP);
		HBITMAP GraphicRenderer::GetBackbuffer();
		GraphicRenderer::GraphicRenderer();
		static void WriteBMP(HBITMAP bitmap, LPTSTR filename);
	private :
		HBITMAP backbuffer;
};