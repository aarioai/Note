//
//  _0_0_2_UITableViewTests.swift
//  10.0.2 UITableViewTests
//
//  Created by Aario on 3/25/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
import XCTest
@testable import _0_0_2_UITableView

class _0_0_2_UITableViewTests: XCTestCase {
    func testMealInitialization() {// Success case.
        // Success case.
        let potentialItem = Meal(name: "Newest meal", photo: nil, rating: 5)
        XCTAssertNotNil(potentialItem)
        
        // Failure cases.
        let noName = Meal(name: "", photo: nil, rating: 0)
        XCTAssertNil(noName, "Empty name is invalid")
        
        let badRating = Meal(name: "Really bad rating", photo: nil, rating: -1)
        XCTAssertNotNil(badRating)
    }
}
