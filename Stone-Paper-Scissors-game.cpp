#include <iostream>
#include<math.h>
#include <cstdlib>
using namespace std;
enum enGameChoice { Stone = 1 ,Papre = 2 , Scissors = 3 } ;
enum enWinner {Player1 = 1 , Computer =2 , Draw = 3 };

struct stRoundsInfo
{
    short RoundsNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice  ComputerChoice;
    enWinner Winner;
    string WinnerName=" ";
};

struct stGameResult 
{
    short  GameRounds =0;
    short Player1WinTime=0;
    short Computer2WinTime=0;
    short DrawTime=0;
    enWinner GameWimmer;
    string WinnerName=" ";
};

int ReadNumber(string Massage) {
    int Num = 0;
    do {
        cout << Massage;
        cin >> Num;
    } while (Num <= 0);
    return Num;
}

int RandomNumber(int From, int To) {
    int randNumber = rand() % (To - From + 1) + From;
    return randNumber;
}

void setWinnerScreenColor(enWinner Winner){
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout<<"\a";
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

string Taps(short NumberOfTap){
    string t=" ";
    for(short i=0;i<NumberOfTap;i++){
        t=t+"\t";
        cout<<t;
    }
    return t;
}

void ShowFinalGameResult(stGameResult GameResult){
    cout<<Taps(2)<<"_____[Game Results]_____\n";
    cout<<Taps(2)<<"Game Rounds : "<<GameResult.GameRounds<<endl;
    cout<<Taps(2)<<"Player win time : "<<GameResult.Player1WinTime<<endl;
    cout<<Taps(2)<<"Computer win time : "<<GameResult.Computer2WinTime<<endl;
    cout<<Taps(2)<<"Draw time : "<<GameResult.DrawTime<<endl;
    cout<<Taps(2)<<"final winner : "<<GameResult.WinnerName<<endl;
    cout<<Taps(2)<<"____________________________________________\n";
    setWinnerScreenColor(GameResult.GameWimmer);
}

void ShowGameOverScreen(){
    cout<<Taps(2)<<"_______________________________________\n\n";
    cout<<Taps(2)<<"          +++Game Over+++\n";
    cout<<Taps(2)<<"________________________________________\n\n";
}

void ReastScreen(){
    system("cls");
    system("color 0F");
}

enWinner WhoWonTheRounds(stRoundsInfo RoundsInfo){
    if(RoundsInfo.PlayerChoice==RoundsInfo.ComputerChoice){
        return enWinner::Draw;
    }
    switch (RoundsInfo.PlayerChoice)
    {
        case enGameChoice::Stone:
        if(RoundsInfo.ComputerChoice==enGameChoice::Papre){
            return enWinner::Computer;
        }
        break;
        case enGameChoice::Papre:
        if(RoundsInfo.ComputerChoice==enGameChoice::Scissors){
            return enWinner::Computer;
        }
        break;
        case enGameChoice::Scissors:
        if(RoundsInfo.ComputerChoice==enGameChoice::Stone){
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string WinnerName(enWinner Winner){
    string arrWinnerName[3]={"Player1","Computer","No Winner"};
    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice(){
    short Choice=1;
    do
    {
        cout<<"\nYour Choice : 1:[Stone] , 2:[Papre] , 3:[Scissors] : ";
        cin>>Choice;
    }while(Choice<1 || Choice>3);
    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice(){
   return (enGameChoice)RandomNumber(1,3);
}

string ChoiceName(enGameChoice Choice){
    string arrChoiceName[3]={"Stone ","Papre","Scissors"};
    return arrChoiceName[Choice-1];
}

void PrintRoundsResult(stRoundsInfo RoundsInfo){
    cout<<"\n____________________Rounds["<<RoundsInfo.RoundsNumber<<"]_______________\n";
    cout<<"Player1 Choice : "<<ChoiceName(RoundsInfo.PlayerChoice)<<endl;
    cout<<"Computer Choice : "<<ChoiceName(RoundsInfo.ComputerChoice)<<endl;
    cout<<"Round Winner : ["<<RoundsInfo.WinnerName<<"]\n";
    cout<<"_______________________________________________\n";
    setWinnerScreenColor(RoundsInfo.Winner);
}

enWinner WhoWonTheGame(stGameResult GameResult){
    if(GameResult.Player1WinTime>GameResult.Computer2WinTime){
        return enWinner::Player1;
    }
    else if(GameResult.Computer2WinTime>GameResult.Player1WinTime){
        return enWinner::Computer;
    }
    else{
        return enWinner::Draw;
    }
}

stGameResult FillGameResult(short HowManyRounds,short Player1WinTime ,short Computer2WinTime,short DrawTime ){
    stGameResult GameResult;
    GameResult.GameRounds=HowManyRounds;
    GameResult.Player1WinTime=Player1WinTime;
    GameResult.Computer2WinTime=Computer2WinTime;
    GameResult.DrawTime=DrawTime;
    GameResult.GameWimmer=WhoWonTheGame(GameResult);
    GameResult.WinnerName=WinnerName(GameResult.GameWimmer);
    return GameResult;
}

stGameResult PlayeGame(short HowManyRounds){
    stRoundsInfo RoundsInfo;
    short Player1WinTime=0,Computer2WinTime=0, DrawTime=0;
    for(short GameRounds =1;GameRounds<=HowManyRounds;GameRounds++){
        cout<<"\nRouuds["<<GameRounds<<"] begine : \n";
        RoundsInfo.RoundsNumber = GameRounds;
        RoundsInfo.PlayerChoice=ReadPlayer1Choice();
        RoundsInfo.ComputerChoice=GetComputerChoice();
        RoundsInfo.Winner=WhoWonTheRounds(RoundsInfo);
        RoundsInfo.WinnerName=WinnerName(RoundsInfo.Winner);

        if(RoundsInfo.Winner==enWinner::Player1){
            Player1WinTime++;
        }
        else if(RoundsInfo.Winner==enWinner::Computer){
            Computer2WinTime++;
        }
        else{
            DrawTime++;
        }
        PrintRoundsResult(RoundsInfo);
    }
    return FillGameResult(HowManyRounds,Player1WinTime,Computer2WinTime,DrawTime);
}

short ReadHowManyRounds(){
    short GameRounds=1;
    do
    {
        cout<<"How many Rounds 1 to 10 : ";
        cin>>GameRounds;
    }while (GameRounds<1 || GameRounds>10);
    return GameRounds;
}

void StartGame(){
    char PlayeAgine='Y';
    do
    {
        ReastScreen();
        stGameResult GameResult = PlayeGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResult);

        cout<<endl<<Taps(2)<<"Do you want to play agine ? Y/N ? ";
        cin>>PlayeAgine;
    }while (PlayeAgine == 'Y'|| PlayeAgine=='y');
    
}

int main(){
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}