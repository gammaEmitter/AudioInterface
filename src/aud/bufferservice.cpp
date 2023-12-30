#include "bufferservice.h"
#include "iodef.h"
#include <utility>

BufferService::BufferService() {
    m_buffer = std::make_unique<std::array<float,AudIO::RingbufferSize>>();
    m_filler = BufferFiller::getInstance();
    m_consumer = BufferConsumer::getInstance();
    m_filler->m_servicebuffer = m_buffer.get();
    m_consumer->m_servicebuffer = m_buffer.get();
}

void BufferService::setSource(SampleOut fillerSource) {
    m_filler->m_source = fillerSource;
}
void BufferService::setDestination(RingbufferPtr consumerDest) {
    m_consumer->m_dest = consumerDest;
}

void BufferService::startTransfer() {
    blocked = BlockedHalf::First; 
    m_consumer->sendMessage(TransferMessage(TransferMessage::FillFirst));
}

void BufferService::unlock() {
    if (blocked == BlockedHalf::First) {
        m_consumer->sendMessage(TransferMessage(TransferMessage::FillSecond));
        blocked = BlockedHalf::Second;
    } else if (blocked == BlockedHalf::Second) {
        m_consumer->sendMessage(TransferMessage(TransferMessage::FillFirst));
        blocked = BlockedHalf::First;
    }
}

std::unique_ptr<BufferFiller> BufferFiller::getInstance() {
    return std::unique_ptr<BufferFiller>(new BufferFiller());
}

void BufferFiller::sendMessage(TransferMessage&& message) {
    m_consumer->receiveMessage(std::move(message));
}
void BufferFiller::receiveMessage(TransferMessage&& message) {
    processMessage(std::move(message));
}

void BufferFiller::processMessage(TransferMessage&& message) {
    switch (message.m_type) {
        case TransferMessage::FillFirst:
            for (int i = AudIO::RingbufferStart; i < AudIO::RingbufferHalf; i++) {
                (*m_servicebuffer).at(i) = 0.f;
            }
            break;
        case TransferMessage::FillSecond:
            for (int i = AudIO::RingbufferHalf; i < AudIO::RingbufferSize; i++) {
                (*m_servicebuffer)[i] = 0.f;
            }
            break;
        default:
            
            break; 
    }
}

std::unique_ptr<BufferConsumer> BufferConsumer::getInstance() {
    return std::unique_ptr<BufferConsumer>(new BufferConsumer());
}
void BufferConsumer::sendMessage(TransferMessage&& message) {
    m_filler->receiveMessage(std::move(message));
}
void BufferConsumer::receiveMessage(TransferMessage&& message) {
    processMessage(std::move(message));
}

void BufferConsumer::processMessage(TransferMessage&& message) {
    switch (message.m_type) {
        default:
            
            break;
    }
}
