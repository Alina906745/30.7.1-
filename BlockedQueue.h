#pragma once
#include <mutex>
#include <condition_variable>

template<class T>

class BlockedQueue
{
public:
    void push(T& item)
    {
        lock_guard<mutex> l(m_locker);
       
        m_task_queue.push(item);
        
        m_notifier.notify_one();
    }
    
    void pop(T& item)
    {
        unique_lock<mutex> l(m_locker);
        if (m_task_queue.empty())
            
            m_notifier.wait(l, [this] {return !m_task_queue.empty(); });
        item = m_task_queue.front();
        m_task_queue.pop();
    }
   
    bool fast_pop(T& item)
    {
        lock_guard<mutex> l(m_locker);
        if (m_task_queue.empty())
           
            return false;
       
        item = m_task_queue.front();
        m_task_queue.pop();
        return true;
    }
private:
    mutex m_locker;
   
    queue<T> m_task_queue;
   
    condition_variable m_notifier;
};

