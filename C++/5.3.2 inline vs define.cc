#define Plus(x) x+x
cout << 5 * Plus(5);   // print 30 (= 5 * 5 + 5 )

#define Plus(x) x+x;   // ends with a semicolon
cout << 5 * Plus(5)     // print 30, without a semicolon at end

