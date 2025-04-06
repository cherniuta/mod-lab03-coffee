// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOff) {
    Automata a;
    EXPECT_EQ(OFF, a.getState());
}

TEST(AutomataTest, PowerOnChangesStateToWait) {
    Automata a;
    a.on();
    EXPECT_EQ(WAIT, a.getState());
}

TEST(AutomataTest, PowerOffReturnsToOffState) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(OFF, a.getState());
}

TEST(AutomataTest, CoinInWaitStateChangesToAccept) {
    Automata a;
    a.on();
    a.coin(50);
    EXPECT_EQ(ACCEPT, a.getState());
}

TEST(AutomataTest, ChoiceInAcceptStateChangesToCheck) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(1);
    EXPECT_EQ(CHECK, a.getState());
}

TEST(AutomataTest, CheckWithEnoughMoneyReturnsTrueAndChangesToCook) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(1);
    EXPECT_TRUE(a.check());
    EXPECT_EQ(COOK, a.getState());
}

TEST(AutomataTest, CheckWithoutEnoughMoneyReturnsFalse) {
    Automata a;
    a.on();
    a.coin(30);
    a.choice(1);
    EXPECT_FALSE(a.check());
    EXPECT_EQ(CHECK, a.getState());
}

TEST(AutomataTest, CancelReturnsToWaitState) {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    EXPECT_EQ(WAIT, a.getState());
}

TEST(AutomataTest, CookCompletesAndReturnsToWaitState) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(1);
    a.check();
    a.cook();
    EXPECT_EQ(WAIT, a.getState());
}

TEST(AutomataTest, GetMenuDoesNotThrow) {
    Automata a;
    a.on();
    EXPECT_NO_THROW(a.getMenu());
}

TEST(AutomataTest, FullTransactionCycleWorks) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(0);
    a.check();
    a.cook();
    EXPECT_EQ(WAIT, a.getState());
}
