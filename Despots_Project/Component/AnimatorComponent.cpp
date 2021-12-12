#include "stdafx.h"
#include "AnimatorComponent.h"
#include "Util/Image2D.h"
#include "Util/Timer.h"

void AnimatorComponent::Update()
{
	m_animationElapsed += Timer::GetDeltaTime();
	if (m_animationElapsed >= m_motionSpeed)
	{
		++m_currFrameX;
		if (m_currFrameX >= m_maxFrameX)
		{
			if (mb_isLoop)
			{
				m_currFrameX = 0;
			}
			else
			{
				--m_currFrameX;
			}
		}
		m_animationElapsed = 0.0f;
	}
}

void AnimatorComponent::DownFrame()
{
	m_animationElapsed += Timer::GetDeltaTime();
	if (m_animationElapsed >= m_motionSpeed)
	{
		--m_currFrameX;
		if (m_currFrameX < 0)
		{
			if (mb_isLoop)
			{
				m_currFrameX = m_maxFrameX;
			}
			else
			{
				++m_currFrameX;
			}
		}
		m_animationElapsed = 0.0f;
	}
}

void AnimatorComponent::Render()
{
	RECT frameRect = { m_frameWidth * m_currFrameX,
						m_frameHeight * m_currFrameY,
						m_frameWidth * (m_currFrameX + 1),
						m_frameHeight * (m_currFrameY + 1) };
	m_img->FrameRender(m_rect, frameRect);
}



void AnimatorComponent::SetImage(const wchar_t* path)
{
	m_img = FIND_IMG(path);
}

void AnimatorComponent::SetRect(RECT rect)
{
	m_rect = rect;
}

void AnimatorComponent::SetFrame(int frameX, int frameY)
{
	m_maxFrameX = frameX;
	m_maxFrameY = frameY;

	m_frameWidth = m_img->GetWidth() / m_maxFrameX;
	m_frameHeight = m_img->GetHeight() / m_maxFrameY;
}

void AnimatorComponent::SetMotionSpeed(float mSpeed)
{
	m_motionSpeed = mSpeed;
}

void AnimatorComponent::SetIsLoop(bool loop)
{
	mb_isLoop = loop;
}

void AnimatorComponent::SetCurrFrame(int frameX)
{
	m_currFrameX = frameX;
}

void AnimatorComponent::ChangeImg(const wchar_t* path, int maxFrameX, int maxFrameY, int currFrameX)
{
	m_img = FIND_IMG(path);
	m_maxFrameX = maxFrameX;
	m_maxFrameY = maxFrameY;

	m_frameWidth = m_img->GetWidth() / m_maxFrameX;
	m_frameHeight = m_img->GetHeight() / m_maxFrameY;

	m_currFrameX = currFrameX;
}
