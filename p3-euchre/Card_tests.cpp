#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <sstream>
using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_defalut_constructor){
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_is_face){
    Card a(JACK, HEARTS);
    Card b(QUEEN, HEARTS);
    Card c(KING, HEARTS);
    Card d(ACE, HEARTS);
    Card e(EIGHT, HEARTS);
    ASSERT_TRUE(a.is_face_or_ace());
    ASSERT_TRUE(b.is_face_or_ace());
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(d.is_face_or_ace());
    ASSERT_FALSE(e.is_face_or_ace());
}

TEST(test_is_trump_normal){
    Card c(TEN, HEARTS);
    ASSERT_TRUE(c.is_trump(HEARTS));
    ASSERT_FALSE(c.is_trump(SPADES));
}

TEST(test_is_trump_left){
    Card c(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_trump(HEARTS));
}

TEST(test_suit_next_black_card){
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
}

TEST(test_suit_next_red_card){
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
}

TEST(test_get_suit_normal){
    Suit trump = HEARTS;
    Card normal_card(TEN, CLUBS);
    ASSERT_EQUAL(CLUBS, normal_card.get_suit(trump));

    Card trump_card(ACE, HEARTS);
    ASSERT_EQUAL(HEARTS, trump_card.get_suit(trump));

    Card right_bow(JACK, HEARTS);
    ASSERT_EQUAL(HEARTS, right_bow.get_suit(trump));

    Card other_jack(JACK, SPADES);
    ASSERT_EQUAL(SPADES, other_jack.get_suit(trump));
}

TEST(test_get_suit_left){
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(c.get_suit(HEARTS), HEARTS);
}

TEST(test_left_bower){
    Suit trump=HEARTS;
    Card a(JACK,DIAMONDS);
    Card b(JACK, HEARTS);
    Card c(JACK, SPADES);
    Card d(ACE,DIAMONDS);
    ASSERT_TRUE(a.is_left_bower(trump));
    ASSERT_FALSE(b.is_left_bower(trump));
    ASSERT_FALSE(c.is_left_bower(trump));
    ASSERT_FALSE(d.is_left_bower(trump));
}

TEST(test_right_bower){
    Suit trump=HEARTS;
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    Card c(JACK, SPADES);
    Card d(ACE,HEARTS);
    ASSERT_TRUE(a.is_right_bower(trump));
    ASSERT_FALSE(b.is_right_bower(trump));
    ASSERT_FALSE(c.is_right_bower(trump));
    ASSERT_FALSE(d.is_right_bower(trump));
}

TEST(test_istream_constructor){
    Card c(ACE, SPADES);
    Card d;
    stringstream in;
    in << c;
    ASSERT_EQUAL(string("Ace of Spades"), in.str());
    in >> d;
    ASSERT_EQUAL(ACE, d.get_rank());
    ASSERT_EQUAL(SPADES, d.get_suit());
}

TEST(test_comparsions_equal){
    Card a(ACE, HEARTS);
    Card b(ACE, HEARTS);
    Card c(ACE, SPADES);
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(a != c);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(a == c);
}

TEST(test_comparsions_smaller){
    ASSERT_TRUE(Card(SEVEN, HEARTS) < Card(EIGHT, HEARTS));
    ASSERT_FALSE(Card(SEVEN, HEARTS) < Card(FIVE, HEARTS));
    ASSERT_TRUE(Card(ACE, SPADES) < Card(ACE, HEARTS));
    ASSERT_FALSE(Card(ACE, HEARTS) < Card(ACE, SPADES));
}

TEST(test_other_comparisions){
    Card a(TEN, CLUBS);
    Card b(TEN, CLUBS);
    Card c(JACK, CLUBS);
    ASSERT_TRUE(a <=b);
    ASSERT_TRUE(a >=b);
    ASSERT_FALSE(a <b);
    ASSERT_FALSE(a > b);
    ASSERT_TRUE(a <c);
    ASSERT_TRUE(c > a);
    ASSERT_TRUE(a <=c);
    ASSERT_TRUE(c >=a);
}

TEST(test_card_less_whether_trump){
    Suit trump = HEARTS;
    Card trump_card(TEN, HEARTS);
    Card not_trump(ACE, SPADES);
    ASSERT_TRUE(Card_less(not_trump, trump_card, trump));
    ASSERT_FALSE(Card_less(trump_card, not_trump, trump));
}

TEST(test_card_less_both_trump){
    Suit trump = HEARTS;
    Card trump_ace(ACE, HEARTS);
    Card right(JACK, HEARTS);
    Card left(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(left, right, trump));
    ASSERT_TRUE(Card_less(trump_ace, left, trump));
    ASSERT_TRUE(Card_less(trump_ace, right, trump));
}

TEST(test_card_less_both_trump_non_bower_rank){
    Suit trump = HEARTS;
    Card a(KING, HEARTS);
    Card b(QUEEN, HEARTS);
    ASSERT_TRUE(Card_less(b, a, trump));
    ASSERT_FALSE(Card_less(a, b, trump));
}

TEST(test_card_less_both_not_trump){
    Suit trump = HEARTS;
    Card a(SEVEN, SPADES);
    Card b(TEN, SPADES);
    ASSERT_TRUE(Card_less(a, b, trump));
    ASSERT_FALSE(Card_less(b,a,trump));
}

TEST(test_card_less_led_suit_offsuit){
    Suit trump = HEARTS;
    Card a(TEN, CLUBS);
    Card b(EIGHT, CLUBS);
    Card c(ACE, SPADES);
    ASSERT_TRUE(Card_less(c, b, a, trump));
    ASSERT_FALSE(Card_less(b, c, a, trump));
}

TEST(test_card_less_led_trump){
    Suit trump = HEARTS;
    Card a(TEN, CLUBS);
    Card not_trump(KING, CLUBS);
    Card trump_card(NINE, HEARTS);
    ASSERT_TRUE(Card_less(not_trump, trump_card, a, trump));
    ASSERT_FALSE(Card_less(trump_card, not_trump, a, trump));
}

TEST(test_card_less_led_both_suit){
    Suit trump = HEARTS;
    Card a(TEN, CLUBS);
    Card b(NINE, CLUBS);
    Card c(KING, CLUBS);
    ASSERT_TRUE(Card_less(b,c,a,trump));
    ASSERT_FALSE(Card_less(c,b,a,trump));
}

TEST(test_card_less_led_left_bower){
    Suit trump = HEARTS;
    Card left(JACK, DIAMONDS);
    Card trump_card(ACE, HEARTS);
    Card not_trump(ACE, SPADES);
    ASSERT_TRUE(Card_less(not_trump, trump_card, left, trump));
    Card follow_trump_card(TEN, HEARTS);
    Card off_suit_card(ACE, SPADES);
    ASSERT_TRUE(Card_less(off_suit_card, follow_trump_card, left, trump));
    ASSERT_FALSE(Card_less(follow_trump_card, off_suit_card, left,trump));
}


TEST_MAIN()
