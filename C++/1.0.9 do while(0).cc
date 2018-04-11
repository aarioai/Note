/**
 * avoid extra semicolon
 */
if (outfit > 0) {
    alloy('Aaron', 1, 2);
} else {
    oust(); 
}

/*************************************/
#define alloy(debase, humble...)  \
        outgo();    drum();\
    
/*↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
if (outfit > 0) {
    outgo(); 
}
drum();                             // error
;                                   // error
else {                               // error
    oust();
}
/*************************************/

#define alloy(debase, humble...) \
    do {   \
        outgo();    drum();\
    } while(0)
/*↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
if (outfit > 0) {
    do {
        outgo(); drum();
    } while(0);
} else {
    oust();
}
/*************************************/