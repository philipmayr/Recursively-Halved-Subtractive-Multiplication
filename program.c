// Karatsuba Multiplication Algorithm

#include <stdio.h>

int find_greater_of_twain(int a, int b)
{
    return a > b ? a : b;
}

int count_bits(int bit_string)
{
    int bit_length = 1;
    
    while (bit_string >>= 1) bit_length++;
    
    return bit_length;
}

int exponentiate(int base, int index)
{
    if (base == 0) return 0;
    if (index == 0) return 1;
    if (index == 1) return base;

    int power = 1;
    
    while (index)
    {
        if (index & 1) power *= base;
        
        base *= base;
        index >>= 1;
    }
    
    return power;
}

int multiply(int multiplicand, int multiplier)
{
    int threshold = 32;
    
    if (multiplicand < threshold && multiplier < threshold)
        return multiplicand * multiplier;

    int multiplicand_bit_length = count_bits(multiplicand);
    int multiplier_bit_length = count_bits(multiplier);
    
    int halved_bit_length = find_greater_of_twain(multiplicand_bit_length, multiplier_bit_length) >> 1;
    int two_exponentiated_by_halved_bit_length = exponentiate(2, halved_bit_length);

    int multiplicand_low_order_bits = multiplicand % two_exponentiated_by_halved_bit_length;
    int multiplier_low_order_bits = multiplier % two_exponentiated_by_halved_bit_length;

    int multiplicand_high_order_bits = multiplicand >> halved_bit_length;
    int multiplier_high_order_bits = multiplier >> halved_bit_length;
    
    int first_product = multiply(multiplicand_low_order_bits, multiplier_low_order_bits);
    int second_product = multiply(multiplicand_high_order_bits, multiplier_high_order_bits);
    int third_product = multiply(multiplicand_low_order_bits + multiplicand_high_order_bits, multiplier_low_order_bits + multiplier_high_order_bits);

    int first_summand = second_product * exponentiate(2, halved_bit_length << 1);
    int second_summand = (third_product - second_product - first_product) * two_exponentiated_by_halved_bit_length;
    int third_summand = first_product;

    int sum = first_summand + second_summand + third_summand;
    
    return sum;
}

int main()
{
    int multiplicand = 0;
    int multiplier = 0;
    int product = 0;
    
    for (;;)
    {
        printf("Enter integer multiplicand: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, buffer;
        
        status = scanf("%d", & input);
        
        while (status != 1)
        {
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter integer multiplicand: ");
              
              status = scanf("%d", & input);
        }
        
        multiplicand = input;
        
        printf("Enter integer multiplier: ");
        
        status = scanf("%d", & input);
        
        while (status != 1)
        {
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter integer multiplier: ");
              
              status = scanf("%d", & input);
        }
        
        multiplier = input;
        
        product = multiply(multiplicand, multiplier);
        
        printf("\n");
        
        printf("%d ⋅ %d æ %d", multiplier, multiplicand, product);
        
        printf("\n\n");
    }

    return 0;
}
