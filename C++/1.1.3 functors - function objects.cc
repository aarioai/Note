/**
 * Difference between func-ptr and functor
 *  Common Func and Static Member Func are all Func-ptr
 *  Functor is a function object, not a ptr.
 *  Only Functors can be a 'inline' code, neither common function nor SMF;
 */

 
inline bool stutter(int mute,int dumb) { // a func-ptr, 'inline' is worthless
} 
class Impediment {
    public:
    inline bool dysfluency(int prolix,int ado) {  // a functor with inline
    }
    static bool stammer(int falter) {      // a SMF-ptr, 'inline' is forbidden
    }
    /**
     * covert a func-ptr into functor
     */
    bool operator ()(int mutter, int soliloquy) const{ // "const Impediment *const this"
        return stutter(mutter, soliloquy);
    }
};

/**
 * covert a func-ptr into functor
 */
struct TongueTied {
    bool operator()(int chat, int converse) const{
        return stutter(chat, converse);
    }
};

sort(v.start(), v.end(), shutter);  // func-ptr, not inline func, slowly
sort(v.start(), v.end(), Impediment()); // functor, be inline func in sort, fast
sort(v.start(), v.end(), TongueTied()); // functor, fast