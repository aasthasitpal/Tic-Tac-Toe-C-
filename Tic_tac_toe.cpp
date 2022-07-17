#include<bits/stdc++.h>

using namespace std;

#define Computer 1
#define Human 2
#define side 3
#define Computermove 'O'
#define Humanmove 'X'

void showBoard(char board[][side]){

    cout<<"   "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"   "<<"---------"<<endl;
    cout<<"   "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"   "<<"---------"<<endl;
    cout<<"   "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
    cout<<"   "<<"---------"<<endl;
}

void showInstructions(){ 

    cout<<endl<<"Choose a cell numbered from 1 to 9 as below and play"<<endl<<endl;
    cout<<"   "<<" 1 | 2 | 3 "<<endl;
    cout<<"   "<<"-----------"<<endl;
    cout<<"   "<<" 4 | 5 | 6 "<<endl;
    cout<<"   "<<"-----------"<<endl;
    cout<<"   "<<" 7 | 8 | 9 "<<endl;
    cout<<"   "<<"-----------"<<endl;
}

void initialise(char board[][side]){

    // Initializing all entries of board as "*"
    for (int i=0; i<side; i++){
        for (int j=0; j<side; j++)
        board[i][j] = '*';
    }
}

void declareWinner(int whoseTurn){

    if (whoseTurn == Computer)
    printf("Computer has won\n");
    else
    printf("Human has won\n");
}

bool rowCrossed(char board[][side]){

    for (int i=0; i<side; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&  board[i][0] != '*')
        return true;
    }
    return false;
}

bool columnCrossed(char board[][side]){

    for (int i=0; i<side; i++){
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&  board[0][i] != '*')
        return true;
    }
    return false;
}

bool diagonalCrossed(char board[][side]){

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;

    return false;

}

bool gameOver(char board[][side]){

    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

int minimax(char board[][side], int depth, bool isAI){

    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true){
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else{
        if(depth < 9){
            if(isAI == true){
                bestScore = -999;
                for(int i=0; i<side; i++){
                    for(int j=0; j<side; j++){
                        if (board[i][j] == '*'){
                            board[i][j] = Computermove;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if(score > bestScore){
                                bestScore = score;
                            }
                        }
                    }
                }
            return bestScore;
            }
            else{
                bestScore = 999;
                for (int i = 0; i < side; i++){
                    for (int j = 0; j < side; j++){
                        if (board[i][j] == '*'){
                            board[i][j] = Humanmove;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore){
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        return 0;
    }
    return 0;
}

int bestmove(char board[][side], int moveIndex){
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < side; i++){
        for (int j = 0; j < side; j++) {
            if (board[i][j] == '*'){
                board[i][j] = Computermove;
                score = minimax(board, moveIndex+1, false);
                board[i][j] = '*';
                if(score > bestScore){
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}


void playTicTacToe(int whoseTurn){

    char board[side][side];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstructions();

    while (gameOver(board) == false && moveIndex != side*side){
        int n;
        if (whoseTurn == Computer){
            n = bestmove(board, moveIndex);
            x = n / side;
            y = n % side;
            board[x][y] = Computermove;
            cout<<"Computer has put a "<<Computermove<<" in cell "<<n+1<<endl<<endl;
            showBoard(board);
            moveIndex ++;
            whoseTurn = Human;
        }
        else if (whoseTurn == Human){
            cout<<"You can insert in the following positions : ";
            for(int i=0; i<side; i++){
                for (int j = 0; j < side; j++){
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
                }
            }
            cout<<endl<<endl<<"Enter the position = ";
            cin>>n;
            n--;
            x = n / side;
            y = n % side;
            if(board[x][y] == '*' && n<9 && n>=0){
                board[x][y] = Humanmove;
                cout<<endl<<"Human has put a "<<Humanmove<<" in cell "<<n+1<<endl<<endl;
                showBoard(board);
                moveIndex ++;
                whoseTurn = Computer;
            }
            else if(board[x][y] != '*' && n<9 && n>=0){
                cout<<endl<<"Position is occupied, select any one place from the available places"<<endl;
            }
            else if(n<0 || n>8){
                cout<<"Invalid position"<<endl;
            }
        }
    }
    if (gameOver(board) == false && moveIndex == side * side)
        cout<<"It's a draw";
    else{
        if (whoseTurn == Computer)
            whoseTurn = Human;
        else if (whoseTurn == Human)
            whoseTurn = Computer;
        declareWinner(whoseTurn);
    }
}


int main(){
    cout<<endl<<"*******************************************************************"<<endl<<endl;
    cout<<"                       "<<"Tic-Tac-Toe"<<endl;
    cout<<endl<<"*******************************************************************"<<endl<<endl;

    char cont='y';
    do {
        char choice;
        cout<<"Do you want to start first?(y/n) : ";
        cin>>choice;
        
        if(choice=='n')
            playTicTacToe(Computer);
        else if(choice=='y')
            playTicTacToe(Human);
        else
            cout<<"Invalid choice"<<endl;
            
        cout<<endl<<endl<<"Do you want to quit(y/n) : ";
        cin>>cont;
    } 
    while(cont=='n');
    return (0);
}