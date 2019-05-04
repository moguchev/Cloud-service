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

TEST(database, merge_with_string) {
    std::string root = std::string("login");
    Note data;
    data = std::any(std::string("mail"));

    myDataBase.makeNote(root, data);

    std::string merging = std::string("login2");
    Note data2;
    data2 = std::any(std::string("c++"));

    myDataBase.makeNote(merging, data2);

    Merge merge(root, merging);

    myReceiver(&merge);

    Note* answer = myDataBase.get("login");

    EXPECT_EQ(std::any_cast<std::string>(answer->GetData()),
              std::string("c++"));

    answer = myDataBase.get("login2");

    EXPECT_EQ(answer, nullptr);
}

TEST(database, merge_with_map) {
    std::string root = std::string("login");
    Note data;
    std::unordered_map<std::string, std::any> rootMap = {
            {std::string("login"), std::any(std::string("person"))},
            {std::string("data"), std::any(std::string("someData"))},
            {std::string("id"), std::any(static_cast<int>(5))}
    };
    data = std::any(rootMap);

    myDataBase.makeNote(root, data);

    std::string merging = std::string("login2");
    Note data2;
    std::unordered_map<std::string, std::any> mergingMap = {
            {std::string("data"), std::any(std::string("someAnotherData"))},
            {std::string("studying"), std::any(std::string("university"))}
    };
    data2 = std::any(mergingMap);

    myDataBase.makeNote(merging, data2);

    Merge merge(root, merging);

    myReceiver(&merge);

    Note* answer = myDataBase.get("login");
    auto answerMap =
            std::any_cast<std::unordered_map<std::string,
            std::any>>(answer->GetData());
    std::unordered_map<std::string, std::any> trueMap = {
            {std::string("login"), std::any(std::string("person"))},
            {std::string("data"), std::any(std::string("someAnotherData"))},
            {std::string("studying"), std::any(std::string("university"))}
    };
    bool status = false;

    if (answerMap.size() == trueMap.size() + 1) {
        status = true;
        for (auto& elem : trueMap) {
            if (std::any_cast<std::string>(elem.second) !=
                    std::any_cast<std::string>(answerMap[elem.first])) {
                status = false;
                break;
            }
        }
        if (status == true &&
                std::any_cast<int>(answerMap["id"]) != 5) {
            status = false;
        }
    }

    EXPECT_EQ(status, true);

    answer = myDataBase.get("login2");

    EXPECT_EQ(answer, nullptr);
}
