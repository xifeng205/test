/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-23 12:31
 * Last modified : 2020-03-23 12:31
 * Filename      : size_t.c
 * Description   : 
 *********************************************************************/
#include <stdio.h>

int main(int argc, char **argv)
{
    size_t i;
    int c;
    typedef union __headbits
    {
        unsigned int	uiWord;
        struct 
        {
            unsigned int uiFtype	:2;                             
            unsigned int uiSegNum 	:14;                            
            unsigned int uiSegPol   :2;
            unsigned int uiPortAddr :8;                                    
            unsigned int uiRF		:3;                
            unsigned int uiRsv		:3; 
        }Bits;
    }__HEADBITS;


    printf("%d\n", sizeof(__HEADBITS));
    printf("%d\n", sizeof(unsigned int));
    printf("%d\n", sizeof(int));
    /* printf("%d", sizeof(int)); */
}

