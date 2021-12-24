#include "MonsterMovement.h"
#include "stdafx.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/MonsterManager.h"
#include "Object/Monster.h"
#include "Object/TileMap.h"
#include "Util/Timer.h"

MonsterMovement::MonsterMovement(Monster* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}


void MonsterMovement::Update()
{
	if (m_path.empty() == false)
	{
		if (mb_isMove == false)
		{
			//이동전 초기값 지정구간
			PathFinderManager::GetInstance()->SetInTileDataM(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 0);
		}
		// 도착점이 장애물이 되었을때
		if (PathFinderManager::GetInstance()->IsObstacle(m_path.front()))
		{
			MonsterManager::GetInstance()->FindNewPath(m_owner);
		}

		mb_isMove = true;
		m_owner->SetState(MonsterState::Run);
		Move();

		// 타겟이 움직였다면 길찾기 다시
		if (m_owner->GetTarget()->GetIsMove() && GameManager::GetInstance()->GetGameState() == GameState::Battle)
		{
			MonsterManager::GetInstance()->FindNewPath(m_owner);
		}

		// 원거리캐릭들은 사거리가 되면 멈춤
		if (m_owner->GetMType() == MonsterType::Dalek)
		{
			if (m_owner->GetRangeInChar() && GameManager::GetInstance()->GetGameState() == GameState::Battle)
			{
				m_path.clear();
			}
		}
	}
	else
	{
		if (PathFinderManager::GetInstance()->IsObstacle(m_owner->GetTilePos()) && mb_isMove)
		{
			MonsterManager::GetInstance()->FindNewPath(m_owner);
			return;
		}
		mb_isMove = false;
		PathFinderManager::GetInstance()->SetInTileDataM(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 5);
		if (m_owner->GetRangeInChar())
		{
			m_owner->SetState(MonsterState::Attack);
		}
		else
		{
			if (GameManager::GetInstance()->GetGameState() == GameState::Battle && m_owner->GetState() == MonsterState::Idle)
				MonsterManager::GetInstance()->FindNewPath(m_owner);
			else if (GameManager::GetInstance()->GetGameState() == GameState::Stanby && m_owner->GetState() == MonsterState::Run)
				m_owner->SetState(MonsterState::Idle);
		}
	}
}

void MonsterMovement::Move()
{
	POINT pos = m_path.back();

	POINT tileMapPos = GameManager::GetInstance()->GetCurrTileMap()->GetPosition();

	POINT destPoint = { tileMapPos.x + pos.x * 15 + 7, tileMapPos.y + WALL_SIZE_Y + pos.y * 15 + 7 };

	POINT charPos = _owner->GetPosition();

	if (pos.x > m_owner->GetTilePos().x)
	{
		m_owner->SetDir(MonsterDir::Right);
	}
	else if (pos.x < m_owner->GetTilePos().x)
	{
		m_owner->SetDir(MonsterDir::Left);
	}


	if (destPoint.x - 2 <= charPos.x && charPos.x <= destPoint.x + 2 && destPoint.y - 2 <= charPos.y && charPos.y <= destPoint.y + 2)
	{
		m_owner->SetTilePos({ pos.x, pos.y });
		m_path.pop_back();
		return;
	}

	float targetAngle = atan2f(
		-(destPoint.y - charPos.y),
		destPoint.x - charPos.x);


	charPos.x += cos(targetAngle) * m_speed * Timer::GetDeltaTime();
	charPos.y -= sin(targetAngle) * m_speed * Timer::GetDeltaTime();


	_owner->SetPosition(charPos);

}

void MonsterMovement::SetPath(deque<POINT> path)
{
	m_path = path;
}

void MonsterMovement::SetIsMove(bool isMove)
{
	mb_isMove = isMove;
}

bool MonsterMovement::GetIsMove()
{
	return mb_isMove;
}
