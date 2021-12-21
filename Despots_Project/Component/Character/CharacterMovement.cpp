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
	if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
	{
		//if (m_path.size() <= 2/*공격 사거리*/)
		//{
		//	while (m_path.empty() == false)
		//	{
		//		m_path.pop_back();
		//	}
		//}
	}
	if (m_path.empty() == false)
	{
		if (mb_isMove == false)
		{

			//이동전 초기값 지정구간
			PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 0);
		}
		// 도착점이 장애물이 되었을때
		if (PathFinderManager::GetInstance()->IsObstacle(m_path.front()))
		{
			PathFinderManager::GetInstance()->PathFindPoint(m_owner->GetTilePos(), m_path.front());
		}

		mb_isMove = true;
		Move();
	}
	else
	{
		mb_isMove = false;
	}

	if (mb_isMove == false)
	{
		PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);
		if (m_owner->GetState() == CharacterState::Run)
		{
			if(GameManager::GetInstance()->GetGameState() == GameState::Stanby)
				m_owner->SetState(CharacterState::Idle);
			else
				m_owner->SetState(CharacterState::Attack);

		}
	}
	else
	{
		m_owner->SetState(CharacterState::Run);

	}


}


void CharacterMovement::Move()
{
	POINT pos = m_path.back();
	//cout << m_path.size() << '\n';
	//int y = m_path.top().first;
	//int x = m_path.top().second;


	POINT tileMapPos = GameManager::GetInstance()->GetCurrTileMap()->GetPosition();

	POINT destPoint = { tileMapPos.x + pos.x * 15 + 7, tileMapPos.y + WALL_SIZE_Y + pos.y * 15 + 7 };

	POINT charPos = _owner->GetPosition();

	if (pos.x > m_owner->GetTilePos().x)
	{
		m_owner->SetDir(CharacterDir::Right);
	}
	else if (pos.x < m_owner->GetTilePos().x)
	{
		m_owner->SetDir(CharacterDir::Left);
	}


	if (destPoint.x - 2 <= charPos.x && charPos.x <= destPoint.x + 2 && destPoint.y - 2 <= charPos.y && charPos.y <= destPoint.y + 2)
	{
	//if(destPoint.x == charPos.x && destPoint.y == charPos.y)
	//{
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

	//POINT tilePos = GameManager::GetInstance()->DistPosToTilePos(charPos);

	//PathFinderManager::GetInstance()->SetInTileData(tilePos.x, tilePos.y, 0);
	
}

void CharacterMovement::SetPath(deque<POINT> path)
{
	m_path = path;
}
