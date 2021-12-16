#pragma once
#include <vector>
#include <string>
#include <stack>
#include "../Util/Singleton.h"

#define INF 987654321
#define MAP_SIZE_X 60
#define MAP_SIZE_Y 27

using namespace std;

struct Pos
{
    int X;
    int Y;

    bool operator<(const Pos& other) const { return (X < other.X) && (Y < other.Y); }
    bool operator==(const Pos& other) const { return X == other.X && Y == other.Y; }
    bool operator!=(const Pos& other) const { return !(*this == other); }
};

class Tile;
class PathFinderManager : public Singleton<PathFinderManager>
{
public:

    stack<pair<int, int>> Astar(Pos start, Pos end);

    int Huristic_M(Pos a, Pos b);

    void PrintMap();
    void ClearMap();

    void SetInTileData(int x, int y, int value);
    void SetInTileData(Tile* tile, int value);
    
    stack<pair<int, int>> PathFind();

	int m_mapGraph[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };
private:

};