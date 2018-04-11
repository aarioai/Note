


function Jujube(yield){     // ['dʒu:dʒu:b]   [jild]
    this.yield = yield;
    
    // method of object Jujube
    this.boil = function(){
        console.log(this.yield + ' this.boil will kill Jujube.prototype.boil');
    }
}

// method of class Jujube
Jujube.boil = function(){
    console.log('Class::boil static');
}

// method of prototype Jujube
Jujube.prototype.Pastry = function(){
    console.log(this.yield + ' Jujube Pastry.');
}

Jujube.prototype.boil = function(){
    console.log('prototype boil will not run, because of this.boil');
}


var j = new Jujube(100);
/******************************************************************************
* the sequence of new a function
    var j = {};   // initial an object j 
    j.__proto__ = Jujube.prototype;
    Jujube.call(j);  // constructs a j
* which means that j.__proto__ === Jujube.prototype in FF and Chrome
******************************************************************************/

j.boil();  
Jujube.boil();
j.Pastry();
j.boil();  //100 this.boil will kill Jujube.prototype.boil
Jujube.prototype.Pastry = null;  // to destroy a prototype



/* A.prototype = new B();   A clone B */
function Cucumber(){
}
Cucumber.prototype = new Jujube();
var c = new Cucumber(300);  // 300 this.boil will kill Jujube.prototype.boil
c.boil;     


/* C.prototype = new B();  if C and B both have the same methods, it doesn't override. */
function Pumpkin(yield){
    this.yield = yield;
    this.boil = function(){
        console.log('Pumpkin ' + this.yield + ' Pumpkin');
    }
}
Pumpkin.prototype = new Jujube(500);
var p = new Pumpkin(800);
p.boil();  // 800 Pumpkin

j.boil.call(p);  //800 this.boil will kill Jujube.prototype.boil
Jujube.boil.call(p);  // Class::boil static