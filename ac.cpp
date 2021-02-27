#include <iostream>
#include <queue>

using namespace std;

struct node{
    int a;
    bool end;
    int index;
    node* fail;
    node* next[3];
}root;

const char* black[16] = {
    "11111", "011110", "011100", "001110", "011010", "010110", "11110", "01111", 
    "11011", "10111", "11101", "001100", "001010", "010100", "000100", "001000"
};
const char* white[16] = {
    "22222", "022220", "022200", "002220", "022020", "020220", "22220", "02222", 
    "22022", "20222", "22202", "002200", "002020", "020200", "000200", "002000"
};

const int scoreTable[] = {
    50000, 4320, 720, 720, 720, 720, 720, 720, 720, 720, 720,
    120, 120, 120, 20, 20
};

//建立字典树
void initTree(){
    for(int i = 0; i < 16; i++){
        node* p = &root;
        for(int j = 0; black[i][j]; j++){
            if(p->next[black[i][j] - '0'] == NULL){
                p->next[black[i][j] - '0'] = new node{black[i][j] - '0'};
            }
            p = p->next[black[i][j] - '0'];
        }
        p->end = true;
        p->index = i;
    }

    for(int i = 0; i < 16; i++){
        node* p = &root;
        for(int j = 0; white[i][j]; j++){
            if(p->next[white[i][j] - '0'] == NULL){
                p->next[white[i][j] - '0'] = new node{white[i][j] - '0'};
            }
            p = p->next[white[i][j] - '0'];
        }
        p->end = true;
        p->index = i;
    }
}

//建立fail指针
void initFail(){
    queue<node*> qu;
    for(int i = 0; i < 3; i++){
        if(root.next[i]){
            root.next[i]->fail = &root;
            qu.push(root.next[i]);
        }
    }
    while (!qu.empty()){
        node* p = qu.front();
        node* pf = p->fail;
        qu.pop();
        for(int i = 0; i < 3; i++){
            pf = p->fail;
            if(p->next[i]){
                qu.push(p->next[i]);
                while(1){
                    if(pf->next[p->next[i]->a]){
                        p->next[i]->fail = pf->next[p->next[i]->a];
                        break;
                    }
                    else if(pf == &root){
                        p->next[i]->fail = &root;
                        break;
                    }
                    else
                        pf = pf->fail;
                }
            }
        }
    }
}

int main(){
    initTree();
    initFail();

    const char* str = "00211110000000111000";
    int i = 0;
    node* p = &root;
    while(str[i]){
        while(p->next[str[i] - '0'] == NULL && p != &root) p = p->fail;
        p = p->next[str[i] - '0'];
        p = (p == NULL)? &root:p;
        node* temp = p;
        while(temp != &root && temp->end){
            temp->end = false;
            cout << scoreTable[temp->index] << endl;
            temp = temp->fail;
        }
        i++;
    }
    return 0;
}