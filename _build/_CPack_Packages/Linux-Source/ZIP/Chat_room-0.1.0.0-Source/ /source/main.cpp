#include "../include/chat_room.h"

int main()
{
    ChatRoom chatRoom_1("ChatRoom_1"), chatRoom_2("ChatRoom_2");
    User user_1("User_1"), user_2("User_2"), user_3("User_3");

    user_1.JoinChatRoom(chatRoom_1);
    user_2.JoinChatRoom(chatRoom_2);
    user_3.JoinChatRoom(chatRoom_1);
    user_3.JoinChatRoom(chatRoom_2);

    chatRoom_1.SendMessage("Hi, nice to meet you!");
    chatRoom_2.SendMessage("I'm Taeguk Kwon!");
}
