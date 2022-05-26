#pragma once

#include <mutex>
#include <condition_variable>

#include "Event.h"
#include "Utils.h"


struct Compare
{
    bool operator()(const std::shared_ptr<Event> &this_, const std::shared_ptr<Event> &that_) {
        return this_->timeStamp() < that_->timeStamp();
    }
};

class PriorityQueue
{
private:
    mutable std::mutex mutex_;
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, Compare> pq_;
    std::condition_variable empty_;
    std::condition_variable full_;
    size_t max_size_{10};
public:
    explicit PriorityQueue() : mutex_(), pq_(), empty_(), full_() {}
    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;

    void push(const std::shared_ptr<Event>& event_)
    {
        UniqueGuard lock(mutex_);
        if (pq_.size() == max_size_)
            full_.wait(lock);
        pq_.push(std::move(event_));
        empty_.notify_all();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return pq_.empty();
    }

    std::shared_ptr<Event> pop()
    {
        UniqueGuard lock(mutex_);
        if (pq_.size() == 0)
            empty_.wait(lock);
        std::shared_ptr<Event> val = std::move(pq_.top());
        pq_.pop();
        full_.notify_all();
        return val;
    }
};
