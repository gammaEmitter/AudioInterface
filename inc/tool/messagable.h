#include <iostream>
#include <functional>
#include <deque>
#include <map>
#include <thread>

class Messagable;

struct Message {

    enum Execution {
        Queued,
        Immediate
    };

    const Messagable& mSender;
    const std::string sMessage;
    explicit Message (const Messagable& from, const std::string& message) : mSender(from), sMessage(message) {} 

};

class Messagable {
public:
    Messagable& send(Messagable& other,  const std::string& message, Message::Execution forced) {
        other.qMessages.push_back(Message(*this,{message}));
        if (forced) {
            other.checkMessage();
        }
       return *this;
    }
    void checkMessage () {
        if (!qMessages.empty()) {
            auto execution = std::thread(mBindings[qMessages.front().sMessage]);
            execution.detach();
            qMessages.pop_front();
        }
        return;
    }
    void bind(const std::string& word, std::function<void()> action) {
        mBindings[word] = action;
    }
private:
    std::deque<Message> qMessages;
    std::map<std::string,std::function<void()>> mBindings;

};

