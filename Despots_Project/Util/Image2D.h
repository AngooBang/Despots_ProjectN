#pragma once
#include "../IBehaviour.h"
#include "../stdafx.h"
class Image2D : public IBehaviour
{
public:
	// 기본 생성자
	Image2D() = default;
	// 할당 연산자
	//Image2D& operator=(const Image2D& rhs)
	//{
	//	if (this != &rhs)
	//	{
	//		Image2D temp(rhs);
	//		std::swap(mp_bitmap, temp.mp_bitmap);
	//		std::swap(m_image_rect, temp.m_image_rect);
	//	}

	//	return *this;
	//}
	virtual void Init(ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
	virtual void Render() override;
	virtual void Render(RECT rect);
	void FrameRender(D2D1_RECT_F rect, D2D1_RECT_F frame);

	inline void SetImageRect(D2D1_RECT_F rect) { m_image_rect = rect; }

	inline int GetWidth() { return mp_bitmap->GetSize().width; }
	inline int GetHeight() { return mp_bitmap->GetSize().height; }

private:

	// Direct2D의 기본 render target에서 사용가능한 기본 비트맵 객체
	ID2D1Bitmap* mp_bitmap = nullptr;
	// 읽어들인 PNG 이미지를 출력할 좌표를 저장할 변수 선언
	D2D1_RECT_F m_image_rect = {};


};

