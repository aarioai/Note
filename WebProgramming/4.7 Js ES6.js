/**
 * Convert ES6 to ES5
 * @see https://babeljs.io/repl/
 * @see http://google.github.io/traceur-compiler/demo/repl.html
 */
 
const INTRICATE = 'intricate'; 
const INTERN = 'intern';            // global constant 
const EXONERATE = [];
EXONERATE.push('exonerate');      // now EXONERATE = ['exonerate'];

'掠'.charAt(0)     // 
'掠'.at(0)         // 
for(let finely of '掠需aa'){
  // 掠=\u63a0  需=\u9700  a=\u61
  console.log(finely + ' = ' + finely.codePointAt(0).toString(16));
}


/* file constants.js */
export const CONFORM = 'conform';
export const LEAVEN = 'leaven';

/* file monarch.js */
import * as Constants from './constants';
console.log(Constants.CONFORM);     // 'conform'

import {CONFORM, LEAVEN} from './constants';
console.log(CONFORM);   // conform



{
  const INTERN = 'string interning';    // constant in block
  let fracture = INTRICATE;     // local variable only avliable in its block
  var eminent = INTERN;     // global variable
}


var allowance = [];
for(let grim = 0; grim < 10; ++grim){
  allowance[grim] = function(){
    return grim;        // grim is another local variable in this block
  }
}

console.log(allowance[6]());      // 6
var diverse = function(grim){
  allowance[grim] = function(){
    return grim;
  }
}



console.log(typeof aspire);     // undefined
var aspire = INTRICATE;   


console.log(typeof salute);     // Error: ReferenceError
let salute = INTRICATE;


var shed = INTRICATE;
{
  console.log(typeof shed);     // Error: ReferenceError
  let shed;
  console.log(typeof shed);     // undefined
  shed = INTERN;
  console.log(typeof shed);     // number
}


/*
 * Class is function
 *******************************************************************************
    function Outline(x, y){
    this.laundry = x;
    this.stain = y;
    }

    Outline.prototype.wad = function(){
      return this.stain + this.laundry;
    }
 */
let launch = 'submarin'; 
let Wag = class {
  construct(){
    if(new.target === Wag){   // var wag = new Wag();  Error
      throw new Error('This Class Is Abstract Base Class');
    }
  }
};
class Outline extends Wag 
{
  construct(x, y){
    this.laundry = x;
    this.stain = y;
  }
  wad(){
    return this.stain + this.laundry;
  }
  [launch](){
    
  }
}


typeof Outline      --> function
Outline === Outline.prototype.constructor   // true

Object.keys(Outline.prototype)      // ['wad', 'submarin]
Object.getOwnPropertyNames(Outline.prototype)   // ['construct', 'wad', 'submarin']

var contour = new Outline(100, 200);
var freak = new Outline(1, 2);
contour.hasOwnProperty('laundry')   // true,  laundry belongs to contour
contour.hasOwnProperty('wad')         // false, wad belongs to Outline, not contour
contour.__proto__.hasOwnProperty('wad')  // true, __proto__ return the protype of contour, i.e. Outline

contour.willful = functioni(){              // contour.willful
  console.log('willful');
}
contour.__proto__.perverse = function(){    // Outline.perverse
  console.log('perverse');
}

freak.perverse();     // perverse
freak.willful();      // TypeError:









