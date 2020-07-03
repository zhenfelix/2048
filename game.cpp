#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#ifdef _MSC_VER

const string kClearCommand = "CLS";

#else

const string kClearCommand = "clear";

#endif

const int row = 4, col = 4;

int board[row][col];
int dc[] = {1,0,-1,0};
int dr[] = {0,1,0,-1};
int start[] = {col-1,row-1,0,0};
int delta[] = {-1,-1,1,1};
char cmdMap[128];
void boardMove() ;

void initGame()
{
    cmdMap['d'] = 0;
    cmdMap['s'] = 1;
    cmdMap['a'] = 2;
    cmdMap['w'] = 3;
    boardMove();
}

void newGame(){
    memset(board,0,sizeof(board));
}

void boardMove(){
    while (true)
    {
        int pos = rand()%(row*col);
        int c = pos%col, r = pos/row;
        if (board[r][c] == 0)
        {
            board[r][c] = 2;
            break;
        }
        
    }
    
}

bool valid(int i,int j){
    return i>=0&&i<row&&j>=0&&j<col;
}

bool slideRow(int dirPos){
    bool change = false;
    for (int c = 0; c < col; c++)
    {
        int slow = start[dirPos], fast = start[dirPos];
        while (valid(fast,c))
        {
            while(valid(fast,c)&&board[fast][c]==0)fast+=delta[dirPos];
            if(valid(fast,c)&&fast!=slow){
                board[slow][c] = board[fast][c];
                board[fast][c] = 0;
                change = true;
            }
            slow+=delta[dirPos];
            fast+=delta[dirPos];
        }
        
    }
    return change;
}

void mergeRow(int dirPos){
    for (int c = 0; c < col; c++)
    {
        int cur = start[dirPos];
        while (valid(cur+delta[dirPos], c))
        {
            if (board[cur][c]>0&&board[cur][c]==board[cur+delta[dirPos]][c])        
            {
                board[cur][c] *= 2;
                board[cur+delta[dirPos]][c] = 0;
            }
            cur += delta[dirPos];
        }
    }
}

bool slideCol(int dirPos)
{
    bool change = false;
    for (int r = 0; r < row; r++)
    {
        int slow = start[dirPos], fast = start[dirPos];
        while (valid(r, fast))
        {
            while (valid(r, fast) && board[r][fast] == 0)
                fast += delta[dirPos];
            if (valid(r, fast)&&fast!=slow){
                board[r][slow] = board[r][fast];
                board[r][fast] = 0;
                change = true;
            }
            slow += delta[dirPos];
            fast += delta[dirPos];
        }
    }
    return change;
}

void mergeCol(int dirPos)
{
    for (int r = 0; r < row; r++)
    {
        int cur = start[dirPos];
        while (valid(r,cur + delta[dirPos]))
        {
            if (board[r][cur] > 0 && board[r][cur] == board[r][cur + delta[dirPos]])
            {
                board[r][cur] *= 2;
                board[r][cur + delta[dirPos]] = 0;
            }
            cur += delta[dirPos];
        }
    }
}

bool chessMove(int dirPos){
    bool change = false;
    if(dirPos&1){
        change = slideRow(dirPos) || change;
        mergeRow(dirPos);
        change = slideRow(dirPos) || change;
    }
    else{
        change = slideCol(dirPos) || change;
        mergeCol(dirPos);
        change = slideCol(dirPos) || change;
    }
    return change;
}

void printUI(){
    system(kClearCommand.c_str());
    for (int i = 0; i < row; i++)
    {
        if(1)
            
        {
            for (int j = 0; j < col; j++)printf("-%-10s", "");
            printf("\n");
        }
        
        for (int j = 0; j < col; j++)
        {
            if(1)cout << "|";
            if (board[i][j] == 0)
            {
                printf("%-10s","");
            }
            else{
                printf("%-10d",board[i][j]);
            }
            
        }
        printf("\n\n\n");
        
    }
    cout << "n: new game, w: up, s: down, d: right, a: left, q: quit\n";
    
}


int main(){
    srand(2020);
    initGame();
    while (true)
    {
        // boardMove();
        printUI();
        char cmd;
        cin >> cmd;
        if (cmd=='n')
        {
            newGame();
        }
        else if(cmd=='q'){
            break;
        }
        else{
            int dirPos = cmdMap[cmd];
            if (!chessMove(dirPos))continue;
            // cout << dirPos << dc[dirPos] << dr[dirPos] << endl;
        }
        boardMove();
    }
    return 0;
}