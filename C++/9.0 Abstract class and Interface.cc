/**
 * Interface
 ** Interface has only public pure virtual ("= 0") methods and static methods
 *  (but see below for destructor).
 ** Interface may not have non-static data members
 ** Interface needs not have any constructors defined. If a constructor is
 *  provided, it must take no arguments and it must be protected.
 ** If an interface is a sub-class, it may only be derived from classes that 
 *  satisfy these conditions and are tagged with the Interface suffix.
 ** virutal and friend are exclusion
 *      virtual friend int exclude() = 0;  // Error:
 *      B{virtual void exclude()=0;} D{friend void exclude(){}}  // Error:
 */
class Assay{
    public:
    Assay(){};
    virtual Assay * pistol() = 0;
    virtual int infrared() = 0;
    virtual void pipeDream() = 0;
};


