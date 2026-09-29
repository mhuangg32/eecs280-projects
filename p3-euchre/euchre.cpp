#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
#include <cassert>
using namespace std;

struct PlayerInfo {
    vector<string> names;
    vector<string> strategies;
};

class Game{
    public:
    Game(PlayerInfo info, int pointsIn, bool shuffleIn, Pack packIn):
        pack(packIn), pointsToWin(pointsIn), doShuffle(shuffleIn), 
        team0Score(0), team1Score(0), dealerIdx(0)
    {
        for(int i = 0; i < 4; i++){
            players.push_back(Player_factory(info.names[i], info.strategies[i]));
        }
    }

    ~Game() {
        for (int i = 0; i < 4; ++i) {
            delete players[i];
        }
    }

    void play(){
        int handCount = 0;
        while(team0Score < pointsToWin && team1Score < pointsToWin){
            playHand(handCount);
            handCount++;
            dealerIdx = (dealerIdx + 1) % 4;
        }

        // Announce Winner
        if (team0Score >= pointsToWin) {
            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " win!" << endl;
        } else {
            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " win!" << endl;
        }
    }

    private:
    vector<Player*> players;
    Pack pack;
    int pointsToWin;
    bool doShuffle;
    int team0Score;
    int team1Score;
    int dealerIdx;

    void playHand(int handCount) {
        Card upcard = shuffleAndDeal(handCount);
        int makerIdx = -1;
        Suit trump = makeTrump(upcard, makerIdx);
        int team0Tricks = playTricks(trump);
        tallyScore(makerIdx, team0Tricks);
    }

    void tallyScore(int makerIdx, int t0Tricks) {
        // 定义团队全名
        string t0Name = players[0]->get_name() + " and " + players[2]->get_name();
        string t1Name = players[1]->get_name() + " and " + players[3]->get_name();
    
        int makerTeam = makerIdx % 2;
        int mTricks;
        string mName;
        string dName;

        // 显式判定叫牌方胜场与名称，替代三元运算符
        if (makerTeam == 0) {
            mTricks = t0Tricks;
            mName = t0Name;
            dName = t1Name;
        } else {
            mTricks = 5 - t0Tricks;
            mName = t1Name;
            dName = t0Name;
        }

        // 判定得分情况
        if (mTricks == 5) {
            // March!
            cout << mName << " win the hand" << endl << "march!" << endl;
            if (makerTeam == 0) { team0Score += 2; } else { team1Score += 2; }
        } 
        else if (mTricks >= 3) {
            // Normal Win
            cout << mName << " win the hand" << endl;
            if (makerTeam == 0) { team0Score += 1; } else { team1Score += 1; }
        } 
        else {
            // Euchred!
            cout << dName << " win the hand" << endl << "euchred!" << endl;
            if (makerTeam == 0) { team1Score += 2; } else { team0Score += 2; }
        }

        // 打印当前分数
        cout << t0Name << " have " << team0Score << " points" << endl;
        cout << t1Name << " have " << team1Score << " points" << endl << endl;
    }

    Card shuffleAndDeal(int handCount){
        /*
        Hand 0
        Adi deals
        Jack of Diamonds turned up
        */
        cout << "Hand " << handCount << endl;
        string dealerName = players[dealerIdx]->get_name();
        cout << dealerName << " deals" << endl;

        if(doShuffle){
            pack.shuffle();
        }
        else{
            pack.reset();
        }

        int round1[] = {3, 2, 3, 2};
        for(int i = 0; i < 4; i++){
            int playerIdx = (dealerIdx + 1 + i) % 4;
            for(int j = 0; j < round1[i]; j++){
                players[playerIdx]->add_card(pack.deal_one());
            }
        }

        int round2[] = {2, 3, 2, 3};
        for(int i = 0; i < 4; i++){
            int playerIdx = (dealerIdx + 1 + i) % 4;
            for(int j = 0; j < round2[i]; j++){
                players[playerIdx]->add_card(pack.deal_one());
            }
        }

        Card upcard = pack.deal_one();
        cout << upcard << " turned up\n";

        return upcard;
    }
    
    Suit makeTrump(Card upcard, int& makerIdx){
        Suit trump;
        bool trumpMade = false;

        // 第一轮：使用 upcard 的花色
        for (int i = 0; i < 4 && !trumpMade; ++i) {
            int playerIdx = (dealerIdx + 1 + i) % 4;
            if (players[playerIdx]->
            make_trump(upcard, (playerIdx == dealerIdx), 1, trump)) {
                cout << players[playerIdx]->get_name() << " orders up " << trump << endl;
                players[dealerIdx]->add_and_discard(upcard);
                makerIdx = playerIdx;
                trumpMade = true;
            } else {
                cout << players[playerIdx]->get_name() << " passes" << endl;
            }
        }

        // 第二轮：如果第一轮没定，换其他花色
        if (!trumpMade) {
            for (int i = 0; i < 4 && !trumpMade; ++i) {
                int playerIdx = (dealerIdx + 1 + i) % 4;
                if (players[playerIdx]->
                make_trump(upcard, (playerIdx == dealerIdx), 2, trump)) {
                    cout << players[playerIdx]->get_name() << " orders up " 
                    << trump << endl;
                    makerIdx = playerIdx;
                    trumpMade = true;
                }
                else {
                    cout << players[playerIdx]->get_name() << " passes" << endl;
                }
            }
        }

        cout << endl;
        return trump;
    }

    int playTricks(Suit trump){
        int trickWon[2] = {0, 0};
        int leaderIdx = (dealerIdx + 1) % 4;

        for(int i = 0; i < 5; i++){
            Card ledCard = players[leaderIdx]->lead_card(trump);
            cout << ledCard << " led by " << players[leaderIdx]->get_name() << endl;

            Card winningCard = ledCard;
            int winnerIdx = leaderIdx;

            for(int j = 1; j < 4; j++){
                int current_idx = (leaderIdx + j) % 4;
                Card played = players[current_idx]->play_card(ledCard, trump);
                cout << played << " played by " 
                << players[current_idx]->get_name() << endl;
        
                // 比较：如果 played 比当前的 winning_card 强
                if (Card_less(winningCard, played, ledCard, trump)) {
                    winningCard = played;
                    winnerIdx = current_idx;
                }
            }

            cout << players[winnerIdx]->get_name() << " takes the trick" << endl << endl;
            trickWon[winnerIdx % 2]++;
            leaderIdx = winnerIdx; // 下一局由赢家领牌
        }

        return trickWon[0];
    }
};



int main(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    return 1;
    }

  int pointsToWin = stoi(argv[3]);
  if(pointsToWin < 1 || pointsToWin > 100){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    return 1;
  }

  string packFileName = argv[1];
  string shuffleArg = argv[2];
  if(shuffleArg != "noshuffle" && shuffleArg != "shuffle"){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    return 1;
  }

  for (int i = 5; i <= 11; i += 2) {
        string type = argv[i];
        if (type != "Simple" && type != "Human"){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                 << "NAME4 TYPE4" << endl;
            return 1;
        }
    }

   ifstream  pack_input(packFileName);
   if(!pack_input.is_open()){
        cout << "Error opening " << packFileName << endl; 
        return 1;
   }

    vector<string> names = {argv[4], argv[6], argv[8], argv[10]};
    vector<string> strategies = {argv[5], argv[7], argv[9], argv[11]};
    bool doShuffle = (shuffleArg == "shuffle");
    Pack pack(pack_input);

    //start game
    PlayerInfo info = {names, strategies};
    Game game(info, pointsToWin, doShuffle, pack);
    game.play();

    return 0;
}