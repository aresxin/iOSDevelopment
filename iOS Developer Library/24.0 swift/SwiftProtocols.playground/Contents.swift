//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"


extension BooleanType where Self: Bird {
    var boolValue: Bool {
        return self.canFly
    }
}


protocol Bird {
    var name: String { get }
    var canFly: Bool { get }
}

protocol Flyable {
    var airspeedVelocity: Double { get }
}



struct FlappyBird: Bird, Flyable {
    let name: String
    let flappyAmplitude: Double
    let flappyFrequency: Double
    //let canFly = true
    var airspeedVelocity: Double {
        return 3 * flappyFrequency * flappyAmplitude
    } 
}





extension Bird where Self: Flyable {
    // Flyable birds can fly!
    var canFly: Bool { return true }
}


struct Penguin: Bird {
    let name: String
    let canFly = false
}



struct SwiftBird: Bird, Flyable {
    var name: String { return "Swift \(version)" }
    let version: Double
    //let canFly = true
    
    // Swift 速度超群!
    var airspeedVelocity: Double { return 2000.0 }
}






enum UnladenSwallow: Bird, Flyable, BooleanType {
    case African
    case European
    case Unknown
    var name: String {
        switch self {
        case .African:
            return "African"
        case .European:
            return "European"
        case .Unknown:
            return "What do you mean? African or European?"
        }
    }
    
    var airspeedVelocity: Double {
        switch self {
        case .African:
            return 10.0
        case .European:
            return 9.9
        case .Unknown:
            fatalError("You are thrown from the bridge of death!")
        } 
    }
}




extension CollectionType {
    func skip(skip: Int) -> [Generator.Element] {
        guard skip != 0 else { return [] }
        
        var index = self.startIndex
        var result: [Generator.Element] = []
        var i = 0
        repeat {
            if i % skip == 0 {
                result.append(self[index])
            }
            index = index.successor()
            i++
        } while (index != self.endIndex)
        
        return result
    }
}



let bunchaBirds: [Bird] =
[UnladenSwallow.African,
    UnladenSwallow.European,
    UnladenSwallow.Unknown,
    Penguin(name: "King Penguin"),
    SwiftBird(version: 2.0),
    FlappyBird(name: "Felipe", flappyAmplitude: 3.0, flappyFrequency: 20.0)]

bunchaBirds.skip(3)

// 扩展类，结构体，枚举，协议。
// 实现协议可以的拿到协议的方法，属性。


if UnladenSwallow.African {
    print("I can fly!")
} else {
    print("Guess I’ll just sit here :[")
}
