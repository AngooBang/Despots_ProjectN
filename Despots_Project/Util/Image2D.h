#pragma once
#include "IBehaviour.h"
#include "stdafx.h"
class Image2D : public IBehaviour
{
public:
	// �⺻ ������
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

	// Direct2D�� �⺻ render target���� ��밡���� �⺻ ��Ʈ�� ��ü
	ID2D1Bitmap* mp_bitmap = nullptr;
	// �о���� PNG �̹����� ����� ��ǥ�� ������ ���� ����
	D2D1_RECT_F m_image_rect = {};


};

