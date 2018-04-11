/**
 * Resource Acquisition Is Initialization
 */
void severe(){
    Silly *silly = new Silly;  // heap
    silly->billy();
    if(stealth())   // if ture, stops here. Makes heap leak
        return;
    susceptable();  // what if throw an exception? Stops here, heap leak left
    delete silly;   // It may not run to here... heap leak left
}

/**  RAII **/
class Acquisition{
    Acquisition(const Acquisition &);
    Acquisition &operator=(const Acquisition &);
    Silly *silly;
    public:
    explicit Acquisition(Silly *mutt):silly(mutt){}
    Silly *obtain(){return silly;}
    ~Acquisition(){delete silly;}
};

void severity(){
    Silly silly;
    Acquisition acquire(new Silly);
    acquire.obtain->billy();
    if(stealth())   // if ture, run Acquisition::~Acquisition && Silly::~Silly
        return;
    susceptible();  // if error, run Acquisition::~Acquisition && Silly::~Silly
    /**
     * what if stealth() and susceptible() are all correct, run
            Step 1: Acquisition::~Acquisition
            Step 2: Silly::~Silly
     */
}