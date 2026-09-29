#include "Pack.hpp"
#include <iostream>
#include <cassert>

using namespace std;

Pack::Pack(){
    next = 0;
    int cardIdx = 0;

    for(int s = SPADES; s <= DIAMONDS; s++){
        for(int r = NINE; r <= ACE; r++){
            Suit suit = static_cast<Suit>(s);
            Rank rank = static_cast<Rank>(r);

            cards[cardIdx] =  Card(rank, suit);
            cardIdx++;
        }
    }
}

Pack::Pack(std::istream& pack_input){
    next = 0;

    for(int i = 0; i < PACK_SIZE; i++){
        pack_input >> cards[i];
    }
}

Card Pack::deal_one(){
    assert(next < PACK_SIZE);

    Card card = cards[next];
    next++;
    return card;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){

    for(int i = 0; i < 7; i++){
        array<Card, PACK_SIZE> newCards;

        int leftIndex = 0;
        int rightIndex = 12;
        for(int i = 0; i < PACK_SIZE; i++){
            if(i % 2 == 0){
                newCards[i] = cards[rightIndex];
                rightIndex++; 
            }
            else{
                newCards[i] = cards[leftIndex];
                leftIndex++;       
            }
        }

        cards = newCards;
    }
    
    reset();
}

bool Pack::empty() const{
    return next >= PACK_SIZE;
}