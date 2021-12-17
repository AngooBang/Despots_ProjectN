#include "CharacterMovement.h"
#include "stdafx.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Object/Character.h"
#include "Object/TileMap.h"
#include "Util/Timer.h"



CharacterMovement::CharacterMovement(Character* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void CharacterMovement::Update()
{
	if (m_path.empty() == false)
	{
		mb_isMove = true;
		Move();
	}
	else
	{
		mb_isMove = false;
	}

	if (mb_isMove == false)
	{
		m_owner->SetState(CharacterState::Idle);
		PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);
	}
	else
	{
		m_owner->SetState(CharacterState::Run);

	}


}


void CharacterMovement::Move()
{
	int y = m_path.top().first;
	int x = m_path.top().second;


	POINT tileMapPos = GameManager::GetInstance()->GetCurrTileMap()->GetPosition();

	POINT destPoint = { tileMapPos.x + x * 15 + 7, tileMapPos.y + WALL_SIZE_Y + y * 15 + 7 };

	POINT charPos = _owner->GetPosition();

	if (x > m_owner->GetTilePos().x)
	{
		m_owner->SetDir(CharacterDir::Right);
	}
	else if (x < m_owner->GetTilePos().x)
	{
		m_owner->SetDir(CharacterDir::Left);
	}


	if (destPoint.x - 2 <= charPos.x && charPos.x <= destPoint.x + 2 && destPoint.y - 2 <= charPos.y && charPos.y <= destPoint.y + 2)
	{
		m_owner->SetTilePos({ x, y });
		m_path.pop();



		return;
	}

	float targetAngle = atan2f(
		-(destPoint.y - charPos.y),
		destPoint.x - charPos.x);


	charPos.x += cos(targetAngle) * m_speed * Timer::GetDeltaTime();
	charPos.y -= sin(targetAngle) * m_speed * Timer::GetDeltaTime();


	_owner->SetPosition(charPos);
}

void CharacterMovement::SetPath(stack<pair<int, int>> path)
{
	m_path = path;
}
