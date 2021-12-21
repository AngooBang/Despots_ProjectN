#include "stdafx.h"
#include "AnimatorComponent.h"
#include "Object/GameObject.h"
#include "Util/Image2D.h"
#include "Util/Timer.h"

void AnimatorComponent::Update()
{
	if (GetStopUpdate()) return;
	if (mb_isReverse == false)
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
					if (mb_isLastFrameSub)
					{
						mb_endAni = true;
						mb_isLastFrameSub = false;
					}

					mb_isLastFrameSub = true;
					--m_currFrameX;
				}
			}
			m_animationElapsed = 0.0f;
		}
	}
	else
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
					if (mb_isLastFrameSub)
					{
						mb_endAni = true;
						mb_isLastFrameSub = false;
					}

					mb_isLastFrameSub = true;
					++m_currFrameX;
				}
			}
			m_animationElapsed = 0.0f;
		}
	}
}

void AnimatorComponent::Render()
{
	if (mb_isVisible == false) return;

	RECT frameRect = { m_frameWidth * m_currFrameX,
						m_frameHeight * m_currFrameY,
						m_frameWidth * (m_currFrameX + 1),
						m_frameHeight * (m_currFrameY + 1) };
	if (mb_horizontalReverse == false)
	{
		//cout << "¿À¸¥ÂÊ º½" << '\n';
			m_img->FrameRender(m_rect, frameRect, GetOwner()->GetPosition(), m_scale);
	}
	else
	{
		//cout << "¿ÞÂÊ º½" << '\n';
			m_img->FrameHReverseRender(m_rect, frameRect, GetOwner()->GetPosition(), m_scale);
	}

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

void AnimatorComponent::SetIsReverse(bool isReverse)
{
	mb_isReverse = isReverse;
}

void AnimatorComponent::SetIsVisible(bool isVisible)
{
	mb_isVisible = isVisible;
}

void AnimatorComponent::SetScale(float scale)
{
	m_scale = scale;
}

void AnimatorComponent::SetIsCam(bool isCam)
{
	mb_isCam = isCam;
}

void AnimatorComponent::SetEndAni(bool endAni)
{
	mb_endAni = endAni;
}

void AnimatorComponent::SetHorizontalReverse(bool reverse)
{
	mb_horizontalReverse = reverse;
}

bool AnimatorComponent::GetIsVisible()
{
	return mb_isVisible;
}

bool AnimatorComponent::GetEndAni()
{
	return mb_endAni;
}

bool AnimatorComponent::GetIsReverse()
{
	return mb_isReverse;
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
