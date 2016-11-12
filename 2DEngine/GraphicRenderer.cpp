#include "stdafx.h"

GraphicRenderer::GraphicRenderer()
{
	this->backbuffer = NULL;
}

void GraphicRenderer::InitBackbuffer(int width, int height)
{
	this->backbuffer = CreateBitmap(width, height, 1, 32, NULL);
}

HBITMAP GraphicRenderer::GetBackbuffer()
{
	return this->backbuffer;
}

void GraphicRenderer::Draw(HBITMAP bmp)
{
	HBITMAP bhsrc = bmp;
	HBITMAP bhdst = this->backbuffer;
	BITMAP bm;
	GetObject(bhsrc, sizeof(bm), &bm);

	// Create DCs.  Making them compatible with 'NULL' means they are compatible with the
	//   display (which is typically good enough unless your display is running less than 32-bit
	//   color)
	HDC srcdc = CreateCompatibleDC(NULL);
	HDC dstdc = CreateCompatibleDC(NULL);

	// Put the bitmaps into the DCs.  Be sure to record the original HBITMAP for cleanup
	HBITMAP srcorig = (HBITMAP)SelectObject(srcdc, bhsrc);
	HBITMAP dstorig = (HBITMAP)SelectObject(dstdc, bhdst);

	// Blit
	BitBlt(dstdc, 0, 0, bm.bmWidth, bm.bmHeight, srcdc, 0, 0, SRCCOPY);

	// cleanup - put the original bitmaps back in the DC
	SelectObject(srcdc, srcorig);
	SelectObject(dstdc, dstorig);

	// delete the DCs we created
	DeleteDC(srcdc);
	DeleteDC(dstdc);

	//WriteBMP(this->backbuffer, L"images\\bb.bmp");
}

void GraphicRenderer::WriteBMP(HBITMAP bitmap, LPTSTR filename)
{
	HDC hDC = CreateCompatibleDC(NULL);
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD cClrBits;
	HANDLE hf; // file handle 
	BITMAPFILEHEADER hdr; // bitmap file-header 
	PBITMAPINFOHEADER pbih; // bitmap info-header 
	LPBYTE lpBits; // memory pointer 
	DWORD dwTotal; // total count of bytes 
	DWORD cb; // incremental count of bytes 
	BYTE *hp; // byte pointer 
	DWORD dwTmp;

	// create the bitmapinfo header information

	if (!GetObject(bitmap, sizeof(BITMAP), (LPSTR)&bmp))
	{
		//AfxMessageBox(L"Could not retrieve bitmap info");
		return;
	}

	// Convert the color format to a count of bits. 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;
	// Allocate memory for the BITMAPINFO structure.
	if (cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits));
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * cClrBits;
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0;

	// now open file and save the data
	pbih = (PBITMAPINFOHEADER)pbmi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) {
		//AfxMessageBox(L"writeBMP::Could not allocate memory");
		return;
	}

	// Retrieve the color table (RGBQUAD array) and the bits 
	if (!GetDIBits(hDC, HBITMAP(bitmap), 0, (WORD)pbih->biHeight, lpBits, pbmi,
		DIB_RGB_COLORS)) {
		//AfxMessageBox(L"writeBMP::GetDIB error");
		return;
	}

	// Create the .BMP file. 
	hf = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE) {
		//AfxMessageBox(L"Could not create file for writing");
		return;
	}
	hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M" 
						 // Compute the size of the entire file. 
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL)) {
		//AfxMessageBox(L"Could not write in to file");
		return;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL))) {
		//AfxMessageBox(L"Could not write in to file");
		return;
	}


	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) {
		//AfxMessageBox(L"Could not write in to file");
		return;
	}

	// Close the .BMP file. 
	if (!CloseHandle(hf)) {
		//AfxMessageBox(L"Could not close file");
		return;
	}

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);
	DeleteDC(hDC);
}