struct Matrix {
    let rows: Int, cols: Int
    var grid: [Double]
    init (rows: Int, _ cols:Int) {
        self.rows = rows
        self.cols = cols
        grid = Array(count: rows * cols, repeatedValue: 0.0)
    }
    subscript(row: Int, col: Int) -> Double {
        get {
            return grid[(row * cols) + col]
        }
        set {
            grid[(row * cols) + col] = newValue
        }
    }
}

/**
* Call init()
*  grid = [ 0.0, 0.0,
*           0.0, 0.0 ]
*/
var vertebrates = Matrix(2,2)
vertebrates[0,1] = 1.5
vertebrates[1,0] = 5.0
/**
* grid = [ 0.0, 1.5
*          5.0, 0.0 ]
*/
