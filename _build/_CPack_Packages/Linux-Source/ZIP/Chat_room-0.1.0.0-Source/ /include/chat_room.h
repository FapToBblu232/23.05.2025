#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace design
{
template <typename Accessor>
class AccessKey
{
private:
    friend Accessor;

    AccessKey() = default;
};

}

class Observable;

// 관찰자
class Observer
{
public:
    virtual ~Observer() = default;

    virtual void Update(Observable& observable, const void* dataKey) = 0;

protected:
    design::AccessKey<Observer> GetAccessKey() { return {}; }
};

// 관찰 대상
class Observable
{
public:
    virtual ~Observable() = 0;

    void Attach(Observer& observer);

    void Detach(Observer& observer);

    void Notify(const void* dataKey);

private:
    std::set<Observer*> observerSet_;
};

inline Observable::~Observable() = default;

class ChatRoom : public Observable
{
public:
    explicit ChatRoom(std::string name);

    void SendMessage(std::string const& message);

    std::string GetName() const;

    std::string const& GetDataFromKey(design::AccessKey<Observer>,
                                      const void* dataKey);

private:
    const std::string name_;
};

class User : public Observer
{
public:
    explicit User(std::string name);

    void Update(Observable& observable, const void* dataKey) override;

    void JoinChatRoom(ChatRoom& chatRoom);

private:
    std::string name_;
    std::set<ChatRoom*> chatRoomSet_;
};
