#pragma once
#include "Component.h"

class Image2D;
class ImageComponent : public Component
{
public:
	using Component::Component;
	virtual ~ImageComponent() noexcept = default;

	virtual void	Render() override;

	void SetImage(const wchar_t* path);
	void SetRect(RECT rect);

private:
	Image2D* m_img = nullptr;
	RECT m_rect = {};
};