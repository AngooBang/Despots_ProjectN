#pragma once
#include "stdafx.h"
#include "Util/Singleton.h"

class Image2D;
class ImageManagerD2 : public Singleton<ImageManagerD2>
{
public:
	void Init(HWND& _hWnd);
	void Release();

	void AddImageList();
	int AddImage(const wchar_t* path, D2D1_RECT_F rect = {});

	Image2D* FindImage(const wchar_t* path);



	inline ID2D1HwndRenderTarget* GetRenderTarget() { return mp_render_target; }

private:
	map<wstring, Image2D*> mapImages;

	ID2D1Factory* mp_factory = nullptr;

	ID2D1HwndRenderTarget* mp_render_target = nullptr;

	IWICImagingFactory* m_pImageFactory = nullptr;

	ID2D1Bitmap* mp_bitmap = nullptr;
};

