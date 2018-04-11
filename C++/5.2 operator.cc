class Condo {
    private:
        int condominium;
    public:
        Condo(int units):condominium(units){}
        int getCondominium() {
            return condominium;
        }

        
        /*
            Condo c;
            c.getCondominium();       
            c->getCondominium();  // reload operator ->
         */
        Condo * operator ->() {   
            return this;   
        }
        Condo & operator +=(Condo c) {
            condominium += c.getCondominium();
            return *this;
        }
        char operator[](int n) {
            const char * str = "Lef-Well";
            const int len = strlen(str);
            //ioo = is_out_len_
            bool ioo_len = n > (len - 1);
            return ioo_len ? '\0' : *(str + n);
        }
        /**
         * size_t = unsigned int in C++
         * Condo *c = new(50) Condo;
         * delete c;
         */
        void * operator new(size_t sz, char init = '\0') {
            char *pregnancy = new char[sz];
            *pregnancy = init;
            return pregnancy;
        }
        
        void operator delete(void *p) {
            char * condom = (char *) p;   // cast any-type point p to (char *)
            delete [] condom;
        }
        
        operator int() {
            
        }
        
                int operator ++(){   // ++Condo
            return ++condominium;
        }
        int operator ++(int) {  // Condo++
            return condominium += 10;
        }
        
        friend istream & operator >> (istream & i_stream, Condo & condo){
            i_stream >> condo.condominium;
            return i_stream;
        }
        friend ostream & operator << (ostream & o_stream, Condo & condo){
            o_stream << "Condominium: " << condo.condominium << endl;
            return o_stream;
        }
        
        
};

/*****************************************************************************/

class StringBad {
    public:
        char *str = new char[];
        StringBad(){
        
        }
        StringBad(char *str_){
            str = str_;
        }
        


        StringBad & operator=(const StringBad & str_) {
            if (this == &st)            // object assigned to itself
                return *this;          // all done
            delete [] str;  // free old string
            len = str_.len;
            str = new char [len + 1];   // get space for new string
            std::strcpy(str, st.str);   // copy the string
            return *this;  // return reference to invoking object
        }
        
        StringBad operator+(char *str_) {
            int len = strlen(str),
                add_len = strlen(str_),
                new_len = len + add_len;
            char * new_str = new char[new_len]
            
       
            return  new_str;
        }
        
};


StringBad a="100";   // same as StringBad a("100);
cout << a.str << endl;


a = a === "100" === "11";  // multi operator