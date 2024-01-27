#include <stdio.h>
#include <stdlib.h>
#include <ieee754.h>

/*
 A= 7.5 and B = 2.5 for without an error case


 A= 3.25 and 24444444.5 with an error case.
 These A and B numbers are giving the wrong answers due to this floating point addition IEEE algorithm. 
 Because exp difference is 23 in decimal when A (mantissa = 500000) is shifted its mantissa rounds up to 0 due to 
 right shifting. In C = A + B => 0 is added as A.
 After D = C -B => D is founded as 0 but if we want to shift D to find A's orginal value, we cant find mantissa 50000 again.

 I can say that if two floating point numbers exp difference is high. When we right shift the smaller number with the 
 difference, it rounds up to 0. Because we have a restricted bit space so after some shifts some values will be gone 
 and cause a problem.

*/

int main(){
    
    float a;
    printf("\n\nENTER the value of A:\n");
    scanf("%f", &a);    
    union ieee754_float *p_a;
    unsigned int a_exp;
    unsigned int a_negative;
    unsigned int a_mantissa;
    p_a = (union ieee754_float*)&a;
    a_exp = p_a->ieee.exponent;
    a_negative = p_a->ieee.negative;
    a_mantissa = p_a->ieee.mantissa;
    printf("exponent of A: %x\n", a_exp);
    printf("negative of A: %x\n", a_negative);
    printf("mantissa of A: %x\n", a_mantissa);
    
    //creating b
    float b;
    printf("\n\nENTER the value of B:\n");
    scanf("%f", &b);    
    union ieee754_float *p_b;
    unsigned int b_exp;
    unsigned int b_negative;
    unsigned int b_mantissa;
    p_b = (union ieee754_float*)&b;
    b_exp = p_b->ieee.exponent;
    b_negative = p_b->ieee.negative;
    b_mantissa = p_b->ieee.mantissa;
    printf("exponent of B: %x\n", b_exp);
    printf("negative of B: %x\n", b_negative);
    printf("mantissa of B: %x\n", b_mantissa);
    
    //creating c and d
    unsigned int c_exp = 0;
    unsigned int c_negative = 0;
    unsigned int c_mantissa = 0;

    unsigned int d_exp = 0;
    unsigned int d_negative = 0;
    unsigned int d_mantissa = 0;
    

    //shifting mantissas by their exponent differences
    //giving c_exp's value according which one of the a_exp and b_exp 's value is bigger
    //if a_exp and b_exp is equal it just gives one of them.
    if (a_exp > b_exp) {
        b_mantissa = (b_mantissa >> (a_exp - b_exp));
        c_exp = a_exp;
        b_exp = a_exp;
        
    } 
    else {
        a_mantissa = (a_mantissa >> (b_exp - a_exp));
        c_exp = b_exp;
        a_exp = b_exp;
    }
    
    printf("\nA mantissa: %x \n", a_mantissa);


    // c = a + b
    c_negative = a_negative;
    c_mantissa = a_mantissa + b_mantissa;
    
    printf("\nValue C:\n");
    printf("exponent of c: %x\n", c_exp);
    printf("negative of c: %x\n", c_negative);
    printf("mantissa of c: %x\n", c_mantissa);
    
    // d = c - b
    //giving d_exp's value according which one of the c_exp and b_exp 's value is bigger
    //if a_exp and b_exp is equal it just gives one of them.
    d_negative = c_negative;
    
    if (c_exp > b_exp) {
        d_exp = c_exp;
        b_exp = c_exp;
    } 
    else {
        d_exp = b_exp;
        c_exp = b_exp;
    }
    
    d_mantissa = c_mantissa - b_mantissa;
    

    printf("\nValue D:\n");
    printf("exponent of d: %x\n", d_exp);
    printf("negative of d: %x\n", d_negative);
    printf("mantissa of d: %x\n", d_mantissa);
   

    return 0;
}
    
    
    
