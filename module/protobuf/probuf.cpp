/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-09 20:36
 * Last modified : 2020-05-09 20:36
 * Filename      : probuf.cpp
 * Description   : 
*********************************************************************/
#include "lpk.helloworld.pb.hpp"
…
 
 int main(void) 
 { 
   
  lpk::helloworld msg1; 
  msg1.set_id(101); 
  msg1.set_name(“李平宽”); 
  msg1.set_age(18); 
     
  // Write the new address book back to disk. 
  fstream output("./log", ios::out | ios::trunc | ios::binary); 
         
  if (!msg1.SerializeToOstream(&output)) { 
      count << "失败" << endl; 
      return -1; 
  }         
  return 0; 
 }

