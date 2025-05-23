#include <gtest/gtest.h>
#include <sstream>

#include "../source/chat_room.cpp"

class ObserverPatternTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация перед каждым тестом
    }

    void TearDown() override {
        // Очистка после каждого теста
    }
};

TEST_F(ObserverPatternTest, ChatRoomCreation) {
    ChatRoom chatRoom("TestRoom");
    EXPECT_EQ(chatRoom.GetName(), "TestRoom");
}

TEST_F(ObserverPatternTest, UserCreation) {
    User user("TestUser");
    // Проверяем, что пользователь создан
    SUCCEED();
}

TEST_F(ObserverPatternTest, SingleUserNotification) {
    ChatRoom chatRoom("TestRoom");
    User user("TestUser");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    user.JoinChatRoom(chatRoom);
    chatRoom.SendMessage("Hello World!");
    
    std::cout.rdbuf(old);
    
    EXPECT_NE(buffer.str().find("[TestUser][TestRoom] Hello World!"), std::string::npos);
}

TEST_F(ObserverPatternTest, MultipleUsersNotification) {
    ChatRoom chatRoom("TestRoom");
    User user1("User1"), user2("User2");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    user1.JoinChatRoom(chatRoom);
    user2.JoinChatRoom(chatRoom);
    chatRoom.SendMessage("Multi-user test");
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("[User1][TestRoom] Multi-user test"), std::string::npos);
    EXPECT_NE(output.find("[User2][TestRoom] Multi-user test"), std::string::npos);
}

TEST_F(ObserverPatternTest, MultipleChatRooms) {
    ChatRoom room1("Room1"), room2("Room2");
    User user("TestUser");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    user.JoinChatRoom(room1);
    user.JoinChatRoom(room2);
    room1.SendMessage("Message for Room1");
    room2.SendMessage("Message for Room2");
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("[TestUser][Room1] Message for Room1"), std::string::npos);
    EXPECT_NE(output.find("[TestUser][Room2] Message for Room2"), std::string::npos);
}

TEST_F(ObserverPatternTest, UserLeavesChatRoom) {
    ChatRoom chatRoom("TestRoom");
    User user("TestUser");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    user.JoinChatRoom(chatRoom);
    chatRoom.SendMessage("First message");
    
    chatRoom.Detach(user);
    chatRoom.SendMessage("Second message");
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("[TestUser][TestRoom] First message"), std::string::npos);
    EXPECT_EQ(output.find("[TestUser][TestRoom] Second message"), std::string::npos);
}

TEST_F(ObserverPatternTest, NoObservers) {
    ChatRoom chatRoom("TestRoom");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    chatRoom.SendMessage("No one should see this");
    
    std::cout.rdbuf(old);
    EXPECT_TRUE(buffer.str().empty());
}
