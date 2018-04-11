var bonus = {
  length:2,
  0:'first',
  1:'second'
};
var sliced = Array.prototype.slice.call(bonus);     // ['first', 'second']
var sliced = Array.prototype.slice.call(bonus, 0);  // ['first', 'second']
var sliced = Array.prototype.slice.call(bonus, 1);  // ['second']

/**
 * objCur.call(objToOfferThis [,arg1 [,arg2...]]) 
 * objCur.apply(objToOfferThis [, argArray]) 
 * Uses methods of another object to replace of current
 * Uses for Multiple Inheritance
 */
function Perfume(){     // [pərˈfju:m]
    this.lily = function(bunch){console.log(bunch + ' Perfume.lily.');}
    this.fart = function(){console.log('Perfume is not fart!!');}
}

function Fume(){        // [fjum]
    this.lily = function(bunch){console.log(bunch + ' Fume.lily.');}
    this.fart = function(){console.log('May fart be perfume?');}
    this.Call = function(bunch){this.lily(bunch);}
}
function Flavor(){      // [ˈflevɚ]
    Perfume.call(this);
    Fume.call(this);
}

var fp = new Flavor();
fp.lily(100);  // inherit successfully, inherit the last one. 100 Fume.lily

/**
 * Uses Call() to call methods of another object
 */
var p = new Perfume();
var f = new Fume();
// same as var arr = [300];  f.lily.apply(p, arr);
f.lily.call(p, 300);  // it'll not change when has the same method of an object. 300 Fume.lily
/**
 * (f.lily).call(p, 300);  so it uses f.lily() to call p (to offer `this`)
 */

f.Call.call(p, [500]);  // Uses p to offer this, so this.lily(bunch) is p.lily(bunch)
                        // 500 Perfume lily