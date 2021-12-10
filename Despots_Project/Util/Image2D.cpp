#include "Image2D.h"

void Image2D::Init(ID2D1Bitmap* bitmap, D2D1_RECT_F rect)
{
    mp_bitmap = bitmap;
    m_image_rect = rect;
}

void Image2D::Render()
{
    // �̹����� ���������� ������ �����Ǿ� �ִٸ� DrawBitmap �Լ��� ����Ͽ�
    // ȭ�鿡 gp_bitmap�� ����� �̹����� ���.
    if (mp_bitmap != NULL)
    {
        //D2ImageManager::GetSingleton()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 0, 0, 60, 330 });

        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
    else
    {
        // �̹����� ���� ���ߴٸ� ȭ���� ���������� ��µǱ� ������ Clear �Լ���
        // ����Ͽ� ������ ��ü ������ �ϴû����� ä���.
        ImageManagerD2::GetInstance()->GetRenderTarget()->Clear(ColorF(0.0f, 0.8f, 1.0f));
    }

}

void Image2D::Render(RECT rect)
{
    m_image_rect = { (FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom };
    Render();
}

void Image2D::FrameRender(RECT rect, RECT frame)
{
    m_image_rect = { (FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom };
    D2D1_RECT_F frameRect = { frame.left, frame.top, frame.right, frame.bottom };
    if (mp_bitmap != NULL)
    {
        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRect);
    }
}


