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
	if (m_owner->GetState() != MonsterState::Run) return;

	m_pathFindElapsed += Timer::GetDeltaTime();


	if (mb_isMove == false)
	{
		PathFinderManager::GetInstance()->SetInTileDataM(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 0);
	}


	mb_isMove = true;

	// 사거리에 들어오면
	if (m_owner->GetRangeInChar())
	{
		// 서있는 자리를 체크해서 장애물이라면
		if (PathFinderManager::GetInstance()->IsObstacle(m_owner->GetTilePos()))
		{
			// 경로를 재탐색 (시작점, 도착점 전부 FloodFill적용)
			MonsterManager::GetInstance()->FindNewPath(m_owner, true, true);
			m_pathFindElapsed = 0.0f;
		}
		else
		{
			//m_path.clear();
			mb_isMove = false;
			//PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);

			if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
				m_owner->SetState(MonsterState::Attack);
			else 
				m_owner->SetState(MonsterState::Idle);
		}
	}
	else
	{
		// 사거리에 적이 없는데
		// 검사를 일정시간마다.
		if (m_pathFindElapsed > 1.0f)
		{
			if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
			{
				MonsterManager::GetInstance()->FindNewPath(m_owner);
			}
			m_pathFindElapsed = 0.0f;
		}
	}
	if (m_path.empty() == false && mb_isMove)
	{
		Move();
	}
	else
	{
		mb_isMove = false;
		PathFinderManager::GetInstance()->SetInTileDataM(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 5);
		if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
			m_owner->SetState(MonsterState::Attack);
		else 
			m_owner->SetState(MonsterState::Idle);
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
