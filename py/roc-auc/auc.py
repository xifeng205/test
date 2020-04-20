#!/usr/bin/env python
# _*_  coding: utf-8 _*_
''''
 ********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-18 21:16
 * Last modified : 2020-04-18 21:16
 * Filename      : auc.py
 * Description   : 
*********************************************************************
'''
import numpy as np
from sklearn.metrics import roc_auc_score
y_true = np.array([0, 0, 1, 1])
y_scores = np.array([0.1, 0.4, 0.35, 0.8])
roc_auc_score(y_true, y_scores)
