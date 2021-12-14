#pragma once
#include "Component.h"

class Image2D;
class ImageComponent : public Component
{
public:
	using Component::Component;
	virtual ~ImageComponent() noexcept = default;

	virtual void	Render() override;


	int GetWidth();
	int GetHeight();

	void SetImage(const wchar_t* path);
	void SetRect(RECT rect);
	void SetIsVisible(bool isVisible);
	void SetIsCam(bool isCam);
	

private:
	Image2D* m_img = nullptr;
	RECT m_rect = {};

	bool mb_isCam = true;
	bool mb_isVisible = true;
};