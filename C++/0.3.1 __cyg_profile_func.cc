/**
 * g++ -std=c++11 -finstrument-functions
 *  void __cyg_profile_func_enter(void *addr_of_this_fn, void *call_addr);
 *  void __cyg_profile_func_exit(void *addr_of_this_fn, void *call_addr);
 */
#include <iostream>
using namespace std;

#ifdef __GNUC__
int depth_ = -1;
extern "C" {
    void __cyg_profile_func_enter(void *, void *) __attribute__((no_instrument_function));
    void __cyg_profile_func_exit(void *, void *) __attribute__((no_instrument_function));
    #define sustainable(fn, caller) \
        do{ \
            printf("%d, %s: fn = %p, caller = %p\n", depth_, __FUNCTION__, fn, caller); \
        } while(0)
    void __cyg_profile_func_enter(void *fn, void *caller){
        printf("Enter: %d\n", depth_);
        depth_++;
        sustainable(fn, caller);
    }
    void __cyg_profile_func_exit(void *fn, void *caller){
        printf("Exit: %d\n", depth_);
        depth_--;
        sustainable(fn, caller);
    }
}
#endif

void sustain() {
    printf("sustain(): %d\n", depth_);
    int depth_ = 100;
}

class Suture
{
    public:
    void sultry() {
        printf("Suture::sultry(): %d\n", depth_);
    }
    
};

int main(int argc, char **argv) {
    sustain();
    Suture suture;
    suture.sultry;
    
}