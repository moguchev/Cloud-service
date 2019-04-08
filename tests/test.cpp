// Copyright 2019 (c) <Cloud9>

#include <gtest/gtest.h>
#include <../include/back.hpp>

TEST(database, good) {
    std::string root = "login";
    std::string data = "mail";

    myDataBase.makeNote(root, data);
    std::string answer = myDataBase.get(root);

    EXPECT_EQ(answer, data);
}

TEST(database, bad) {
    std::string root = "login";
    std::string data = "mail";

    myDataBase.makeNote(root, data);
    std::string answer = myDataBase.get("logout");

    EXPECT_EQ(answer, std::string(""));
}

TEST(database, delete_note) {
    std::string root = "login";
    std::string data = "mail";

    myDataBase.makeNote(root, data);
    std::string answer = myDataBase.get("login");
    EXPECT_EQ(answer, data);

    myDataBase.deleteNote(root);
    answer = myDataBase.get("login");
    EXPECT_EQ(answer, std::string(""));
}

TEST(receiver, execute) {
    Load load("login", "mail");

    myReceiver(&load);

    std::string answer = myDataBase.get("login");

    EXPECT_EQ(answer, std::string("mail"));
}
