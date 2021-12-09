#pragma once
#include "../IBehaviour.h"
#include "../stdafx.h"
class Image2D : public IBehaviour
{
public:
	// �⺻ ������
	Image2D() = default;
	// �Ҵ� ������
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

	// Direct2D�� �⺻ render target���� ��밡���� �⺻ ��Ʈ�� ��ü
	ID2D1Bitmap* mp_bitmap = nullptr;
	// �о���� PNG �̹����� ����� ��ǥ�� ������ ���� ����
	D2D1_RECT_F m_image_rect = {};


};

