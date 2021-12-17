#include "Image2D.h"

void Image2D::Init(ID2D1Bitmap* bitmap, D2D1_RECT_F rect)
{
    mp_bitmap = bitmap;
    m_image_rect = rect;
}

void Image2D::Render()
{
    // 이미지가 정상적으로 읽혀져 생성되어 있다면 DrawBitmap 함수를 사용하여
    // 화면에 gp_bitmap에 저장된 이미지를 출력.
    if (mp_bitmap != NULL)
    {

        m_image_rect = { (FLOAT)m_image_rect.left - CAMERA_POS.x, (FLOAT)m_image_rect.top - CAMERA_POS.y, (FLOAT)m_image_rect.right - CAMERA_POS.x, (FLOAT)m_image_rect.bottom - CAMERA_POS.y };

        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
    else
    {
        // 이미지를 읽지 못했다면 화면이 검은색으로 출력되기 때문에 Clear 함수를
        // 사용하여 윈도우 전체 영역을 하늘색으로 채운다.
        ImageManagerD2::GetInstance()->GetRenderTarget()->Clear(ColorF(0.0f, 0.8f, 1.0f));
    }

}

void Image2D::Render(RECT rect, bool isCam)
{
    
    m_image_rect = { (FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom };
    if (isCam)
    {
        Render();
    }
    else
    {
        UNFCT_Render();
    }
}

void Image2D::UNFCT_Render()
{
    if (mp_bitmap != NULL)
    {
        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
}

void Image2D::FrameRender(RECT rect, RECT frame, POINT pos, float scale)
{

    m_image_rect = { (FLOAT)rect.left - CAMERA_POS.x, (FLOAT)rect.top - CAMERA_POS.y, (FLOAT)rect.right - CAMERA_POS.x, (FLOAT)rect.bottom - CAMERA_POS.y };
    
    D2D1_RECT_F frameRect = { (FLOAT)frame.left, (FLOAT)frame.top, (FLOAT)frame.right, (FLOAT)frame.bottom };
    ImageManagerD2::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(scale, scale,
        D2D1_POINT_2F{ (float)pos.x,(float)pos.y }));

    if (mp_bitmap != NULL)
    {
        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, frameRect);
    }

    // 사용 후 원상태로
    ImageManagerD2::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 1.0f,
        D2D1_POINT_2F{ (float)pos.x,(float)pos.y }));
}

void Image2D::FrameHReverseRender(RECT rect, RECT frame, POINT pos, float scale)
{
    ImageManagerD2::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(-scale, scale,
        D2D1_POINT_2F{ (float)pos.x,(float)pos.y }));

    m_image_rect = { (FLOAT)rect.left - CAMERA_POS.x, (FLOAT)rect.top - CAMERA_POS.y, (FLOAT)rect.right - CAMERA_POS.x, (FLOAT)rect.bottom - CAMERA_POS.y };
    D2D1_RECT_F frameRect = { (FLOAT)frame.left, (FLOAT)frame.top, (FLOAT)frame.right, (FLOAT)frame.bottom };

    if (mp_bitmap != NULL)
    {
        ImageManagerD2::GetInstance()->GetRenderTarget()->DrawBitmap(mp_bitmap, m_image_rect, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, frameRect);
    }

    // 사용 후 원상태로
    ImageManagerD2::GetInstance()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 1.0f,
        D2D1_POINT_2F{ (float)pos.x,(float)pos.y }));
}


