#include "../include/chat_room.h"

void Observable::Attach(Observer& observer)
{
    observerSet_.insert(&observer);
}

void Observable::Detach(Observer& observer)
{
    observerSet_.erase(&observer);
}

void Observable::Notify(const void* dataKey)
{
    for (auto& observer : observerSet_)
    {
        observer->Update(*this, dataKey);
    }
}

ChatRoom::ChatRoom(std::string name)
    : name_(std::move(name))
{}

void ChatRoom::SendMessage(std::string const& message)
{
    Notify(&message);
}

std::string ChatRoom::GetName() const { return name_; }

std::string const& ChatRoom::GetDataFromKey(design::AccessKey<Observer>,
                                    const void* dataKey)
{
    assert(dataKey);
    return *reinterpret_cast<std::string const*>(dataKey);
}

User::User(std::string name)
    : name_(std::move(name))
{}

void User::Update(Observable& observable, const void* dataKey) {
    auto& chatRoom = static_cast<ChatRoom&>(observable);
    assert(chatRoomSet_.find(&chatRoom) != std::end(chatRoomSet_));

    std::cout << "[" << name_ << "][" << chatRoom.GetName() << "] " <<
        chatRoom.GetDataFromKey(GetAccessKey(), dataKey) << std::endl;
}

void User::JoinChatRoom(ChatRoom& chatRoom)
{
    chatRoomSet_.insert(&chatRoom);
    chatRoom.Attach(*this);
}
