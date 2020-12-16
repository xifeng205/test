#!/usr/bin/python3
# _*_  coding: utf-8 _*_

# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-02-21 10:29
# * Last modified : 2020-02-21 10:29
# * Filename      : json.py
# * Description   : 
# *******************************************************************
import json

data = {
        'no' : 1,
        'name' : 'runoob',
        'url' : 'www.runoob.com'
        }

print("eg1")
json_data = json.dumps(data)
print("python origin data:", repr(data))
print("json tansmit data:", json_data)

print("eg2")
data1 = json.loads(json_data)
print("data1.name:", data1['name'])
print("data1.name:", data1['url'])

print("eg3")

with open("data.json", 'w') as f:
    json.dump(data, f)

with open('data.json', 'r') as f:
    data2 = json.load(f)

print("data2:", repr(data2))
