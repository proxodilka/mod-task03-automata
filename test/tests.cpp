#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, Basic) {
    Automata a;
    EXPECT_EQ(a.get_state(), STATE::OFF);

    a.on();
    EXPECT_EQ(a.get_state(), STATE::WAIT);

    a.coin(10);
    EXPECT_EQ(a.get_state(), STATE::ACCEPT);

    a.coin(10);
    EXPECT_EQ(a.get_state(), STATE::ACCEPT);

    int money_before = a.get_cash();
    EXPECT_EQ(money_before, 20);

    // not enough money
    a.choice(0);
    EXPECT_EQ(a.get_state(), STATE::CHECK);

    a.check();
    EXPECT_EQ(a.get_state(), STATE::ACCEPT);
    EXPECT_EQ(money_before, a.get_cash());

    a.choice(1);
    EXPECT_EQ(a.get_state(), STATE::CHECK);

    a.check();
    EXPECT_EQ(a.get_state(), STATE::TRANSACTION_APPROVED);
    EXPECT_EQ(money_before - TEST_MENU[1].price, a.get_cash());

    a.cook();
    EXPECT_EQ(a.get_state(), STATE::COOK);

    a.finish();
    EXPECT_EQ(a.get_state(), STATE::WAIT);
    EXPECT_EQ(money_before - TEST_MENU[1].price, a.get_cash());

    a.off();
    EXPECT_EQ(a.get_state(), STATE::OFF);
}

// TEST(AutomataTest, MoneySave) {
//     Automata* a = new Automata();
//     a->on();
//     a->coin(100);
//     a->choice(0);

//     testing::internal::CaptureStdout();
//     a->cancel();
//     EXPECT_EQ(a->get_cash(), 0);
//     EXPECT_EQ("Here is your coins, I don't need them anymore...\n", testing::internal::GetCapturedStdout());

//     a->coin(100);
//     testing::internal::CaptureStdout();
//     a->off();
//     EXPECT_EQ(a->get_cash(), 0);
//     EXPECT_EQ("Here is your coins, I don't need them anymore...\n", testing::internal::GetCapturedStdout());

//     a->on();
//     a->coin(100);
//     testing::internal::CaptureStdout();
//     delete a;
//     EXPECT_EQ("Here is your coins, I don't need them anymore...\n", testing::internal::GetCapturedStdout());
// }

// TEST(AutomataTest, IncorrectTransitions) {
//     Automata a;
    
//     // Putting coins into the off automat
//     ASSERT_THROW(a.coin(10), IncorrectTransitionError);

//     a.on();
//     a.coin(10);
//     a.choice(0);

//     // Cook without check
//     ASSERT_THROW(a.cook(), IncorrectTransitionError);

//     a.check();

//     // Cook after declined transaction
//     ASSERT_THROW(a.cook(), IncorrectTransitionError);

//     a.coin(100);
//     a.choice(0);
//     a.check();
//     a.cook();
//     a.finish();

//     // Successful result even after few exceptions
//     EXPECT_EQ(a.get_state(), STATE::WAIT);
// }
