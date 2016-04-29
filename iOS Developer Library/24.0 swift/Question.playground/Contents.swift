/*:
# Playground for iOS Developer

姓名: 请填入你的名字

小提示:
 * 保持代码简洁易于维护.
 * 充分考虑各种异常处理.
 * 使用Swift的最新版本.
 */

import UIKit


//Question 1. Implement Singleton Pattern.
//https://github.com/hpique/SwiftSingleton
class SingletonA {
    
    static let sharedInstance = SingletonA()
    
    init() {
    
    }
    
}

class SingletonB {
    
    class var sharedInstance: SingletonB {
        struct Static {
            static let instance: SingletonB = SingletonB()
        }
        return Static.instance
    }
    
}

class SingletonC {
    
    class var sharedInstance: SingletonC {
        struct Static {
            static var onceToken: dispatch_once_t = 0
            static var instance: SingletonC? = nil
        }
        dispatch_once(&Static.onceToken) {
            Static.instance = SingletonC()
        }
        return Static.instance!
    }
}
/*: 
## 问题一: 实现斐波那契数列
斐波那契数列的排列是:0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144...

在数学上, 斐波纳契数列以如下被以递归的方法定义:F0=0, F1=1, Fn=Fn-1 + Fn-2(n>=2,n∈N*).

简单来说, 就是斐波那契数列列由 0 和 1 开始，之后的斐波那契数列系数就由之前的两数相加。*/

struct Fibonacci {
    var fromIndex: Int
    var toIndex: Int
    
    init(toIndex: Int, fromIndex: Int = 0) {
        self.fromIndex = fromIndex
        self.toIndex = toIndex
    }
    
    
    //http://swift.gg/2015/12/04/the-fibonacci-sequencetype/
    
    
    let fibonacciNumbers = AnySequence { () -> AnyGenerator<Int> in
        // 为了创建一个生成器，我们首先需要建立一些状态...
        var i = 0
        var j = 1
        return AnyGenerator {
            // ... 然后生成器进行改变
            // 调用 next() 一次获取每一项
            // (代码看起来是不是很熟悉？)
            (i, j) = (j, i + j)
            return i
        }
    }
    
    func printFibonacciNumbers(toIndex: Int, fromIndex: Int = 0) {
        for f in fibonacciNumbers {
            print(f) // 打印 1, 然后打印 1, 继续打印 2, 3, 5, 8, 13, 21, 34, 55...
        }
    }
    
    
    func printFib(toIndex: Int, fromIndex: Int = 0) {
        for index in fromIndex...toIndex {
            nthFibonacci(index)
            print(nthFibonacci(index))
        }
    }
    
    
    func nthFibonacci(n: Int) -> Int
    {
        var i = 0
        var j = 1
        for _ in 0..<n {
            (i, j) = (j, i + j)
        }
        return i
    }
    
}






/*:
**测试1. 打印从F0 到 F10的斐波那契数列**

预期结果为:0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
 */
let fib = Fibonacci(toIndex: 10)
fib.nthFibonacci(10)
fib.printFib(10)
print(Fibonacci(toIndex: 10))




/*:
**测试2. 打印从F5 到 F10的斐波那契数列**

预期结果为:5, 8, 13, 21, 34, 55
*/
print(Fibonacci(toIndex: 10, fromIndex: 5))
fib.printFib(10, fromIndex:5)
/*:
## 问题二: 排序

 * 对所有 **Developer** 按年龄大小进行降序排序.
 * Print时, 只打印姓名.
 */

enum StaffRole {
    case Boss
    case Developer
    case QA
}

struct Staff {
    var name: String
    var age: Int
    var role: StaffRole
    
    init(name: String, age: Int, role: StaffRole) {
        self.name = name
        self.age = age
        self.role = role
    }
}

let jeon = Staff(name: "Jeon", age: 1, role: .Boss)
let squid = Staff(name: "Squid", age: 2, role: .Developer)
let young = Staff(name: "Young", age: 3, role: .Developer)
let owen = Staff(name: "Owen", age: 4, role: .Developer)
let richard = Staff(name: "Richard", age: 5, role: .Developer)
let jessica = Staff(name: "Jessica", age: 6, role: .QA)

var members: [Staff] = [
    jeon,
    squid,
    young,
    owen,
    richard,
    jessica
]

members.sortInPlace { (s1:Staff, s2:Staff) -> Bool in
    return s1.age > s2.age
}

members.sortInPlace({$0.age > $1.age})

members.sortInPlace{$0.age > $1.age}
print(members)
// print(sortedDevelopers)

/*:
## 问题三: 在Playground中实现带有圆角的照片效果.

*/
extension UIImage {
    func drawRectWithRoundedCorner(radius radius: CGFloat, _ sizetoFit: CGSize) -> UIImage {
        let rect = CGRect(origin: CGPoint(x: 0, y: 0), size: sizetoFit)
        
        UIGraphicsBeginImageContextWithOptions(rect.size, false, UIScreen.mainScreen().scale)
        CGContextAddPath(UIGraphicsGetCurrentContext(),
            UIBezierPath(roundedRect: rect, byRoundingCorners: UIRectCorner.AllCorners,
                cornerRadii: CGSize(width: radius, height: radius)).CGPath)
        CGContextClip(UIGraphicsGetCurrentContext())
        
        self.drawInRect(rect)
        CGContextDrawPath(UIGraphicsGetCurrentContext(), .FillStroke)
        let output = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        
        return output
    }
}


//Question 4. Implement a Sortable Stack
//Hashable
struct Stack<T:Comparable> {
    var items = [T]()
    mutating func push(item: T) {
        items.append(item)
    }
    
    // mutating关键字
    
//    mutating func pop() -> T?{
//        //        items.removeLast()
//        
//        guard items.count > 0 else {
//            return nil
//        }
//        
//        let max = self.max()
//        let index = items.indexOf(max)
//        return items.removeAtIndex(index!)
//    }
    
    
    mutating func pop() {
//        items.removeLast()
        
        guard items.count > 0 else {
            return
        }
        
        let max = self.max()
        let index = items.indexOf(max)
        items.removeAtIndex(index!)
    }
    
    func max() -> T {
        let numMax = items.maxElement()
        return numMax!
    }
    
    func maxIndex() -> Int {
        let max = self.max()
        let index = items.indexOf(max)
        return index!
    }
}


var stackOfStrings = Stack<String>()
stackOfStrings.push("Xuno")
stackOfStrings.push("Zdos")
stackOfStrings.push("Zzres")
stackOfStrings.push("Acuatro")
print(stackOfStrings)

let max = stackOfStrings.max()
print(max)
let maxIndex = stackOfStrings.maxIndex()
print(maxIndex)


stackOfStrings.pop()
print(stackOfStrings)
//
//func fib(n: Int) -> Int {
//    if n <= 1 {
//        return 1
//    }
//    else {
//        return fib(n-1) + fib(n-2)
//    }
//}
//
//fib(3)
