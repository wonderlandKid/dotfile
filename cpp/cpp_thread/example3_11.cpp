#include <thread>
#include <mutex>
#include <memory>

using namespace std;

shared_ptr<int> resource_ptr;
mutex resource_mutex;

void foo(){
    unique_lock<mutex> lk(resource_mutex);
    if(!resource_ptr){
        resource_ptr.reset(new int(1));
    }
    lk.unlock();
    resource_ptr->f();
}
