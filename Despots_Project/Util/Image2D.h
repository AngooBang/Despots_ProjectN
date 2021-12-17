#pragma once
#include "IBehaviour.h"
#include "stdafx.h"
class Image2D : public IBehaviour
{
public:
	// 기본 생성자
	Image2D() = default;

	virtual void Init(ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
	virtual void Render() override;
	virtual void Render(RECT rect, bool isCam = true);
	void UNFCT_Render();

	void FrameRender(RECT rect, RECT frame, POINT pos = {}, float scale = 1.0f);
	void FrameHReverseRender(RECT rect, RECT frame, POINT pos = {}, float scale = 1.0f);

	inline void SetImageRect(D2D1_RECT_F rect) { m_image_rect = rect; }

	inline int GetWidth() { return (INT)mp_bitmap->GetSize().width; }
	inline int GetHeight() { return (INT)mp_bitmap->GetSize().height; }

private:

	// Direct2D의 기본 render target에서 사용가능한 기본 비트맵 객체
	ID2D1Bitmap* mp_bitmap = nullptr;
	// 읽어들인 PNG 이미지를 출력할 좌표를 저장할 변수 선언
	D2D1_RECT_F m_image_rect = {};


};

