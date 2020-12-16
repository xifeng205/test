#!/usr/bin/env python
# _*_  coding: utf-8 _*_
''''
 ********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-18 20:52
 * Last modified : 2020-04-18 20:52
 * Filename      : sklearn.py
 * Description   : 
*********************************************************************
'''
import numpy as np
from sklearn import metrics

y = np.array([1,1,2,2])
scores = np.array([0.1, 0.4, 0.35, 0.8])
fpr, tpr, thresholds = metrics.roc_curve(y, scores, pos_label=2)

