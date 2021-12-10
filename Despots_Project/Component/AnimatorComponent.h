#pragma once
#include "Component.h"

class Image2D;
class AnimatorComponent : public Component
{

public:
	using Component::Component; 
	virtual ~AnimatorComponent() noexcept = default;
	
	virtual void	Update() override;
	virtual void	Render() override;

	void SetImage(const wchar_t* path);
	void SetRect(RECT rect);
	void SetFrame(int frameX, int frameY);
	void SetMotionSpeed(float mSpeed);
	void SetIsLoop(bool loop);

private:
	Image2D* m_img = nullptr;
	RECT m_rect = {};

	int m_currFrameX = 0;
	int m_currFrameY = 0;
	int m_maxFrameX = 0;
	int m_maxFrameY = 0;

	int m_frameWidth = 0;
	int m_frameHeight = 0;

	float m_motionSpeed = 80.0f;
	float m_animationElapsed = 0.0f;

	bool mb_isLoop = false;
};