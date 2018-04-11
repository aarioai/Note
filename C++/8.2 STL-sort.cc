/**
 * std::sort(ptr_begin, ptr_end [,sort_func])
 */

class Assorted{
    public:
    int detached() const;
};
inline bool sortie(const Assorted &divide, const Assorted &fission){ // func-ptr
    return (divide.detached() < fission.detached());
}

Assorted assorted[30];

/**
 * Common functions and NSMFs are all pointers
 * Though it's an 'inline function', it's a pointers. It means 'sortile' is a 
    ptr in sort(), but not a 'inline function' --> slowly
 * Using lambda function or function objector to instead a function
 */
sort(assorted, assorted+30, sortie);//sortie is func-ptr, not 'inline' in sort()


bool classify = [](const Assorted categorize, const Assorted depart){
    return (categorize.detached() < depart.detached());
}
sort(assorted, assorted+30, classify);
sort(assorted, assorted+30, [](const Assorted categorize, const Assorted depart){return (categorize.detached() < depart.detached());} );


struct Apportion: public binary_function<Assorted, Assorted, bool>{
    bool operator()(const Assorted &division, const Assorted &fissile) const{
        return sortie(division, fissile);
    }
}
sort(assorted, assorted+30, Apportion());