/*
#pragma once
#ifndef _TEXT_H                // Prevent multiple definitions if this 
#define _TEXT_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"
#include "graphics.h"

class TextDX
{
private:
	float angle;
	float color;

public:
	int print(const std::string &str, int x, int y);
	int print(const std::string &str, RECT &rect, UINT format);
	
	bool initialize(Graphics *g, int height, bool bold, bool italic, const std::string & fontName);

	INT DrawText(
		LPD3DXSPRITE pSprite,
		LPCTSTR pString,
		INT Count,
		LPRECT pRect,
		DWORD Format,
		D3DCOLOR Color
	);

	HRESULT D3DXCreateFont(
		LPDIRECT3DDEVICE9 pDevice,
		INT Height,
		UINT Width,
		UINT Weight,
		UINT MipLevels,
		BOOL Italic,
		DWORD CharSet,
		DWORD OutputPrecision,
		DWORD Quality,
		DWORD PitchAndFamily,
		LPCTSTR pFacename,
		LPD3DXFONT *ppFont
	);

	float getDegrees() { return angle * (180.0f / (float)PI); }
	float getRadians() { return angle; }
	float getFontColor() { return color; }
	float setDegrees(float deg) { angle = deg * ((float)PI / 180.0f); }
	float setRadians(float rad) { angle = rad; }
	float setFontColor(COLOR_ARGB C) { color = C; }
};
#endif
*/