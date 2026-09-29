#include "Player.hpp"
#include "Card.hpp"
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player{
    private:
        string name;
        vector<Card> hand;
    public:
        SimplePlayer(const string &name_in): name(name_in) {}
        const string & get_name() const override{
            return name;
    }

        void add_card(const Card &c) override {
            assert(hand.size() < 5);
            hand.push_back(c);
    }


        bool make_trump(const Card &upcard, bool is_dealer, int round,
                  Suit &order_up_suit) const override{
            assert(round==1 || round==2);
            if(round==1){
                Suit trump = upcard.get_suit();
                int num_cards=0;
                for(int i=0; i<hand.size(); i++){
                    if((hand[i].is_trump(trump))&&(hand[i].is_face_or_ace())){
                        num_cards++;
                    }
                }
                if(num_cards>=2){
                    order_up_suit=trump;
                    return true;
                }else{
                    return false;
                }
            }else{
                Suit trump=Suit_next(upcard.get_suit());
                int num_cards=0;
                for(int i=0; i<hand.size(); i++){
                    if(hand[i].is_trump(trump) && hand[i].is_face_or_ace()){
                        num_cards++;
                    }
                }
                if(num_cards>=1){
                    order_up_suit = trump;
                    return true;
                }
                if(is_dealer){
                    order_up_suit=trump;
                    return true;
                }
                return false;
            }
        }

        void add_and_discard(const Card &upcard) override{
            assert(hand.size()==5);
            Suit trump = upcard.get_suit();
            hand.push_back(upcard);
            int min=0;
            for(int i=0; i<hand.size(); i++){
                if(Card_less(hand[i], hand[min], trump)){
                    min = i;
                }
            }
            hand.erase(hand.begin()+min);
            assert(hand.size()==5);
        }

        Card lead_card(Suit trump) override {
            assert(hand.size()>=1);
            bool non_trump=false;
            for(int i=0; i<hand.size(); i++){
                if(!hand[i].is_trump(trump)){
                    non_trump=true;
                    break;
                }
            }
            int max=0;
            if (non_trump) {
                max = -1;
                for (int i = 0; i < (int)hand.size(); ++i) {
                    if (hand[i].is_trump(trump)){
                        continue;
                    }
                    if (max == -1 || Card_less(hand[max], hand[i], trump)) {
                        max = i;
                    }
                }
            }else{
                for(int i=1; i<hand.size(); i++){
                    if(Card_less(hand[max], hand[i], trump)){
                        max=i;
                    }
                }
            }
            Card result = hand[max];
            hand.erase(hand.begin()+max);
            return result;
        }

        Card play_card(const Card &led_card, Suit trump) override {
            assert(hand.size()>=1);
            Suit led_suit = led_card.get_suit(trump);
            bool follow = false;
            for(int i=0; i<hand.size(); i++){
                if(hand[i].get_suit(trump)==led_suit){
                    follow=true;
                    break;
                }
            }
            int index = 0;
            if (follow) {
                index = -1;
                for (int i = 0; i < (int)hand.size(); ++i) {
                    if (hand[i].get_suit(trump) != led_suit){
                        continue;
                    }
                    if (index == -1 || Card_less(hand[index], hand[i], led_card, trump)) {
                        index = i;
                    }
                }
            }else{
                for(int i=0; i<hand.size(); i++){
                    if(Card_less(hand[i], hand[index], trump)){
                        index=i;
                    }
                }
            }
            Card result=hand[index];
            hand.erase(hand.begin()+index);
            return result;
        }

};

class HumanPlayer : public Player {
private:
  string name;
  vector<Card> hand;
public:
  HumanPlayer(const string &name_in) : name(name_in) {}
  const string & get_name() const override {
    return name;
  }
  // 每次添加牌后立即排序，确保手牌始终有序
  void add_card(const Card &c) override {
    assert(hand.size() < MAX_HAND_SIZE);
    hand.push_back(c);
    std::sort(hand.begin(), hand.end());
  }
  bool make_trump(const Card &upcard, bool is_dealer, int round,
                  Suit &order_up_suit) const override {
    //打印当前手牌
    for (size_t i = 0; i < hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
    }
    cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
    string decision;
    cin >> decision;
    if (decision != "pass") {
      order_up_suit = string_to_suit(decision);
      return true;
    }
    return false;
  }
  void add_and_discard(const Card &upcard) override {
    assert(hand.size() > 0);
    
    //打印当前手牌
    for (size_t i = 0; i < hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
    }
    cout << "Discard upcard: [-1]" << endl;
    cout << "Human player " << name << ", please select a card to discard:" << endl;
    int index;
    cin >> index;
    if (index != -1) {
      // 替换手牌并重新排序
      hand[index] = upcard;
      std::sort(hand.begin(), hand.end());
    }
    // 如果输入是 -1，则直接丢弃 upcard，手牌不变
  }
  Card lead_card(Suit trump) override {
    //打印当前手牌
    for (size_t i = 0; i < hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
    }
    cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
    cout << "Human player " << name << ", please select a card:" << endl;
    
    int index;
    cin >> index;
    Card card = hand[index];
    hand.erase(hand.begin() + index);
    return card;
  }
  Card play_card(const Card &led_card, Suit trump) override {
    // 与 lead_card 相同：显示手牌并读取用户选择
    //打印当前手牌
    for (size_t i = 0; i < hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
    }
    cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
    cout << "Human player " << name << ", please select a card:" << endl;
    
    int index;
    cin >> index;
    Card card = hand[index];
    hand.erase(hand.begin() + index);
    return card;
  }
};


Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }else if(strategy == "Human"){
        return new HumanPlayer(name);
    }
  // Repeat for each other type of Player
  // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

