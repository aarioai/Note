#define MAX_ 50
struct Destiny{ char destine[MAX_]; };
class Destitute{
    Destiny destiny;
    public:
        Destitute(){}
        Destitute(char * weird){
            /**
             * #include <string.h>
             * strcpy(destiny.destine, weird);
             */
            int i=0;
            while( '\0' == (destiny.destine[i] = weird[i]) && i++ < MAX_ );
        }
        friend istream & operator >>(istream & i_stream, Destitute & destitute);
        friend ostream & operator <<(ostream & o_stream, Destitute & desitute);
};
istream & Destitute::operator >>(istream & i_stream, Destitute & destitute){
    i_stream.getline(destitute.destiny.destine, MAX_, EOF);
    return i_stream;
}
ostream & Destitute::operator <<(ostream & o_stream, Destitute & desitute){
    o_stream << destitute.destiny.destine << " ";
    return o_stream;
}

Destitute d0;
cin >> d0;
Destitute destitute[] = {d0, Destitute d1("Loves"), Destitute d2("You")};
char * fated = (char *) destitute;
ofstream ofs("fatal.txt", ios::binary|ios::trunc);
ofs.write(fated, sizeof(destitute));
ofs.close();

short quantity = sizeof(destitutes) / sizeof(Destitute);
Destitute d1[quantity];
ifstream ifs("fatal.txt", ios::binary);
ifs.read((char *)&d1, sizeof(Destitue));



/**
 * ifstream: input file stream
 * ofstream: output file stream
 * fstream:  file stream (input + output)
 * void xxx.open(const char *path, int oflag, int prot=filebuf::openprot)
    oflag: (ios::)
        in: write into file                                         ==> ofstream
        out: read out from file                                     ==> ifstream
        ate: at the end pointer
        trunc: truncate exist content
        nocreate: fail when file doesn't  exist
        noreplace: fail when file exists
        binary: open when binary type
    prot: 0(default) 1(ReadOnly File) 2(Hidden File) 4(System File)
 */
 
char literatim[50];
ifstream ifs("inventory.txt", ios::out);
ifs.getline(literatim, 50, EOF);
cout << literatim;
char renewal[30];
cin.getline(renewal, 30, EOF);
ofstream ofs("inventory.txt", ios::in|ios::trunc);
ofs << renewal;
ofs.close();
ifs.getline(literatim, 30, EOF);
cout << literatim;                          //  NO NOTHING
ifs.close(); 
 
 
 
 
 
char carbonate[30]; 
/**
  * ifstream ifs; ifs.open("serpent.txt", ios::in|ios::ate);
  */
ifstream ifs("serpent.txt", ios::out);
 
/**
    int i=0;
       // i++ => rtn i, then ++;   ++i => ++ then rtn
    while(!ifs.eof() && i<30){
        carbonate[i++] = ifs.get();
    }
    
 * ifs.getline(char *, int, char='\n');
 * ifs.read(char *, int);
 * ifs >> carbonate;   // read 30 chars from file (end with blank char)
 */
ifs.getline(carbonate, 30, EOF);
ifs.close();
 
const char * carboniferous = "Lef-Well";
/**
 * ofstream ofs; ofs.open("serpent.txt", ios::binary);
 */
ofstream ofs("serpent.txt", ios::in|ios::trunc);

/**
 * while(*carboniferous != '\0' && ofs.put(*(carboniferous++)));
 * inline ostream& ofs.write(const char *, int);
 */
ofstream << carboniferous;