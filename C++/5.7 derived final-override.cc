class Queue{
private:
    int previous;
    const int consequence;
public:
    explicit Queue(const int n){cout << n << endl;};
    void Permutation() const;   // can't change parameter in this class
    
    /**
     * final indicates that you can't redefine Queue::suite() anymore    
     */
    bool suite() const final{
        // previous = 100; // cant change because of const
        return consequence;
    }
    /**
     * override is contrast to final
     * it indicates that you have to redefine this method
     */
    bool suite(int x) const override{
        return x == consequence;
    }
    


    
}

Queue::Queue(int x){
    consequence = x;  // not acceptable
}

Queue::Queue(int x) : consequence(x){  // initialize consequence to x
}

Queue::Queue(int x) : previous(10), consequence(x){  // initialize consequence to x
}

Queue::suite(int x){  // this has to be redefined for 'override'
    if(x<0) return false;
    else return x == consequence;
}

int x = 100;
Queue & rf_qr = x;  // &qr(100)
Queue * pt_qr = &x;
rf_qr.Permutation();  // invoke with reference
pt_qr->Permutation();  // invoke with pointer