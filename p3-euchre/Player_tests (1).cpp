#include "Player.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <iostream>
#include "Card.hpp"
using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion_prints_name){
    Player *p= Player_factory("John", "Simple");
    ostringstream oss;
    oss << *p;
    ASSERT_EQUAL("John", oss.str());
    delete p;
}

TEST(test_make_trump_round1_orders_up_two_ace_trump){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(THREE, SPADES));
    p->add_card(Card(THREE, DIAMONDS));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c, false, 1, order));
    ASSERT_EQUAL(HEARTS, order);
    delete p;
}

TEST(test_make_trump_round1_orders_up_one_ace_trump){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(EIGHT, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(THREE, SPADES));
    p->add_card(Card(THREE, DIAMONDS));
    Suit order = HEARTS;
    ASSERT_TRUE(!(p->make_trump(c, false,1,order)));
    delete p;
}

TEST(test_make_trump_round1_left_bower_trump){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(THREE, SPADES));
    p->add_card(Card(THREE, CLUBS));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c, false, 1, order));
    ASSERT_EQUAL(HEARTS,order);
    delete p;
}

TEST(test_make_trump_round1_two_face_not_upcard){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(THREE, DIAMONDS));
    p->add_card(Card(FOUR, CLUBS));
    Suit order = SPADES;
    ASSERT_FALSE(p->make_trump(c, false, 1, order));
    delete p;
}

TEST(test_make_trump_round1_left_bower_wrong_color){
    Player *p = Player_factory("John","Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(JACK, SPADES));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(THREE, DIAMONDS));
    p->add_card(Card(FOUR, CLUBS));
    Suit order = SPADES;
    ASSERT_FALSE(p->make_trump(c, false, 1, order));
    delete p;
}

TEST(test_make_trump_round2_orders_sameColor_one_ace){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(KING, DIAMONDS));
    p->add_card(Card(EIGHT, CLUBS));
    p->add_card(Card(TWO, SPADES));
    p->add_card(Card(THREE, HEARTS));
    p->add_card(Card(THREE, CLUBS));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c, false,2,order));
    ASSERT_EQUAL(DIAMONDS, order);
    delete p;
}

TEST(test_make_trump_round2_force_same_color){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(TWO, SPADES));
    p->add_card(Card(THREE, HEARTS));
    p->add_card(Card(THREE, CLUBS));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c, true,2,order));
    ASSERT_EQUAL(DIAMONDS, order);
    delete p;
}

TEST(test_make_trump_round2_counts_left_bower_samecolor){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TWO, SPADES));
    p->add_card(Card(THREE, CLUBS));
    p->add_card(Card(FOUR, SPADES));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c,false,2,order));
    ASSERT_EQUAL(DIAMONDS, order);
    delete p;
}

TEST(test_make_trump_round2_only_left_bower){
    Player *p = Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    Suit order = SPADES;
    ASSERT_TRUE(p->make_trump(c, false, 2, order));
    ASSERT_EQUAL(DIAMONDS, order);
    delete p;
}

TEST(test_make_trump_round2_never_choose_upcard_suit){
    Player *p = Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(NINE, HEARTS));
    Suit order = SPADES;
    ASSERT_FALSE(p->make_trump(c, false, 2, order));
    delete p;
}

TEST(test_make_trump_round2_no_upcard_suit){
    Player *p= Player_factory("John", "Simple");
    Card c(NINE, HEARTS);
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(THREE, CLUBS));
    Suit order = SPADES;
    ASSERT_FALSE(p->make_trump(c, false, 2, order));
    delete p;
}

TEST(test_add_and_discard_five_cards){
    Player *p= Player_factory("John", "Simple");
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(JACK, CLUBS));
    p->add_card(Card(TWO, SPADES));
    p->add_card(Card(THREE, HEARTS));
    p->add_card(Card(THREE, CLUBS));
    Card c1(NINE, HEARTS);
    p->add_and_discard(c1);
    Suit trump = HEARTS;
    Card a = p->lead_card(trump);
    Card b = p->lead_card(trump);
    Card c = p->lead_card(trump);
    Card d = p->lead_card(trump);
    Card e = p->lead_card(trump);
    Card expected1(NINE, HEARTS);
    Card expected2(TEN, DIAMONDS);
    Card expected3(JACK, CLUBS);
    Card expected4(THREE, HEARTS);
    Card expected5(THREE, CLUBS);
    ASSERT_TRUE(a==expected1 || b==expected1 || c==expected1 || d==expected1 || e==expected1);
    ASSERT_TRUE(a==expected2 || b==expected2 || c==expected2 || d==expected2 || e==expected2);
    ASSERT_TRUE(a==expected3 || b==expected3 || c==expected3 || d==expected3 || e==expected3);
    ASSERT_TRUE(a==expected4 || b==expected4 || c==expected4 || d==expected4 || e==expected4);
    ASSERT_TRUE(a==expected5 || b==expected5 || c==expected5 || d==expected5 || e==expected5);
    Card discard(TWO, SPADES);
    ASSERT_FALSE(a==discard || b==discard || c==discard || d==discard || e==discard);
    delete p;
}  

TEST(test_add_and_discard_when_upcard_is_lowest){
    Player *p = Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(JACK, HEARTS));
    Card c1(NINE, HEARTS);
    p->add_and_discard(c1);
    Card a = p->lead_card(trump);
    Card b = p->lead_card(trump);
    Card c = p->lead_card(trump);
    Card d = p->lead_card(trump);
    Card e = p->lead_card(trump);
    Card f(NINE, HEARTS);
    ASSERT_FALSE(a==f || b==f || c==f || d==f || e==f);
    Card e1(JACK, HEARTS);
    Card e2(ACE, HEARTS);
    Card e3(KING, HEARTS);
    Card e4(QUEEN, HEARTS);
    Card e5(TEN, HEARTS);
    ASSERT_TRUE(a==e1 || b==e1 || c==e1 || d==e1 || e==e1);
    ASSERT_TRUE(a==e2 || b==e2 || c==e2 || d==e2 || e==e2);
    ASSERT_TRUE(a==e3 || b==e3 || c==e3 || d==e3 || e==e3);
    ASSERT_TRUE(a==e4 || b==e4 || c==e4 || d==e4 || e==e4);
    ASSERT_TRUE(a==e5 || b==e5 || c==e5 || d==e5 || e==e5);
    delete p;
}

TEST(test_add_and_discard_should_not_discard_low_trump_if_any_nonthrump_exists){
    Player *p = Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(JACK, SPADES));
    Card c1(TEN, HEARTS);
    p->add_and_discard(c1);
    Card a = p->lead_card(trump);
    Card b = p->lead_card(trump);
    Card c = p->lead_card(trump);
    Card d = p->lead_card(trump);
    Card e = p->lead_card(trump);
    Card f(JACK, SPADES);
    ASSERT_FALSE(a==f || b==f || c==f || d==f || e==f);
    Card g(NINE, HEARTS);
    ASSERT_TRUE(a==g || b==g || c==g || d==g || e==g);
    delete p;
}

TEST(test_add_discard_lowest_trump_when_all_trump){
    Player *p= Player_factory("John", "Simple");
    Card c1(JACK, HEARTS);
    Suit trump=HEARTS;
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(ACE, HEARTS));
    p->add_and_discard(c1);
    Card a = p->lead_card(trump);
    Card b = p->lead_card(trump);
    Card c = p->lead_card(trump);
    Card d = p->lead_card(trump);
    Card e = p->lead_card(trump);
    ASSERT_EQUAL(Card(JACK, HEARTS), a);
    ASSERT_EQUAL(Card(ACE, HEARTS), b);
    ASSERT_EQUAL(Card(KING, HEARTS), c);
    ASSERT_EQUAL(Card(QUEEN, HEARTS), d);
    ASSERT_EQUAL(Card(TEN, HEARTS), e);
    delete p;
}

TEST(test_lead_card_highest_nontrump){
    Player *p= Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(QUEEN, SPADES));
    p->add_card(Card(THREE, CLUBS));
    p->add_card(Card(THREE, HEARTS));
    Card c = p->lead_card(trump);
    ASSERT_EQUAL(c, Card(QUEEN, SPADES));
    delete p;
}

TEST(test_lead_card_all_trump_left_bower_beats_ace){
    Player *p = Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(KING, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    Card c=p->lead_card(trump);
    ASSERT_EQUAL(Card(JACK, DIAMONDS),c);
    delete p;
}

TEST(test_play_card_suit_with_highest_of_that_suit){
    Player *p= Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(TWO, HEARTS));
    p->add_card(Card(QUEEN, CLUBS));
    p->add_card(Card(FOUR, SPADES));
    p->add_card(Card(THREE, CLUBS));
    p->add_card(Card(THREE, DIAMONDS));
    Card c(KING, CLUBS);
    ASSERT_EQUAL(Card(QUEEN, CLUBS), p->play_card(c, trump));
    delete p;
}

TEST(test_play_card_not_follow_lowest){
    Player *p= Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(FIVE, HEARTS));
    p->add_card(Card(QUEEN, CLUBS));
    p->add_card(Card(FOUR, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(THREE, DIAMONDS));
    Card c(KING, SPADES);
    ASSERT_EQUAL(Card(THREE, DIAMONDS), p->play_card(c, trump));
    delete p;
}

TEST(test_play_card_follow_suit_even_if_has_trump){
    Player *p = Player_factory("John", "Simple");
    Suit trump = HEARTS;
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(NINE, DIAMONDS));
    Card c(KING, CLUBS);
    Card c1=p->play_card(c, trump);
    ASSERT_EQUAL(Card(ACE, CLUBS), c1);
    delete p;
}

TEST(test_simple_player_add_and_discard_protect_left_bower) {
    Player * p = Player_factory("Ken", "Simple");
    // 假设翻开的trump是 Spades，那么 Jack of Clubs 就是 Left Bower (第二大trump)
    // 手牌中包含：Left Bower 和一些高点数的非trump
    p->add_card(Card(JACK, CLUBS));    // Left Bower
    p->add_card(Card(ACE, HEARTS));   // 非trump
    p->add_card(Card(KING, HEARTS));  // 非trump
    p->add_card(Card(QUEEN, HEARTS)); // 非trump
    p->add_card(Card(TEN, HEARTS));   // 非trump (当前手牌中最弱的)

    Card upcard(NINE, SPADES); // trump是 Spades
    p->add_and_discard(upcard); 
    // 正确逻辑：upcard (9 of Spades) 是trump，比 10 of Hearts 强。
    // 应该丢弃 10 of Hearts。
    // 如果 Bug 认为 Jack of Clubs 不是trump，它可能会错误地丢弃 Jack。

    // 验证：最后出的牌应该是最强的。如果 Jack of Clubs 还在，它作为trump会最后出
    // (SimplePlayer 的策略是先出最高非trump，最后出trump)
    p->lead_card(SPADES); // 应该出 Ace Hearts
    p->lead_card(SPADES); // 应该出 King Hearts
    p->lead_card(SPADES); // 应该出 Queen Hearts
    Card c4 = p->lead_card(SPADES); // 应该出 Jack Clubs (Left Bower)
    Card c5 = p->lead_card(SPADES); // 应该出 Nine Spades (Upcard)

    ASSERT_EQUAL(c4, Card(JACK, CLUBS));
    ASSERT_NOT_EQUAL(c5, Card(TEN, HEARTS)); 

    delete p;
}

TEST(test_simple_player_add_and_discard_suit_tiebreak) {
    Player * p = Player_factory("Ken", "Simple");
    // 设定trump为 Clubs。手牌中有两张等级相同的 9
    p->add_card(Card(NINE, DIAMONDS)); // 非trump
    p->add_card(Card(NINE, SPADES));   // 非trump (根据 D>C>H>S，这是全场最小的) 
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(ACE, HEARTS));

    Card upcard(KING, CLUBS); // trump是 Clubs
    p->add_and_discard(upcard);

    // 应该丢弃 9 of Spades
    // 验证：通过出牌检查 9 of Spades 是否消失
    for (int i = 0; i < 5; ++i) {
        Card led = p->lead_card(CLUBS);
        ASSERT_NOT_EQUAL(led, Card(NINE, SPADES));
    }
    delete p;
}

TEST(test_simple_player_add_and_discard_left_bower_protection) {
    Player * p = Player_factory("Ken", "Simple");
    // trump是 Spades，梅花 Jack 是左包
    p->add_card(Card(JACK, CLUBS));    
    p->add_card(Card(ACE, HEARTS));   
    p->add_card(Card(KING, HEARTS));  
    p->add_card(Card(QUEEN, HEARTS)); 
    p->add_card(Card(TEN, HEARTS));   // 这才是全手牌最弱的

    Card upcard(NINE, SPADES); 
    p->add_and_discard(upcard); 

    // 验证：10 of Hearts 应该被丢弃了
    for (int i = 0; i < 5; ++i) {
        Card c = p->lead_card(SPADES);
        // 如果 10 of Hearts 还在，说明丢错牌了
        ASSERT_NOT_EQUAL(c, Card(TEN, HEARTS)); 
    }
    delete p;
}

TEST(test_simple_player_add_and_discard_real_euchre_ranks) {
    Player * p = Player_factory("Ken", "Simple");
    p->add_card(Card(NINE, SPADES));   // 非trump
    p->add_card(Card(NINE, CLUBS));    // 非trump
    p->add_card(Card(TEN, SPADES));    
    p->add_card(Card(JACK, SPADES));   
    p->add_card(Card(QUEEN, SPADES));  
    
    Card upcard(ACE, DIAMONDS); // trump是 Diamonds
    p->add_and_discard(upcard);
    
    // 根据权重 D > C > H > S，9 of Spades 是最小的，应该丢掉
    for (int i = 0; i < 5; ++i) {
        Card c = p->lead_card(DIAMONDS);
        ASSERT_NOT_EQUAL(c, Card(NINE, SPADES));
    }
    delete p;
}

TEST(test_simple_player_add_and_discard_bug8_exposure) {
    Player * p = Player_factory("Ken", "Simple");
    // 庄家手牌全是 Ace 和 King
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(ACE, DIAMONDS));
    p->add_card(Card(KING, CLUBS));
    p->add_card(Card(QUEEN, CLUBS)); // 确保没有比 9 Hearts 更小的牌（除了Rank）

    // Upcard 是 Rank 最低的trump (9 of Hearts)
    Card upcard(NINE, HEARTS); 
    p->add_and_discard(upcard); 

    // 关键断言：验证 9 of Hearts (trump) 是否还在手里
    // 如果是 Buggy 实现，它会因为 9 的 Rank 小而把 9 扔掉
    bool found_nine = false;
    for (int i = 0; i < 5; ++i) {
        Card c = p->lead_card(HEARTS);
        if (c == Card(NINE, HEARTS)) {
            found_nine = true;
        }
    }
    ASSERT_TRUE(found_nine); // 正确代码应该留下这门trump
    delete p;
}

TEST(test_simple_player_make_trump_dealer_round1_not_greedy) {
    Player * p = Player_factory("Ken", "Simple");
    // 庄家手里只有一张trump Ace
    p->add_card(Card(ACE, HEARTS));   // trump
    p->add_card(Card(TEN, SPADES));  
    p->add_card(Card(NINE, SPADES)); 
    p->add_card(Card(TEN, CLUBS));   
    p->add_card(Card(NINE, CLUBS));  

    Card upcard(KING, HEARTS); // Upcard 是trump
    Suit order_up_suit;
    
    // 即使拿起 King 就能有两张trump，但作为 Simple Player，第一轮必须 pass
    ASSERT_FALSE(p->make_trump(upcard, true, 1, order_up_suit));
    
    delete p;
}

TEST(test_simple_player_make_trump_round2_ignore_cross_suit) {
    Player * p = Player_factory("Ken", "Simple");
    // Upcard 是 Hearts，所以第二轮只考虑 Diamonds
    Card upcard(NINE, HEARTS); 

    // 手里有另一颜色的 Ace (比如 Spades)
    p->add_card(Card(ACE, SPADES));   // 强力牌，但不是 Diamonds
    p->add_card(Card(TEN, HEARTS));  
    p->add_card(Card(NINE, HEARTS)); 
    p->add_card(Card(TEN, CLUBS));   
    p->add_card(Card(NINE, CLUBS));  

    Suit order_up_suit;
    // 虽然有 Ace，但因为花色不对，第二轮必须 pass
    ASSERT_FALSE(p->make_trump(upcard, false, 2, order_up_suit));
    
    delete p;
}

TEST(test_simple_player_make_trump_round1_right_bower) {
    Player * p = Player_factory("Ken", "Simple");
    Card upcard(NINE, SPADES); 

    // 手里有 Right Bower (Jack of Spades) 和另一个 Face 牌
    p->add_card(Card(JACK, SPADES));  // Right Bower
    p->add_card(Card(QUEEN, SPADES)); // 另一张trump Face
    p->add_card(Card(TEN, HEARTS));  
    p->add_card(Card(NINE, HEARTS)); 
    p->add_card(Card(TEN, CLUBS));   

    Suit order_up_suit;
    ASSERT_TRUE(p->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, SPADES);
    
    delete p;
}

TEST_MAIN()
