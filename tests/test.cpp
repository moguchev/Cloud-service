// Copyright 2019 (c) <Cloud9>

//
// Created by Андронов Дмитрий on 2019-04-08.
//
#include <unordered_map>
#include "classes.hpp"

    class FakeDataBase: public AbstractDataBase {
    private:
        std::unordered_map <std::string , std::string> baseData;
    public:
        std::string get(const std::string& data) const override;
        void makeNote(const std::string& root,
                      const std::string& data) const override;
        void deleteNote(const std::string& str) override ;
        ~FakeDataBase() = default;
    };

// Test authentication

    class TestAuthentication : public ::testing::Test {
    public:
        TestAuthentication() {
            FakeDataBase fakeBase;
        }
        ~TestAuthentication() {}

        void SetUp () {
            FakeDataBase fakeBase;
            fakeBase.makeNote("Dima" , "123");

        }
    };


TEST_F (TestAuthentication ,  properAuth) {
    Authentication auth ("Dima" , "123");
    Condition condition = auth.execute ();
    EXCEPT_EQ (condition , Condition::OK);
}

TEST_F (TestAuthentication , badAuth) {
    Authentication auth ("alexey" , "1255");
    Condition condition = auth.execute ();
    EXCEPT_EQ (condition , Condition::ERROR);
}


// test registration
class TestRegistration  : public ::testing::Test {
public:
    TestRegistration() {
        FakeDataBase fakeBase;
    }
    ~TestSerialization() {}
    void SetUp () {
        fakeBase.makeNote("dima" , "123");
    }
}


TEST_F(TestRegistration , properRegistration) {
    Registration reg ("Alexey" , "987");
    Condition condition = reg.execute();
    EXCEPT_EQ (condition , Condition::OK);
}

TEST_F (TestRegistration , badRegistration) {
    Registration reg ("Dima" , "abc");
    Condition condition = reg.execute () ;
    EXCEPT_EQ (condition , Condition::ERROR);
}

// Test isExistUser
 class TestIsExistUser  : public ::testing::Test {
public:
    TestIsExistUser() {
        FakeDataBase fakeBase;
    }
    ~TestIsExistUser() {}
    void SetUp () {
        fakeBase.makeNote("dima" , "123");
    }
}


TEST_F (TestIsExistUser , UserExist) {
    isExistUser testUse ("dima");
    Condition condition = testUse.execute();
    EXCEPT_EQ (condition , Condition::OK);
}


// test Add New Client

TEST(PushRequestTest , ProperTest) {
    RestServer restServer(nullptr);
    Request req;
    int size = restServer.sizeQueue();
    restServer.pushRequest(req);
    int newSize = restServer.sizeQueue()
    EXCEPT_EQ (newSize - size , 1);

}

TEST(PushRequestTest , ProperTest) {
    RestServer restServer(nullptr);
    Request req;
    int size = restServer.sizeQueue();
    restServer.pushRequest(req);
    int size = restServer.sizeQueue();
    restServer.popRequest();
    int newSize = restServer.sizeQueue();
    EXCEPT_EQ (size - newSize , 1);
}





int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

