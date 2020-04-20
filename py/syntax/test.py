#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# **********************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-01-30 17:02
# * Last modified : 2020-01-30 17:02
# * Filename      : conding.py
# * Description   :
# **********************************************************

print("hellow word")

#first comment

'''
second comment
tcvoird commmet
'''

if True:
    print("True")
else:
    print("false")

item_one = 1
item_two = 2
item_three = 3

total = item_one + \
        item_two + \
        item_three

print(total)


'''
Mumber
Python 中数字四中有四种类型：整数  布尔型  浮点型和复数
* int , 只有一种int 型
* bool
* float
* complex
'''

total = [item_one,
        item_two,
        item_three]

print(total)


'''
string

'''

string = 'this is a string'

print(string)

string =string + '\n'

print(string)

string = r"this is a string \n"
print(string + "\n")

string = "this is a string"

print(string[0:-1])
print(string[0])
print(string[-1])
print(string[0:2])
print(string[0:4:2])
print(string * 2)

# input("please input word\n\r")

'''
ython可以在同一行中使用多条语句，语句之间使用分号(;)分割
'''

import sys; x = "hellow word!"; sys.stdout.write(x + '\n')

print(string,  end = "")
print(string,  end = "")
print("\n------------------------------------")

import sys

for i in  sys.argv:
    print(i)

print(sys.path)

print("\n------------------------------------")

a, b, c = 1, 2 ,"hellow word"

print(a,b,c)

'''
不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）
可变数据（3 个）：List（列表）、Dictionary（字典）、Set（集合）
'''

a, b, c, d = 20, 5, True, 4+3j

print(type(a), type(b), type(c), type(d))


print("\n------------------------------------")

'''
 type()不会认为子类是一种父类类型。
isinstance()会认为子类是一种父类类型
'''
a = 111

isinstance(a, int)

print("\n------------------------------------")

'''
注意：在 Python2 中是没有布尔型的，它用数字 0 表示 False，用 1 表示 True。到 Python3 中，把 True 和 False 定义成关键字了，但它们的值还是 1 和 0，它们可以和数字相加。
'''
var1 = 1
var2 = 2

print(var1)
print(var2)

del  var1, var2

print("\n------------------------------------")

'''
    1、Python可以同时为多个变量赋值，如a, b = 1, 2。
    2、一个变量可以通过赋值指向不同类型的对象。
    3、数值的除法包含两个运算符：/ 返回一个浮点数，// 返回一个整数。
    4、在混合计算时，Python会把整型转换成为浮点数。

'''
c, a = 0, 5
c = a / 2
print(c)
c = a // 2
print(c)

a = 10
b = -768
c = 80
d = 490
e = 0x260
f = -0x69
print(a, b, c, d, e, f)

a = 0.0
b = -.8
c = 80.
d = 4.90
e = 23.3e+18
f = 9e-12
print(a, b, c, d, e, f)

a = 0.1
b = -.8j
c = 80.j
d = 4.90j
e = 23.3e+18j
f = 9e-12j
print(a, b, c, d, e, f)

print("\n------------------------------------")
c = complex(a, b)
print(c)
print("\n------------------------------------")

'''
Python中的字符串用单引号 ' 或双引号 " 括起来，同时使用反斜杠 \ 转义特殊字符。
'''
'''
ist（列表） 是 Python 中使用最频繁的数据类型。

列表可以完成大多数集合类的数据结构实现。列表中元素的类型可以不相同，它支持数字，字符串甚至可以包含列表（所谓嵌套）。

列表是写在方括号 [] 之间、用逗号分隔开的元素列表。

和字符串一样，列表同样可以被索引和截取，列表被截取后返回一个包含所需元素的新列表。

列表截取的语法格式如下：

变量[头下标:尾下标]
'''
list = ['abcd', 768, 2.23, 'runoob', 70.2]
tinylist = [123, 'runoob']

print("\n------------------------------------")
print(list)
print(tinylist)
print(list[0])
print(list[1:3])
print("\n------------------------------------")
'''
与Python字符串不一样的是，列表中的元素是可以改变的
'''
'''
uple（元组）

元组（tuple）与列表类似，不同之处在于元组的元素不能修改。元组写在小括号 () 里，元素之间用逗号隔开。

'''
tuple = ('adcd', 768, 2.23, 70.2)

print(tuple)
print(tuple[1])
print(tuple[-1])
print(tuple[0:4:2])

'''
虽然tuple的元素不可改变，但它可以包含可变的对象，比如list列表。
'''
list1 = [1.1, 3, "233"]
tup1 = (2, list1)
print(tup1)

list1[2] = "222"
print(tup1)

'''
构造包含 0 个或 1 个元素的元组比较特殊，所以有一些额外的语法规则
'''

tup2 = ()
tup3 = (20,)
print(tup2)
print(tup3)
print(tup1 + tup2 + tup3)

'''
 集合（set）是由一个或数个形态各异的大小整体组成的，构成集合的事物或对象称作元素或是成员。

基本功能是进行成员关系测试和删除重复元素。

可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
'''

student = {'Tom', 'Jim', 'jack', 'Rose'}
print(student)

if 'Rose' in student:
    print('Rose is in student')
else:
    print('Rose is not in student')


#set 可以进行集合运算
print("\n------------------------------------")
a = set()

print(a)

b = set('abcdefhijk')
c = set('abcdefml')

print(b)
print(c)
print(b - c)
print(b | c)
print(b & c)
print(b ^ c)
print("\n------------------------------------")

'''
 字典（dictionary）是Python中另一个非常有用的内置数据类型。

列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。

字典是一种映射类型，字典用 { } 标识，它是一个无序的 键(key) : 值(value) 的集合。

键(key)必须使用不可变类型。

在同一个字典中，键(key)必须是唯一的。
'''
dict = {}
print(dict)

dict1 = {}
dict1[1] = "one"
dict1['key'] = "two"
print(dict1)
print(dict1[1])

print('-----------------------------\n')

tinydict = {'naem':'runoob', 'code':1, 'side':'www.runoob.com'}
print(tinydict)
print(tinydict.keys())
print(tinydict.values())

print('-----------------------------\n')
# dict8 = dict(Runoob=1, Google=2, Taobao=3)
# dict9 = dict([('runoob', 1), ('google', 2)])
# print(dict4)
print('-----------------------------\n')

i = "2"

print(i)
i = int(i, 16)
print(i)

print('-----------------------------\n')
a = 60
b = 13
c = 0
c = a & b
print(c)
c = a >> 2
print(c)
print('-----------------------------\n')

a = 10
b = 20

print(a and b)

a = 10
b = 20

print(a or b)

c = 10

print(not c)

c = 0

print(not c)

list = [ 'adc', 1, 3, 'dkfdj']
a = 1

if (a in list):
    print('a in list')
else:
    print('a not in list')

b = 3

if (b not in list):
    print('b not in list')
else:
    print('b in list')


'''
身份运算用于比较两个对象的存储单元
id()函数用于获取对象的内存地址
'''
a =20
b =20

print(id(a))
print(id(b))

print(a is b)

if (a is b):
    print('a is b')
else:
    print('a is not b')

# print(random())
print('-----------------------------------------\n')

'''
ython2.6 开始，新增了一种格式化字符串的函数 str.format()，它增强了字符串格式化的功能。

基本语法是通过 {} 和 : 来代替以前的 % 。

format 函数可以接受不限个参数，位置可以不按顺序。
'''
string = "abcdef"
print("{} {}".format("ss", 'adf'))
print("{1} {0}".format('aad',"dfdsf"))
print("webname:{name}, add：{url}".format(name = "cyp", url= "www.runoob.com"))

# 通过字典设置参数
site = {"name": "菜鸟教程", "url": "www.runoob.com"}
print("网站名：{name}, 地址 {url}".format(**site))
# 通过列表索引设置参数
my_list = ['菜鸟教程', 'www.runoob.com']
print("网站名：{0[0]}, 地址 {0[1]}".format(my_list))  # "0" 是必须的
print("{:.2f}".format(3.141455))
print("{:+.2f}".format(3.141455))
print("{:-.2f}".format(3.141455))
print("{:-.0f}".format(3.141455))
print("{:x<4d}".format(3))
print("{:+>4d}".format(3))
print("{:,}".format(1000000000))
print("{:.2%}".format(0.34))
print("{:.2e}".format(1122))
print("{:>10d}".format(222))
print("{:<10d}".format(2222))
print("{:^10d}".format(20347))

'''
^, <, > 分别是居中、左对齐、右对齐，后面带宽度， : 号后面带填充的字符，只能是一个字符，不指定则默认是用空格填充。

+ 表示在正数前显示 +，负数前显示 -；  （空格）表示在正数前加空格

b、d、o、x 分别是二进制、十进制、八进制、十六进制。

此外我们可以使用大括号 {} 来转义大括号，如下实例：
'''
print("({} response {{00}}".format("runoob"))
print("%d%s"% (22, 'fkdigji'))
# print("%*d%s"% (22.333, 'fkdigji'))

name = 'runoob'
a = f'hellow {name}'
print(a)

x = 1
print(f'{1+2}')
print(f'{x+1}')

'''
Python2 的字符串常用内建函数如下：
'''
src = 'this is s \t Test!!'

print(src)
print(src.capitalize())
print(src.center(50, "*"))
print(src.count('s', 0, len(src)))
print(src.encode("UTF-8"))
print(src.endswith('!!'))
print(src.endswith('w'))
print(src.expandtabs(16))
print(src.find('is'))
print(src.isdigit())
print(src.isnumeric())
print(src.isspace())
print(src.istitle())

list1 = ['Google', 'Runoob', 'Taobao']
list1.insert(1, 'Baidu')
print ('列表插入元素后为 : ', list1)

list1 = ['Google', 'Runoob', 'Taobao']
list1.pop()

print ("列表现在为 : ", list1)
list1.pop(1)
print ("列表现在为 : ", list1)
list1 = ['Google', 'Runoob', 'Taobao', 'Baidu']
list1.remove('Taobao')
print ("列表现在为 : ", list1)
list1.remove('Baidu')
print(list1)
list1.reverse()
print ("列表反转后: ", list1)

aList = ['Google', 'Runoob', 'Taobao', 'Facebook']
print(aList)
aList.sort()
print ( "List : ", aList)

#  获取列表的第二个元素
def takeSecond(elem):
    return elem[1]
# 列表
random = [(2, 2), (3, 4), (4, 1), (1, 3)]
# 指定第二个元素排序
random.sort(key=takeSecond)
# 输出类别
print ('排序列表：', random)

list1 = ['Google', 'Runoob', 'Taobao', 'Baidu']
list1.clear()
print ("列表清空后 : ", list1)

list1 = ['Google', 'Runoob', 'Taobao', 'Baidu']
list2 = list1.copy()
print ("list2 列表: ", list2)

tup4 = "a", "b", "c"
print(tup4)
tup5 = ()
print(tup5)
list = [1, 2, 2, 3]
print(list)
# list = tuple(list)
# print(list)

seq = ('name', 'age', 'sex')
dict = dict.fromkeys(seq)
print ("新的字典为 : %s" %  str(dict))
val = [10, 39., 90]
dict = dict.fromkeys(seq, val)
print ("新的字典为 : %s" %  str(dict))

# age = input("input age;")
# print(age)
# age = int(age)
# print(age)
print(range(5))
a = range(5)
print(a)
for i in range(5):print(i)
for i in range(0, 10, 3):print(i)

a = ['Google', 'Baidu', 'runoob', 'QQ']

for i in range(len(a)):print(i, a[i])

# print(list(range(5)))

'''
循环语句可以有 else 子句，它在穷尽列表(以for循环)或条件变为 false (以while循环)导致循环终止时被执行，但循环被 break 终止时不执行。
'''

for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, '等于', x, '*', n / x);break;
    else:print(n, 'is zhishu ')


class MyNumbers:
    def __iter__(self):
        self.a = 1
    return self
def __next__(self):
    x = self.a
    self.a += 1
    return x

myclass = MyNumbers()
myiter = iter(myclass)
print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))



