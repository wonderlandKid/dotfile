#include <iostream>
#include <mutex>
using namespace std;
class some_big_project {};
void swap(some_big_project& lhs, some_big_project& rhs);
class X {
   private:
    some_big_project some_detail;
    mutex m;

   public:
    X(some_big_project const& sd) : some_detail(sd) {}
    friend void swap(X& lhs, X& rhs) {
        if (&lhs == &rhs) return;
        unique_lock lock_a(lhs.m, defer_lock);
        unique_lock lock_b(rhs.m, defer_lock);
        lock(lock_a, lock_b);
        std::swap(lhs.some_detail, rhs.some_detail);
    }
};
