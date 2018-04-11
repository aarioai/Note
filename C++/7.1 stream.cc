/**
 *                ios
 *      istream         ostream        --> iostream inherits istream and ostream
 *  ifstream    iostream    ofstream
 *              fstream
 */

class Yacht{
    private:
        char owner[50];
        int capacity;
    public:
        Yacht(){}
        friend istream& operator >>(istream& i_stream, Yacht& yacht);
        friend ostream& operator <<(ostream& o_stream, Yacht& yacht);
};
istream& Yacht::operator >>(istream& i_stream, Yacht& yacht){
    i_stream >> yacht.owner;
    i_stream >> yacht.capacity;
    return i_stream;
}
ostream& Yacht::operator <<(ostream& o_stream, Yacht& yacht){
    o_stream << "Owner: " << yacht.owner <<"; Capacity: " << yacht.capacity;
    return o_stream;
}
 
 
 
/******************************************************************************/ 
char carbohydrate[50];
/**
 * "Lef" into non-buffer, "Well" into buffer
 */
cin >> carbohydrate;  //input  "  Lef Well", 
cout << carbohydrate;  // output "Lef"

/**
 * cin.getline(char *pstr, int n, char delim)
 */
cin.getline(carbohydrate, 50, '#');  // input "  Lef Well#Love"

/**
 * EOF  = Ctrl+D in Linux; Ctrl+Z in Win
 * Likes cin.getline(carbohydrate,50,EOF);
 * But it may ends with `EOF`
 * i++ => rtn i then ++;  ++i => ++ then rtn;
 */
 short i = 0;
 while((i<50) && (carbohydrate[i++] = cin.get()) != EOF);





/**
 * endl is used to flush buffer
 */
cout << carbohydrate << endl;  // output "  Lef Well"

/**
 * cout.write(char *, int)
 */
cout.write(carbohydrate, 50);