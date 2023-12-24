?#prgma once
#include <queue>
#include <future>
#include <condition_variable>
#include <vector>

using namespace std;


typedef function<void()> task_type;


typedef void (*FuncType) (int*, int, int);


class ThreadPool
{
public:
    ThreadPool();
    
    void start();
    
    void stop();
   
    void push_task(FuncType f, int* array, int begin, int end);
 
    void threadFunc(int qindex);
private:
   
    int m_thread_count;
    
    vector<thread> m_threads;
    
    vector<BlockedQueue<task_type>> m_thread_queues;
    
    int m_index;
};
