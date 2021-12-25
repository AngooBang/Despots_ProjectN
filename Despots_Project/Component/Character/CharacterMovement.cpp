#include "CharacterMovement.h"
#include "stdafx.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/CharacterManager.h"
#include "Object/Character.h"
#include "Object/Monster.h"
#include "Object/TileMap.h"
#include "Util/Timer.h"



CharacterMovement::CharacterMovement(Character* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void CharacterMovement::Update()
{
	if (m_owner->GetState() != CharacterState::Run) return;

	m_pathFindElapsed += Timer::GetDeltaTime();


	if (mb_isMove == false)
	{
		PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 0);
	}


	mb_isMove = true;

	// 사거리에 들어오면
	if (m_owner->GetIsRangeInMon())
	{
		// 서있는 자리를 체크해서 장애물이라면
		if (PathFinderManager::GetInstance()->IsObstacle(m_owner->GetTilePos()))
		{
			// 경로를 재탐색 (시작점, 도착점 전부 FloodFill적용)
			CharacterManager::GetInstance()->FindNewPath(m_owner, true, true);
			m_pathFindElapsed = 0.0f;
		}
		else
		{
			//m_path.clear();
			mb_isMove = false;
			//PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);

			if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
				m_owner->SetState(CharacterState::Attack);
			else if (GameManager::GetInstance()->GetGameState() == GameState::Stanby)
				m_owner->SetState(CharacterState::Idle);
		}
	}
	else
	{
		// 사거리에 적이 없는데
		// 검사를 일정시간마다.
		if (m_pathFindElapsed > 1.0f)
		{
			if ( GameManager::GetInstance()->GetGameState() == GameState::Battle)
			{
				CharacterManager::GetInstance()->FindNewPath(m_owner);
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
		PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);
		if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
			m_owner->SetState(CharacterState::Attack);
		else if (GameManager::GetInstance()->GetGameState() == GameState::Stanby)
			m_owner->SetState(CharacterState::Idle);
	}
	//if (m_path.empty() == false)
	//{
	//	if (mb_isMove == false)
	//	{
	//		//이동전 초기값 지정구간
	//		PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 0);
	//	}
	//	// 도착점이 장애물이 되었을때
	//	if (m_owner->GetCType() == CharacterType::Normal || m_owner->GetCType() == CharacterType::GutSword || m_owner->GetCType() == CharacterType::Shield)
	//	{
	//		if (PathFinderManager::GetInstance()->IsObstacle(m_path.front()))
	//		{
	//			m_path.clear();
	//			cout << "도착지점이 장애물일때 길찾기 실행" << '\n';
	//			CharacterManager::GetInstance()->FindNewPath(m_owner);
	//		}
	//	}

	//	mb_isMove = true;
	//	m_owner->SetState(CharacterState::Run);
	//	Move();

	//	// 타겟이 움직였다면 길찾기 다시
	//	if (m_pathFindElapsed > 1.0f)
	//	{
	//		if (m_owner->GetTarget() != nullptr)
	//		{
	//			if (/*m_owner->GetTarget()->GetState() == MonsterState::Run && */GameManager::GetInstance()->GetGameState() == GameState::Battle)
	//			{
	//				m_path.clear();
	//				//cout << "타겟의 상태가 Run 이고 전투중일때 길찾기 실행" << '\n';
	//				CharacterManager::GetInstance()->FindNewPath(m_owner);
	//			}
	//		}
	//		m_pathFindElapsed = 0.0f;
	//	}

	//	// 원거리캐릭들은 사거리가 되면 멈춤
	//	if (m_owner->GetCType() == CharacterType::Crossbow || m_owner->GetCType() == CharacterType::Ring)
	//	{
	//		if (m_owner->GetIsRangeInMon() && GameManager::GetInstance()->GetGameState() == GameState::Battle)
	//		{
	//			m_path.clear();
	//		}
	//	}
	//}
	//else
	//{	
	//	mb_isMove = false;
	//	PathFinderManager::GetInstance()->SetInTileData(m_owner->GetTilePos().x, m_owner->GetTilePos().y, 2);
	//	if (m_owner->GetIsRangeInMon())
	//	{
	//		m_owner->SetState(CharacterState::Attack);			
	//	}
	//	else /*if(m_owner->GetState() != CharacterState::Attack)*/
	//	{
	//		if (GameManager::GetInstance()->GetGameState() == GameState::Battle/* && m_owner->GetState() == CharacterState::Idle*/)
	//		{
	//			m_path.clear();
	//			cout << "전투중에 사거리내에 적이없고 Idle상태가 됐을때 새로운 패스 찾기 실행" << '\n';
	//			CharacterManager::GetInstance()->FindNewPath(m_owner);
	//		}
	//		else if (GameManager::GetInstance()->GetGameState() == GameState::Stanby && m_owner->GetState() == CharacterState::Run)
	//			m_owner->SetState(CharacterState::Idle);
	//	}
	//	if (PathFinderManager::GetInstance()->IsObstacle(m_owner->GetTilePos()) && mb_isMove)
	//	{
	//		m_path.clear();
	//		cout << "내 자리가 장애물일때 새로운 패스 찾기 실행" << '\n';
	//		CharacterManager::GetInstance()->FindNewPath(m_owner);
	//		return;
	//	}
	//}
}


void CharacterMovement::Move()
{
	POINT pos = m_path.back();

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

void CharacterMovement::SetPath(deque<POINT> path)
{
	m_path = path;
}

void CharacterMovement::SetIsMove(bool isMove)
{
	mb_isMove = isMove;
}

bool CharacterMovement::GetIsMove()
{
	return mb_isMove;
}
