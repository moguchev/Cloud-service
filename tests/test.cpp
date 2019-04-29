// Copyright 2019 (c) <Cloud9>

#include <gtest/gtest.h>
#include <../include/back.hpp>

TEST(database, good) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);
    Note* answer = myDataBase.get(root);

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::any_cast<std::string>(data.GetData()));
}

TEST(database, bad) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);
    Note* answer = myDataBase.get(std::string("logout"));

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string(""));
}

TEST(database, delete_note) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);
    Note* answer = myDataBase.get(std::string("login"));
    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::any_cast<std::string>(data.GetData()));

    myDataBase.deleteNote(root);
    answer = myDataBase.get(std::string("login"));
    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string(""));
}

TEST(receiver, execute) {
    Load load(std::string("login"), std::string("mail"));

    myReceiver(&load);

    Note* answer = myDataBase.get(std::string("login"));

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string("mail"));
}
