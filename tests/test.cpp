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
    Note* answer = myDataBase.get("logout");

    EXPECT_EQ(answer, nullptr);
}

TEST(database, delete_note) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);
    Note* answer = myDataBase.get("login");
    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::any_cast<std::string>(data.GetData()));

    Delete _delete(root);
    myReceiver(&_delete);

    answer = myDataBase.get("login");
    EXPECT_EQ(answer, nullptr);
}

TEST(receiver, execute) {
    Load load(std::string("login"), std::string("mail"));

    myReceiver(&load);

    Note* answer = myDataBase.get("login");

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string("mail"));
}

TEST(database, change) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);
    Note* answer = myDataBase.get(root);

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::any_cast<std::string>(data.GetData()));

    Change change(std::string("login"), std::string("c++"));

    myReceiver(&change);

    answer = myDataBase.get("login");

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string("c++"));
}

TEST(database, merge) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    std::string merging = std::string("login2");
    Note data2;
    data2 = std::any(std::string("c++"));

    myDataBase.makeNote(merging, data2);

    Merge merge(root, merging);

    myReceiver(&merge);

    Note* answer = myDataBase.get("login");

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string("loginc++"));

    answer = myDataBase.get("login2");

    EXPECT_EQ(answer, nullptr);
}
