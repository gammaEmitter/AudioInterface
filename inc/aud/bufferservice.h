#pragma once
#include <queue>
#include "iodef.h"
/*
 *  This system will manage wokers that collect the samples from registered sources of [Channel, Bus]
 *  Every channel has got a ringbuffer, every Bus has got a ringbuffer
 *
 *  -- Half buffer transfer system --
 *      MasterBus collects samples from all its sources into half of the buffer --> FirstFilled
 *      outputCallback consumes other half of buffer                             --> SecondConsumed
 *      MasterBus collects samples from all its sources into other half buffer  --> SecondFilled
 *      outputCallback consumes first half of buffer                             --> FirstConsumed
 *     
 *
 *      AudioInterface class holds those signals? Worker thread polls a message queue?
 *
 *      I dont know yet, if every other Bus should have a woker aswell to collect samples
 *      or simply call ->pull() from it's ringbuffer (then it could work without a ringbuffer tbh)
 *      
 *
 *      MasterBus = af.master()
 *
 * */

// std::jthread ignores return values. use std::promise
// or std::async for that.
//

enum BlockedHalf {
    First,
    Second
};
class TransferMessage {
public: 
    enum MessageType {
        None,
        StartSumming,
        StopSumming,
        FillFirst,
        FillSecond,
        FirstFilled,
        SecondFilled,
    };
    TransferMessage(MessageType type) : m_type(type) {};
    ~TransferMessage() = default;
    MessageType m_type = MessageType::None;
private:
};
/* class BufferController {
public:
    BufferController() = default;
    void send (TransferMessage&& message);
private:
    std::queue<TransferMessage> m_messagequeue {};
    SampleOut source = nullptr; 

};
*/
class BufferFiller;
class BufferConsumer;
class BufferService;

class BufferService {
public:
    BufferService();
    ~BufferService() = default;
    BufferService(BufferService& other) = delete;
    BufferService& operator= (BufferService& other) = delete;
    BufferService(BufferService&& other) = delete;
    BufferService& operator= (BufferService&& other) = delete;

    void setSource(SampleOut fillerSource);
    void setDestination(RingbufferPtr consumerDest);
    void startTransfer();
    void unlock();
    BlockedHalf blocked = BlockedHalf::First;
    std::unique_ptr<std::array<float,AudIO::RingbufferSize>> m_buffer = nullptr;

private:
    std::unique_ptr<BufferConsumer> m_consumer = nullptr;
    std::unique_ptr<BufferFiller> m_filler = nullptr;

};

class BufferFiller {
public:
    
    void sendMessage(TransferMessage&& message);
    void receiveMessage(TransferMessage&& message);
    ~BufferFiller() = default;

private:
    friend class BufferService;

    BufferFiller() = default;
    BufferFiller(BufferFiller& other) = delete;
    BufferFiller& operator= (BufferFiller& other) = delete;
    BufferFiller(BufferFiller&& other) = delete;
    BufferFiller& operator= (BufferFiller&& other) = delete;
    static std::unique_ptr<BufferFiller> getInstance();
    void processMessage (TransferMessage&& message);
    SampleOut m_source = nullptr;
    BufferConsumer* m_consumer = nullptr;
    BufferPtr m_servicebuffer = nullptr;
};

class BufferConsumer {
public:
    void sendMessage(TransferMessage&& message);
    void receiveMessage(TransferMessage&& message);

    ~BufferConsumer() = default;
private:
    friend class BufferService;

    BufferConsumer() = default;
    BufferConsumer(BufferConsumer& other) = delete;
    BufferConsumer& operator= (BufferConsumer& other) = delete;
    BufferConsumer(BufferConsumer&& other) = delete;
    BufferConsumer&& operator= (BufferConsumer&& other) = delete;
    static std::unique_ptr<BufferConsumer> getInstance();
    void processMessage (TransferMessage&& message);
    RingbufferPtr m_dest = nullptr;     //pointer to output buffer of PortAudio callback
    BufferFiller* m_filler = nullptr;
    BufferPtr m_servicebuffer = nullptr;
};

