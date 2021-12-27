#include "PathFinderManager.h"
#include "Object/Tile.h"
#include "stdafx.h"
//
//int dy[] = { -1, 1,0, 0 ,-1, 1,-1,1 };
//int dx[] = { 0, 0,-1, 1 ,-1,-1, 1,1 };
int dy[] = {  0, -1, 1, -1, 1, 0,-1, 1 };
int dx[] = { -1, -1,-1,  0, 0, 1, 1, 1 };
float dg[] = { STR,DIA,DIA,STR,STR,STR,DIA,DIA };

deque<POINT> PathFinderManager::Astar(Pos start, Pos end)
{

    vector<vector<float>> f;
    for (int i = 0; i < MAP_SIZE_Y; ++i)
        f.emplace_back(MAP_SIZE_X, INF);
    f[start.Y][start.X] = 0;

    vector<vector<float>> g;
    for (int i = 0; i < MAP_SIZE_Y; ++i)
        g.emplace_back(MAP_SIZE_X, 0);


    Pos path[MAP_SIZE_Y][MAP_SIZE_X] = { NULL };
    path[start.Y][start.X] = start;

    priority_queue<pair<float, Pos>> pq;
    pq.emplace(0, start);

    while (false == pq.empty())
    {
        float w = -pq.top().first;
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

            float ng = Euclidean({ nx, ny }, pos) + g[pos.Y][pos.X];
            float nf = dg[i] + Euclidean({ nx, ny }, end) + g[pos.Y][pos.X];
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
                g[ny][nx] = ng;

                path[ny][nx] = pos;

                //cout << "path x : " << path[ny][nx].X;
                //cout << "path y : " << path[ny][nx].Y << "\n";
                //puts("");

                pq.emplace(-f[ny][nx], Pos{ nx, ny });
            }
        }
    }
    
    deque<POINT> pathStack;
    if (path[end.Y][end.X].X == NULL) // 길이 없을때
    {
        return pathStack;
    }

    Pos curr = end;
    while (curr != start)
    {
        m_mapGraph[curr.Y][curr.X] = 4;

        pathStack.push_back({curr.X, curr.Y});
        curr = path[curr.Y][curr.X];
    }

    return pathStack;
}

int PathFinderManager::Huristic_M(Pos a, Pos b)
{
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}


float PathFinderManager::Euclidean(Pos a, Pos b)
{
    return sqrtf(pow(abs(a.X - b.X), 2) + pow(abs(a.Y - b.Y), 2));
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
            else if (m_mapGraph[r][c] == 5)
                cout << "M";
        }
        cout << '\n';
    }
    puts("");
}

void PathFinderManager::ClearMap()
{
    for (int y = 0; y < MAP_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_SIZE_X; ++x)
        {
            if (m_mapGraph[y][x] != 2 /*&& m_mapGraph[y][x] != 5*/)
                m_mapGraph[y][x] = 0;
        }
    }
}


void PathFinderManager::SetInTileData(int x, int y, int value)
{

    if (INTILE[y][x] != 5)     INTILE[y][x] = value;
    if (INTILE[y - 1][x] != 5) INTILE[y - 1][x] = value;
    if (INTILE[y + 1][x] != 5) INTILE[y + 1][x] = value;
    if (INTILE[y][x - 1] != 5) INTILE[y][x - 1] = value;
    if (INTILE[y][x + 1] != 5) INTILE[y][x + 1] = value;

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


void PathFinderManager::SetInTileDataM(int x, int y, int value)
{
    INTILE[y - 2][x] = value;
    INTILE[y - 1][x - 1] = value;         INTILE[y -  1][x] = value;       INTILE[y - 1][x + 1] = value;
    INTILE[y][x - 2] = value; INTILE[y][x - 1] = value;     INTILE[y][x] = value;   INTILE[y][x + 1] = value; INTILE[y][x + 2] = value;
    INTILE[y + 1][x - 1] = value;     INTILE[y + 1][x] = value;   INTILE[y + 1][x + 1] = value;
    INTILE[y + 2][x] = value;
}

void PathFinderManager::SetInTileDataM(Tile* tile, int value)
{
    int x = tile->x;
    int y = tile->y;
                                                                                  INTILE[y * 3 - 1][x * 3 + 1] = value;
                                          INTILE[y * 3][x * 3] = value;         INTILE[y * 3][x * 3 + 1] = value;       INTILE[y * 3][x * 3 + 2] = value;
    INTILE[y * 3 + 1][x * 3 - 1] = value; INTILE[y * 3 + 1][x * 3] = value;     INTILE[y * 3 + 1][x * 3 + 1] = value;   INTILE[y * 3 + 1][x * 3 + 2] = value; INTILE[y * 3 + 1][x * 3 + 3] = value;
                                            INTILE[y * 3 + 2][x * 3] = value;     INTILE[y * 3 + 2][x * 3 + 1] = value;   INTILE[y * 3 + 2][x * 3 + 2] = value;
                                                                                 INTILE[y * 3 + 3][x * 3 + 1] = value;
}

POINT PathFinderManager::GetEndTile(POINT pos)
{
    // POINT 를 기준으로 가장 가까우면서 자리를 차지하고 있지 않은 POINT값 return
    queue<POINT> queue;
    queue.push(pos);

    // 추가처리 : 유닛이 도착지점에 가는 도중에 도착지점이 (벽, 장애물)이 될 경우 새로운 도착지점을 찾아서 길찾기를 해준다.
    // 도착지점이 움직인다면?
    // 길찾기 알고리즘은 객체가 요청할때마다
    while (queue.empty() == false)
    {
        POINT nowPos = queue.front();
        queue.pop();
        if (m_mapGraph[nowPos.y][nowPos.x] == 0)
            return nowPos;
        for (int i = 0; i < 8; ++i)
        {
            int nx = dx[i] + nowPos.x;
            int ny = dy[i] + nowPos.y;

            //if (m_mapGraph[ny][nx] == 5 || m_mapGraph[ny][nx] == 2)
            queue.push({ nx, ny });

        }
    }
    
}

bool PathFinderManager::IsObstacle(POINT pos)
{
    if (m_mapGraph[pos.y][pos.x] == 2 || m_mapGraph[pos.y][pos.x] == 5)
        return true;
    else
        return false;
}



deque<POINT> PathFinderManager::PathFind()
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

    deque<POINT> st = Astar({ startX, startY }, { endX, endY });
    if (st.empty())
    {
        // 길이 없을때 차선책을 구해야함
    }

    SetInTileData(startX, startX, 0);
    //SetInTileData(endX, endY, 2);

    //PrintMap();
    ClearMap();

    return st;
}

deque<POINT> PathFinderManager::PathFindPoint(POINT start, POINT end, bool sFloodFill, bool eFloodFill)
{

    //PathFinderManager::GetInstance()->SetInTileData(start.x, start.y, 0);
    //m_mapGraph[start.y][start.x] = 1;
    //m_mapGraph[end.y][end.x] = 3;

    // 차선책을 따로 보관을해서

    // 지금 구한 길과 차선책의 사이즈를 비교해서 더 크면 이동 X

    deque<POINT> dq;

    // 도착점 차선책설정  (flood fill Algorithm)
    //start = PathFinderManager::GetInstance()->GetEndTile(start);

    if(sFloodFill)
        start = PathFinderManager::GetInstance()->GetEndTile(start);

    if(eFloodFill)
        end = PathFinderManager::GetInstance()->GetEndTile(end);


    dq = Astar({ start.x, start.y }, { end.x, end.y });

    

    //SetInTileData(start.x, start.y, 0);

    //PrintMap();
    ClearMap();

    return dq;
}
