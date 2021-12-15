#include "ImageManagerD2.h"
#include "Util/Image2D.h"


void ImageManagerD2::Init(HWND& _hWnd)
{
    RECT r;
    GetClientRect(_hWnd, &r);

    // D2D1Factory ����
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

    // ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target�� ����.
    mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
        HwndRenderTargetProperties(_hWnd, SizeU(r.right, r.bottom)),
        &mp_render_target);

    // WICImagingFactory ����
    if (S_OK == CoInitialize(NULL))
    {

    }
    if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, NULL,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mp_ImageFactory)))
    {

    }
    //__uuidof(IDWriteFactory),
    //    reinterpret_cast<IUnknown**>(&pDWriteFactory_)
    if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(mp_WriteFactory),
        reinterpret_cast<IUnknown**>(&mp_WriteFactory)))
    {
    }

    AddImageList();
}

void ImageManagerD2::Release()
{
    if (mp_render_target != NULL)
    {
        mp_render_target->Release();
        mp_render_target = NULL;
    }

    map<wstring, Image2D*>::iterator it;
    for (it = mapImages.begin(); it != mapImages.end();)
    {
        // erase���� ���ϰ����� it�� ���� iterator�� �����ְԵ�. ��� �����ؼ� �ݺ���Ŵ
        it = mapImages.erase(it);
    }

}

void ImageManagerD2::AddImageList()
{

    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/BackGround.bmp");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/Despot_Logo.bmp");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/Start_Hover.png");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/Start_Active.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/Exit_Hover.png");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Title/Exit_Active.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Wall.bmp");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Bottom.bmp");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Ground_0.bmp");


    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Left_Door.png");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Up_Open.png");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Right_Door.png");
    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/Down_Reveal.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Map/MoveFrame.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Character/Normal/Normal_Idle.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/InterFace/SelectBox.png");

    ImageManagerD2::GetInstance()->AddImage(L"Image/Character/Selected.png");

}

int ImageManagerD2::AddImage(const wchar_t* path, D2D1_RECT_F rect)
{
    // ������ ���� �̹����� ������ �ش� �̹����� ����
    //if (mp_bitmap != NULL)
    //{
    //    mp_bitmap->Release();
    //    mp_bitmap = NULL;
    //}

    wstring str = path;
    if (mapImages.find(str) != mapImages.end())
    {
        // �̹� �ִ°���
        return -1;
    }

    Image2D* img = new Image2D;

    // ����� �̹����� ������ ��ü
    IWICBitmapDecoder* p_decoder;
    // Ư�� �׸��� ������ ��ü
    IWICBitmapFrameDecode* p_frame;
    // �̹��� ��ȯ ��ü
    IWICFormatConverter* p_converter;
    // �׸� ������ ���� ��� �� (0�̸� �׸� �б� ����, 1�̸� �׸� �б� ����)
    int result = 0;
    // WIC�� Factory ��ü�� ����Ͽ� �̹��� ���� ������ ���� ��ü�� ����
    if (S_OK == mp_ImageFactory->CreateDecoderFromFilename(path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder)) {
        // ������ �����ϴ� �̹��� �߿��� ù��° �̹����� �����Ѵ�.
        if (S_OK == p_decoder->GetFrame(0, &p_frame))
        {
            // IWICBitmap������ ��Ʈ���� ID2D1Bitmap. �������� ��ȯ�ϱ� ���� ��ü ����
            if (S_OK == mp_ImageFactory->CreateFormatConverter(&p_converter))
            {
                // ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ ����
                if (S_OK == p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
                {
                    // IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� ����
                    if (S_OK == mp_render_target->CreateBitmapFromWicBitmap(p_converter, NULL, &mp_bitmap))
                    {
                        img->Init(mp_bitmap, rect);
                        mapImages.insert(make_pair(path, img));
                        result = 1;
                    }  // ���������� ������ ���
                }
                // �̹��� ��ȯ ��ü ����
                p_converter->Release();
            }
            // �׸����Ͽ� �ִ� �̹����� �����ϱ� ���� ����� ��ü ����
            p_frame->Release();
        }
        // ������ �����ϱ� ���� ������ ��ü ����
        p_decoder->Release();
    }
    //// WIC�� ����ϱ� ���� ������� Factory ��ü ����
    //m_pImageFactory->Release();

    return result;  // PNG ������ ���� ����� ��ȯ�Ѵ�.

}

Image2D* ImageManagerD2::FindImage(const wchar_t* path)
{
    map<wstring, Image2D*>::iterator it = mapImages.find(path);
    if (it == mapImages.end())
    {
        return nullptr;
    }
    return it->second;
}