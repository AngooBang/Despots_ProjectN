#include "PathFinderManager.h"
#include "Object/Tile.h"
#include "stdafx.h"

stack<pair<int, int>> PathFinderManager::Astar(Pos start, Pos end)
{

    vector<vector<int>> f;
    for (int i = 0; i < MAP_SIZE_Y; ++i)
        f.emplace_back(MAP_SIZE_X, INF);
    f[start.Y][start.X] = 0;

    Pos path[MAP_SIZE_Y][MAP_SIZE_X];
    path[start.Y][start.X] = start;

    priority_queue<pair<int, Pos>> pq;
    pq.emplace(0, start);

    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dg[] = { 10, 14, 10, 14, 10, 14, 10, 14 };

    while (false == pq.empty())
    {
        int w = -pq.top().first;
        Pos pos = pq.top().second;
        pq.pop();

        if (f[pos.Y][pos.X] < w)
        {
            continue;
        }

        if (pos == end)
        {
            break;
        }

        for (int i = 0; i < 8; ++i)
        {
            int ny = dy[i] + pos.Y;
            int nx = dx[i] + pos.X;

            if (ny < 0 || ny >= MAP_SIZE_Y || nx < 0 || nx >= MAP_SIZE_X)
            {
                continue;
            }

            if (!(m_mapGraph[ny][nx] == 0 || m_mapGraph[ny][nx] == 3))
            {
                continue;
            }

            int nf = dg[i] + Huristic_M({ nx, ny }, end);
            //cout << "\n";
            //cout << "nx : "<< nx << "\n";
            //cout << "end.x : " << end.X << "\n";
            //cout << "ny : " << ny << "\n";
            //cout << "end.y : " << end.Y << "\n";
            //cout << "h : " << h << "\n";
            //cout << "nf : " << nf << "\n";

            if (f[ny][nx] > nf)
            {
                f[ny][nx] = nf;

                path[ny][nx] = pos;

                //cout << "path x : " << path[ny][nx].X << "\n";
                //cout << "path y : " << path[ny][nx].Y << "\n";

                pq.emplace(-f[ny][nx], Pos{ nx, ny });
            }
        }
    }
    
    stack<pair<int, int>> pathStack;
    Pos curr = end;
    while (curr != start)
    {
        m_mapGraph[curr.Y][curr.X] = 4;

        pathStack.push(make_pair(curr.Y, curr.X));
        curr = path[curr.Y][curr.X];
    }

    return pathStack;
}

int PathFinderManager::Huristic_M(Pos a, Pos b)
{
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}



void PathFinderManager::PrintMap()
{
    for (int r = 0; r < MAP_SIZE_Y; ++r)
    {
        for (int c = 0; c < MAP_SIZE_X; ++c)
        {
            if (m_mapGraph[r][c] == 0)
                cout << " ";
            else if (m_mapGraph[r][c] == 1)
                cout << "S";
            else if (m_mapGraph[r][c] == 2)
                cout << "B";
            else if (m_mapGraph[r][c] == 3)
                cout << "E";
            else if (m_mapGraph[r][c] == 4)
                cout << "P";
        }
        cout << endl;
    }
    puts("");
}

void PathFinderManager::ClearMap()
{
    for (int y = 0; y < MAP_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_SIZE_X; ++x)
        {
            if (m_mapGraph[y][x] != 2)
                m_mapGraph[y][x] = 0;
        }
    }
}

void PathFinderManager::SetInTileData(Tile* tile, int value)
{
    int x = tile->x;
    int y = tile->y;
    INTILE[y * 3][x * 3 + 1] = value;
    INTILE[y * 3 + 1][x * 3] = value;
    INTILE[y * 3 + 1][x * 3 + 1] = value;
    INTILE[y * 3 + 1][x * 3 + 2] = value;
    INTILE[y * 3 + 2][x * 3 + 1] = value;
}

void PathFinderManager::SetInTileData(int x, int y, int value)
{

    INTILE[y][x] = value;
    INTILE[y - 1][x] = value;
    INTILE[y + 1][x] = value;
    INTILE[y][x - 1] = value;
    INTILE[y][x + 1] = value;

}

stack<pair<int, int>> PathFinderManager::PathFind()
{
    int startY = 0;
    int startX = 0;
    int endY = 0;
    int endX = 0;
    for (int y = 0; y < MAP_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_SIZE_X; ++x)
        {
            if (m_mapGraph[y][x] == 1)
            {
                startY = y;
                startX = x;
            }
            if (m_mapGraph[y][x] == 3)
            {
                endY = y;
                endX = x;
            }
            if (startY != 0 && startX != 0 && endY != 0 && endX != 0)
                break;
        }
    }

    stack<pair<int, int>> st = Astar({ startX, startY }, { endX, endY });

    //PrintMap();
    ClearMap();

    return st;
}
