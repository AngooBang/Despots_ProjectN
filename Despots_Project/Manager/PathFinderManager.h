#pragma once
#include <Windows.h>
#include <queue>
#include <vector>
#include <string>
#include <stack>
#include "../Util/Singleton.h"

#define INF 987654321
#define MAP_SIZE_X 60
#define MAP_SIZE_Y 27

#define DIA 1.4f
#define STR 1.0f

using namespace std;


// 경로가 찾아지지 않을때 (벽,장애물 무시)처리
// 길찾기를 했는데, 도착지에 다른애가 있을때
struct Pos
{
    int X;
    int Y;

    bool operator<(const Pos& other) const { return (X < other.X) && (Y < other.Y); }
    bool operator==(const Pos& other) const { return X == other.X && Y == other.Y; }
    bool operator!=(const Pos& other) const { return !(*this == other); }
};

//struct POINT;
class Tile;
class PathFinderManager : public Singleton<PathFinderManager>
{
public:

    deque<POINT> Astar(Pos start, Pos end);

    int Huristic_M(Pos a, Pos b);

    float Euclidean(Pos a, Pos b);

    void PrintMap();
    void ClearMap();

    void SetInTileData(int x, int y, int value);
    void SetInTileData(Tile* tile, int value);

    void SetInTileDataM(Tile* tile, int value);
    POINT GetEndTile(POINT pos);

    bool IsObstacle(POINT pos);
    

    deque<POINT> PathFind();
    deque<POINT> PathFindPoint(POINT start, POINT end);

	int m_mapGraph[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };
private:

};