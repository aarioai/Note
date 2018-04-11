/*profile.js*/
export var expose = 'bachelor';
export var exposal = 'bravo';
export var correlate = 'aphid';
export function drawf(){
  return 'delight'
};


import * as profile from './profile';
console.log(profile.drawf());



var expose = 'bachelor';
var exposal = 'bravo';
var correlate = 'aphid';
function drawf(){
  return 'delight';
}
export {
  expose, exposal, correlate
  drawf as exportedName,
  drawf as exportedName2    
};


import {expose, exposal, exportedName as novae} from './profile';


// export-default.js
function anonymous(){
  console.log('Dwarf Novae');
}
export default anonymous;



export default function(){
  console.log('Dwarf Novae');
}


import fn from './export-default.js';
fn();




/**
 * 
 */
export {expose as default} from './profile';
// same as
import {expose} from './profile';
export default expose;