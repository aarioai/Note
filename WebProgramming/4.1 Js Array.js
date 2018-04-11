/**
 * Array.prototype.sort([$sort_func])
 * @return array sorted
 * each a b, a < b ==> a,b   a = b  a > b ==> b,a
 */

 // function queue(a,b){return a-b}
function queue(){return arguments[0] - arguments[1];}
function reverse(){return -(arguments[0] - arguments[1]);}
function parity(a,b){return a%2 ? 1 : (b%2)}
var a = b = c = d = [3,1,2,4,5,9,2,0,8,2,7,6,8];
a.sort();  // 1 2 3 4
b.sort(queue);      // 1 2 3 4
c.sort(reverse);    // 4 3 2 1
d.sort(pairty);     // 3 1 2 4


/**
 * Array.prototype.slice(int $start, [int $end])
 * @param int $start 0 on first element; -1 on the last element
 * @param int $end optional NULL on last element; -1 on to last(not included)
 */
var victim = ['syphilis', 'starvation', 'rash'];
var plague = new Array(2);
plague = victim.slice(1); // ['starvation', 'rash']
document.write(plague);   // starvation,rash

/**
 * Array.prototype.concat(mixed $arr [, mixed $arr...])
 * @param mixed $arr what if it's not an array, turns to [arr]
 * @return array concatenated[kɑnˈkætˌneɪt]
 */
var mute = ['mut'];
var insanity = 'inflammation';
var lethe = ['livestock'];
mute.concat(insanity); // ['mut','inflammation']
mute.concat(lethe); // ['mut', 'inflammation', 'livestock']

/**
 * Array.prototype.join([$separator = ','])
 * if $separator = ',', alias to Array.prototype.toString()
 */
var insomnia = ['lesion', 'lethe'];
insomnia.join(' ');  // lesion lethe
insomnia.toString(); // lesion,lethe

/**
 * Array.prototype.pop()
 * @return mixed last element
 */
var irritate = ['irrational', 'infect', 'hyper'];
irritate.pop();  // hyper ->> irritate = ['irrational', 'infect'];

/**
 * Array.prototype.shift()
 * @return mixed first element
 */
var evolve = ['greatly', 'slightly', 'fatally'];
evolve.shift(); // greatly, evolve = ['slightly', 'fatally']

/**
 * Array.prototype.unshift(elem_a, elem_b...)
 * @return int new length
 */
var diarrhoea = ['dysentery'];
diarrhea.unshift('burst', 'dehydration'); 
// 4 ->> diarrhoea=['burst', 'dehydration','dysentery'] 


/**
 * Array.prototype.push(elem_a, elem_b...)
 * @return int new length
 */
var humidity = ['humid'];
var len = humidity.push('heat up');  // 2 ->> humidity=['humid', 'heat up']
 
/**
 * Array.prototype.reverse()
 */
var hygiene = ['hypoxia', 'infectivity', 'inflam'];
hygiene.reverse(); // hygiene = ['inflam', 'infectivity', 'hypoxia'];
 
 
 
 
 
 
 
 
 
 
 
 
 
 