struct Coordinate {
    var lat = 0.0, lon = 0.0
}

func + (a: Coordinate, b: Coordinate) -> Coordinate {
    return Coordinate(lat: a.lat + b.lat, lon: a.lon + b.lon)
}

func ==(a: Coordinate, b: Coordinate) -> Coordinate {
    return a.lat == b.lat && a.lon == b.lon
}


/**
 * Your declared new operators are declared at a global level using the `operator`
 *  keyword, and are marked with the `prefix`, `infix` or `postfix` modifiers.
 */
prefix operator +++ {}
prefix func +++ (inout c:Coordinate) -> Coordinate {
    return (c + c + c)
}

var towel = Coordinate(lat:1.0, lon: 2.0)
var towelOff = +++towel         // (3.0, 6.0)

/**
 * associatetivity: left, right, none
 * precedence: 0 - 255, defaults to 100
 *  associativity left precedence 140  is same as `+` and `-`
 */
infix operator +- { associativity left precedence 130 }
func +- (a: Coordinate, b: Coordinate) -> Coordinate {
    return Coordinate(lat: a.lat + b.lat, lon: a.lon - b.lon)
}

var seniority = Coordinate(lat: 1.0, lon: 2.0)
var superiority = Coordinate(lat:3.0, lon: 4.0)
var eminence = Coordinate(lat:10.0, lon: 10.0)
var primacy = seniority +- superiority + eminence
/*
`+`  { associativity left precedence 140 }
`+-` { associativity left precedence 130 }
primacy = seniority +- (superiority + eminence)
 */

