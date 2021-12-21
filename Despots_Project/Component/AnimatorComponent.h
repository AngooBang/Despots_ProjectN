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
	void SetCurrFrame(int frameX);
	void SetIsReverse(bool isReverse);
	void SetIsVisible(bool isVisible);
	void SetScale(float scale);
	void SetIsCam(bool isCam);
	void SetEndAni(bool endAni);
	void SetHorizontalReverse(bool reverse);

	bool GetIsVisible();
	bool GetEndAni();
	bool GetIsReverse();

	void ChangeImg(const wchar_t* path, int maxFrameX, int maxFrameY, int currFrameX);
	

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

	float m_scale = 1.0f;



	bool mb_isVisible = true;
	bool mb_isLoop = false;
	bool mb_isReverse = false;
	bool mb_isCam = true;
	bool mb_horizontalReverse = NULL;
	bool mb_endAni = false;


	bool mb_isLastFrameSub = false;
};