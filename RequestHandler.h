#pragma once

#include "ThreadPool.h"

class RequestHandler
{
public:
    RequestHandler();
    ~RequestHandler();
  
    void pushRequest(FuncType f, int* array, int begin, int end);
private:
    
    ThreadPool m_tpool;
};
