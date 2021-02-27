#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

string start;
string goal;
int goalPos[9];
struct node{
    string state;
    int g, h;
    bool operator<(const node& n1)const{
        if(n1.g + n1.h != g + h)
            return n1.g + n1.h > g + h;
        else if(n1.g != g)
            return n1.g > g;
        else if(n1.h != h)
            return n1.h > h;
        else
            return n1.state > state;
    }
};
map<string, bool> visit;
map<node, int> opened;
vector<node> closed;

const int dir[4] = {1, -1, 3, -3};
const int htable[9][9] = {
    0, 1, 2, 1, 2, 3, 2, 3, 4,
    1, 0, 1, 2, 1, 2, 3, 2, 3,
    2, 1, 0, 3, 2, 1, 4, 3, 2,
    1, 2, 3, 0, 1, 2, 1, 2, 3,
    2, 1, 2, 1, 0, 1, 2, 1, 2,
    3, 2, 1, 2, 1, 0, 3, 2, 1,
    2, 3, 4, 1, 2, 3, 0, 1, 2,
    3, 2, 3, 2, 1, 2, 1, 0, 1,
    4, 3, 2, 3, 2, 1, 2, 1, 0
};

bool check(string state, int g){
    if(state == goal){
        cout << g;
        return true;
    }
    return false;
}

bool expand(node& n, int g){
    if(check(n.state, g)) return true;

    int zeroind = 0;
    for(int i = 0; i < 9; i++){
        if(n.state[i] == '0'){
            zeroind = i;
            break;
        }
    }

    for(int i = 0; i < 4; i++){
        if(dir[i] == 1 && zeroind % 3 == 2) continue;
        if(dir[i] == -1 && zeroind % 3 == 0) continue;
        int ind = zeroind + dir[i];
        if(ind < 0 || ind > 8) continue;

        string expandstate = n.state;
        swap(expandstate[zeroind], expandstate[ind]);
        if(visit.count(expandstate) == 1 && visit[expandstate] == 0) continue;     //在closed表中

        int h = 0;
        for(int j = 0; j < 9; j++){
            if(expandstate[j] == '0') continue;
            h += htable[j][goalPos[expandstate[j] - '0']];
        }

        node epnode = node{expandstate, g + 1, h};
        auto point = visit.find(expandstate);
        if(point == visit.end()){         //不在open表中
            visit[expandstate] = 1;       //加入open表
            opened[epnode] = 1;
        }
        else if(visit[expandstate] == 1){           //在open表中
            auto pos = opened.end();
            for(auto j = opened.begin(); j != opened.end(); ++j){
                if(j->first.state == expandstate && j->first.g > g + 1){
                    pos = j;
                    break;
                }
            }
            if(pos != opened.end()){
                opened.erase(pos);
                opened[epnode] = 1;
            }
        }
    }
    return false;
}

void Astar(){
    opened[node{start}] = 1;
    visit[start] = 1;

    while(!opened.empty()){
        node n = opened.begin()->first;
        opened.erase(opened.begin());
        visit[n.state] = 0;        //放入close表

        //closed.push_back(n);
        if(expand(n, n.g)) break;
    }
}

int main(){
    cin >> start;
    //cin >> goal;
    goal = "123804765";
    for(int i = 0; i < 9; i++){
        goalPos[goal[i] - '0'] = i;
    }
    Astar();
    return 0;
}