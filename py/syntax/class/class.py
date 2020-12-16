#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-07 12:52
# * Last modified : 2020-02-07 12:52
# * Filename      : class.py
# * Description   : 
# **********************************************************
class myclass:
    """myclass"""
    i = 1234

    def f(self):
        return 'hellow'

class complex:
    def __init__(self, realpart, imagpart):
        self.r = realpart
        self.i = imagpart

class test:
    def prt(self):
        print(self)
        print(self.__class__)

class people:
    name =''
    age = 0
    __weight = 0

    def __init__(self, n, a, w):
        self.name = n
        self.age = a
        self.__weight = w

    def speak(self):
        print("%s say:I %d years old." %(self.name, self.age))

class student(people):
    grade = ''

    def __init__(self, n, a, w, g):
        people.__init__(self, n, a, w)
        self.grade = g

    def speak(self):
        print("%s say:I %d years old.I am %d" %(self.name, self.age, self.grade))

class speaker():
    topic = ''
    name = ''

    def __init__(self, n, t):
        self.name = n
        self.topic = t

    def speak(self):
        print("我叫 %s，我是一个演说家，我演讲的主题是 %s"%(self.name,self.topic))

class sample(speaker, student):
    a = ''

    def __init__(self, n, a, w, g, t):
        student.__init__(self, n, a, w, g)
        speaker.__init__(self, n, t)

class Parent:
   def myMethod(self):
       print ('调用父类方法')

class Child(Parent):
   def myMethod(self):
       print ('调用子类方法')

class JustCounter:
    __secretCount = 0  # 私有变量
    publicCount = 0    # 公开变量

    def count(self):
        self.__secretCount += 1
        self.publicCount += 1
        print (self.__secretCount)
class Site:
    def __init__(self, name, url):
        self.name = name       # public
        self.__url = url   # private

    def who(self):
        print('name  : ', self.name)
        print('url : ', self.__url)

    def __foo(self):
        print('这是私有方法')

    def foo(self):
        print('这是公共方法')
        self.__foo()

#main function
if __name__ == '__main__':
    x = myclass()
    print(x.i)
    print(x.f())
    y = complex(3, 4)
    print(y.r)
    print(y.i)
    t = test()
    t.prt()
    p = people('cuiyunpeng', 10, 30)
    p.speak()
    s = student('ken', 10, 50, 3)
    s.speak()
    test = sample("tim", 25,  34, 5, "python")
    test.speak()

    c = Child()
    c.myMethod()
    super(Child, c)

    counter = JustCounter()
    counter.count()
    counter.count()
    print (counter.publicCount)
    # print (counter.__secretCount)

    x = Site('菜鸟教程', 'www.runoob.com')
    x.who()
    x.foo()
    # x.__foo()

