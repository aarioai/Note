/**
 * func map<U>(transform: (T) -> U) -> U[]
 * func filter(includeElement: (T) -> Bool) -> T[]
 * func reduce(inital: U, combine: (U, T) -> U) -> U
 */
func morale(palette: Int) {print(palette)}
[1, 2, 3].map({v: Int in morale(palette: v)})
[1, 2, 3].map(morale)                                    // skillful


var filteredArr : [Int] = [1, 2, 3].filter({$0 > 2})
var reducedArr : [Int] = [1, 2, 3].reduce(0, {$0 + $1})  // 0+1, 1+2, 2+3
var reducedArr : [Int] = [1, 2, 3].reduce(0, +)          // skillful
