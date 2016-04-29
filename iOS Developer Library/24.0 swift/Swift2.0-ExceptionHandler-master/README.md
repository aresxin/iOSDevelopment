#Swift2.0－异常处理（Exception handler）

<br>

##前言

关于我们为什么要使用异常处理，请看百度百科为我们作出的描述，想要更详细的资料请点[这里](http://baike.baidu.com/link?url=pgGvxSsSqeuz3OnQ7NrWkqYwZXtY9MVTeuhOZolRvcr2UQtCLzZHQ3Y-2lFpAxeCQURXjCLqqY84XX0VLs4zaa)

```
异常处理，英文名为exceptional handling, 是代替日渐衰落的error code方法的新法，提供error code 所未能具体的优势。异常处理分离了接收和处理错误代码。这个功能理清了编程者的思绪，也帮助代码增强了可读性，方便了维护者的阅读和理解。 异常处理（又称为错误处理）功能提供了处理程序运行时出现的任何意外或异常情况的方法。异常处理使用 try、catch 和 finally 关键字来尝试可能未成功的操作，处理失败，以及在事后清理资源。
异常处理，是编程语言或计算机硬件里的一种机制，用于处理软件或信息系统中出现的异常状况（即超出程序正常执行流程的某些特殊条件）。

它有功能强大的控制流语句，像`do`、`try`、`catch`、`guard`和`defer`。我们能够使用这些关键字去操控我们的代码，更精确地执行我们的代码。
```

以上摘自百度百科：


关联，在`Objective-C`中，异常处理一般都是使用`NSError`类接收异常和抛出异常，使用方法像这样

```objc
NSError *error = nil;
NSString *string = [[NSString alloc] initWithContentsOfFile:@"filePath" encoding:NSUTF8StringEncoding error:&error];
if (error != nil) {
    // Exception handle
    NSLog(@"Erorr is %@", error);
}
// Code...
```

不得不说，`Swift`的异常处理更为优雅，下面会重点介绍。

##Demo

你可以在`github`上下载这个[示例Demo](https://github.com/GarveyCalvin/Swift2.0-ExceptionHandler)

##构建异常类型

我们可以构建自己的异常类型，它只是一个枚举，遵循`ErrorType`，像是这样

```swift
enum MyErrorHandling: ErrorType {
    
    case error1
    case error2
    
}
```

##定义函数可抛出异常

这里值得一提的是，只有函数才能够抛出异常。我们需要在参数后和返回值前加上`throws`关键字，并用`guard`捕捉异常，用`throw`抛出异常。

```swift
func myLoad(item: String?) throws -> String {
    guard let newItem = item else {
        throw MyErrorHandling.error1
    }
    return newItem
}
```

> **guard**: `guard`必须与`else`配合使用，只有当`guard`审查的条件成立，`guard`之后的代码才会执行，否则抛出异常。


##捕获/处理异常

我们使用`do-try-catch`去获取并处理异常

```swift
do {
    try myLoad(nil)
} catch {
    print("error")
}
```

如果只包含一个`catch`语句，那么所有的错误都会在这个`catch`中执行，我们能够捕抓其错误信息

```swift
do {
    try myLoad(nil)
} catch let error as NSError {
    print(error)
}
```

我们在使用`catch`时，它是能够进行模式匹配的，我们能够进行更精准的错误匹配处理

```swift
do {
    try myLoad("test")
} catch MyErrorHandling.error1 {
    print("error1")
} catch MyErrorHandling.error2 {
    print("error2")
}
```

如果我们不需要捕抓错误，那么我们可以使用`try!`或`try?`去执行该函数

```swift
try? myLoad(nil)
```

> 不建议使用`try!`，使用`try?`会更加安全。因为如果当有错误捕抓到时，程序会直接崩溃

##Defer（延迟执行）

那么我们何时需要使用到`defer`？这里使用官方的例子，比如我们需要读取某文件内容并处理，你需要打开这个文件，最后你需要关闭这个文件。当一切顺利的时候，程序一直往下运行，文件也将会被关闭。那么当中间出现一些错误呢？例如在某个环节执行失败了，但是你依然是需要去关闭该文件，在此`defer`就表现得很强大了。在这个例子中，我们可以把关闭文件的代码放到`defer`里面，在`defer`里的代码无论是函数执行成功或失败都会被执行。

```swift
func myLoad(item: String?) throws -> String {
    defer {
        print("Handle 1")
    }
    
    defer {
        print("Handle 2")
    }
    
    guard let newItem = item else {
        throw MyErrorHandling.error1
    }
    
    return newItem
}
```

> 需要注意的是，`defer`语句可以有多个，它们的执行顺序是`Handle 1` -> `Handle 2`。不难理解，它们的执行顺序是先进后出的。


这里再说一下，你可以在`github`上下载这个[示例Demo](https://github.com/GarveyCalvin/Swift2.0-ExceptionHandler)

<br>

##声明

博文作者：GarveyCalvin<br>
博文出处：[http://www.cnblogs.com/GarveyCalvin/](http://www.cnblogs.com/GarveyCalvin)<br>
本文版权归作者和博客园共有，欢迎转载，但须保留此段声明，并给出原文链接，谢谢合作！<br>