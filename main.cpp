#include <QCoreApplication>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "index.h"

using namespace std;

class NodeMap
{
public:
    int d;
    int name;
    NodeMap *parent;
};

bool isexisted(int &temp, vector<int> &list);

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    int i, j;
    int dist;
    int temp = V;
    int min, MinPoint;
    int map[PointNum][PointNum] = {0};
    NodeMap MinMap[PointNum] = {0};
    vector<int> CheckList, UncheckList;

    map[A][B] = 12;
    map[A][C] = map[A][D] = map[A][E] = INF;
    map[A][F] = 16;
    map[A][G] = 14;

    map[B][C] = 10;
    map[B][D] = map[B][E] = map[B][G] = INF;
    map[B][F] = 7;

    map[C][D] = 3;
    map[C][E] = 5;
    map[C][F] = 6;
    map[C][G] = INF;

    map[D][E] = 4;
    map[D][F] = map[D][G] = INF;

    map[E][F] = 2;
    map[E][G] = 8;

    map[F][G] = 9;

    for(i = 1; i < PointNum; i++)
    {
        for(j = 0; j < i; j++)
            map[i][j] = map[j][i];
    }

    for(i = 0; i < PointNum; i++)
    {

        min = INF;

         //Search all the nodes connected directly to V(start) point
        //Record the distance between them
        if(i == 0)
        {
            for(j = 0; j < PointNum; j++)
            {
                MinMap[j].d = map[temp][j];
                if(j != temp)
                MinMap[j].parent = &MinMap[temp];
                MinMap[j].name = j;

                if(map[temp][j] < min && temp != j)
                {
                    min = map[temp][j];
                    MinPoint = j;
                }
            }

            CheckList.push_back(temp);
            temp = MinPoint;  //*********
        }
        //Choose temp to be the next node.Search all the nodes connected directly to temp.
        //If the distance from a node to V via temp is shorter than previous minimum distance
        //from node to V, then refresh the distance.
        else
        {
            for(j = 0; j < PointNum; j++)
            {
                if(!isexisted(j, CheckList))
                {
                    dist = map[temp][j];
                    if(MinMap[temp].d + dist < MinMap[j].d)
                    {
                        MinMap[j].d = MinMap[temp].d + dist;
                        MinMap[j].parent = &MinMap[temp];
                    }

                    if(MinMap[j].d < min)
                    {
                        min = MinMap[j].d;
                        MinPoint = j;
                    }
                }

            }
            CheckList.push_back(temp);
            temp = MinPoint;
        }


    }

    for(i = 0; i < PointNum; i++)
    {
        NodeMap *node = &MinMap[i];
        cout << "Min Dist " << char('A' + V) << "," << char('A' + i) << " ";
        cout << MinMap[i].d << "  ";

        cout << "Path: ";

        while(node != NULL)
        {
            usleep(1000);
            cout << char('A' + node->name) << " ";
            node = node->parent;
        }
        cout << endl;
    }

    return 0;
}

bool isexisted(int &temp, vector<int> &list)
{
    vector<int>::iterator result;
    result = find(list.begin(), list.end(), temp);
    if(result == list.end())
        return 0;
    else
        return 1;
}
