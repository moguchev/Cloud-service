// Copyright 2019 (c) <Cloud9>

#include <gtest/gtest.h>
#include <../include/back.hpp>


TEST(database, good) {
    std::any root = std::make_any("login");
    std::any data = std::make_any("mail");

    myDataBase.make_note(root, data);
    std::any answer = myDataBase.get(root);

    EXPECT_EQ(answer, data);
}

TEST(database, bad) {
    std::any root = std::make_any("login");
    std::any data = std::make_any("mail");

    myDataBase.make_note(root, data);
    std::any answer = myDataBase.get(std::make_any("logout"));

    EXPECT_EQ(answer, std::make_any(nullptr));
}

TEST(database, delete_note) {
    std::any root = std::make_any("login");
    std::any data = std::make_any("mail");

    myDataBase.make_note(root, data);
    std::any answer = myDataBase.get(std::make_any("login"));
    EXPECT_EQ(answer, data);

    myDataBase.delete_note(root);
    answer = myDataBase.get(std::make_any("login"));
    EXPECT_EQ(answer, std::make_any(nullptr));
}

TEST(receiver, execute) {
    Load load(std::make_any("login"), std::make_any("mail"));

    myReceiver(&load);

    std::any answer = myDataBase.get(std::make_any("login"));

    EXPECT_EQ(answer, std::make_any("mail"));
}

