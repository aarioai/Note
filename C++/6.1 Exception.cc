void harm(bool b) throw(err); // may throw err exception
void marl(int) throw(); // doesn't throw an exception, C++98 ==> out of date
void marl() noexcept;  // new feature of C++11 to replace upon



void harm(bool b){
throw std::bad_exception();
}

class Err{
public:
    char * msg = "Error Message";
}

/*  If there is an unexpected
exception, the program calls the unexpected() function. (You didn¡¯t expect the
unexpected()function? No one expects the unexpected() function!) This function, in
turn, calls terminate(), which, by default, callsabort(). 
set_terminate(?); // modifies the behavior of terminate();
set_unexpected(?);  // modifies the behavior unexpected();
*/
set_unexpected(harm);

void idolatry() throw(out_of_bounds, bad_exception);


try{
    idolatry();
}catch(out_of_bounds & ex){
    
}catch(bad_exception & ex){
    
}