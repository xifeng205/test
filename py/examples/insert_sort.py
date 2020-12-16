
#!/usr/bin/env python
# _*_  coding: utf-8 _*_
# Author        : cuiyunpeng
# Email         : @163.com
# Create time   : 2020-07-24 21:31
# Last modified : 2020-07-24 21:31
# Filename      : insert_sort.py
# Description   :

def insert_sort(arry, low, high):
    """binary

    :param arry:
    :param low:
    :param high:
    """
    if low > high: high, low = low, high

    for i in range(low, high):
        for j in  range(i):
            if arry[i] < arry[j]:
                arry[i], arry[j] = arry[j], arry[i]
def main():
    list = [1, 2, 5, 6, 23, 0, 7, 4, 8, 3]
    insert_sort(list, 0, len(list))
    print(list)

if __name__ ==  "__main__":
    main()
