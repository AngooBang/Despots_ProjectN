#include "ImageManagerD2.h"
#include "Util/Image2D.h"


void ImageManagerD2::Init(HWND& _hWnd)
{
    RECT r;
    GetClientRect(_hWnd, &r);

    // D2D1Factory 생성
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

    // 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target을 생성.
    mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
        HwndRenderTargetProperties(_hWnd, SizeU(r.right, r.bottom)),
        &mp_render_target);

    // WICImagingFactory 생성
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
        // erase에서 리턴값으로 it의 다음 iterator를 돌려주게됨. 계속 대입해서 반복시킴
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
    // 기존에 읽은 이미지가 있으면 해당 이미지를 제거
    //if (mp_bitmap != NULL)
    //{
    //    mp_bitmap->Release();
    //    mp_bitmap = NULL;
    //}

    wstring str = path;
    if (mapImages.find(str) != mapImages.end())
    {
        // 이미 있는거임
        return -1;
    }

    Image2D* img = new Image2D;

    // 압축된 이미지를 해제할 객체
    IWICBitmapDecoder* p_decoder;
    // 특정 그림을 선택한 객체
    IWICBitmapFrameDecode* p_frame;
    // 이미지 변환 객체
    IWICFormatConverter* p_converter;
    // 그림 파일을 읽은 결과 값 (0이면 그림 읽기 실패, 1이면 그림 읽기 성공)
    int result = 0;
    // WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
    if (S_OK == mp_ImageFactory->CreateDecoderFromFilename(path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder)) {
        // 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
        if (S_OK == p_decoder->GetFrame(0, &p_frame))
        {
            // IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
            if (S_OK == mp_ImageFactory->CreateFormatConverter(&p_converter))
            {
                // 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
                if (S_OK == p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
                {
                    // IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
                    if (S_OK == mp_render_target->CreateBitmapFromWicBitmap(p_converter, NULL, &mp_bitmap))
                    {
                        img->Init(mp_bitmap, rect);
                        mapImages.insert(make_pair(path, img));
                        result = 1;
                    }  // 성공적으로 생성한 경우
                }
                // 이미지 변환 객체 제거
                p_converter->Release();
            }
            // 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
            p_frame->Release();
        }
        // 압축을 해제하기 위해 생성한 객체 제거
        p_decoder->Release();
    }
    //// WIC를 사용하기 위해 만들었던 Factory 객체 제거
    //m_pImageFactory->Release();

    return result;  // PNG 파일을 읽은 결과를 반환한다.

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