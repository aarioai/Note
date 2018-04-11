function allergic(){        // T allergic(){}
    var resist = "rash";
    return resist;
}

var symptom = allergic;    // T (*symptom)() = allergic;
var allergen = allergic;   
symptom === allergen;   // true: allergic === allergic
symptom() === allergen(); // true: rash
var brutal = new allergic();   // 
var mega = new allergic();
brutal === mega;  // false


function infection(){       // T (*infection())(){}   T (* ((*)()))()
    return function(){                           
        return "pathogen";
    }
}
var resistance = infection;   // T (* ((*resistance)()))() = infection;
var syphilis = infection;     
resistance === syphilis;  // true: infection === infection
resistance() === syphilis(); // false: infection() === infection()
resistance()() === syphilis()();  // true: pathogen