/* 
 * CSCI3240: Project 2
 * 
 * Timothy Beckett tdb2q
 * 
 * Project2.c - Source file with your solutions to the Lab.
 *          This is the file you will submit in the D2L -> Project2 dropbox.
 *
 *   Make sure you have insightful comments in your code. 
 * 
 */

#include <stdio.h>

long MysteryFunction1(long a, int b);
unsigned int MysteryFunction2(unsigned int num);
long MysteryFunction3(long* a, int n);
int MysteryFunction4(unsigned long n);
unsigned int MysteryFunction5(unsigned int a, unsigned int b);

int main(int argc, char** argv)
{
    // test MysteryFunction1 a = 2, b = 0, result 1
    printf("MysteryFunction1 a = 2, b = 0, result %ld\n", MysteryFunction1(2,0));
    // test MysteryFunction1 a = 2, b = 1, result 2
    printf("MysteryFunction1 a = 2, b = 1, result %ld\n", MysteryFunction1(2,1));
    // test MysteryFunction1 a = 2, b = 2, result 4
    printf("MysteryFunction1 a = 2, b = 3, result %ld\n", MysteryFunction1(2,2));
    // test MysteryFunction1 a = 2, b = 3, result 8
    printf("MysteryFunction1 a = 2, b = 3, result %ld\n", MysteryFunction1(2,3));

    // test MysteryFunction2 n = 1
    printf("MysteryFunction2 n = 1 %u\n", MysteryFunction2(1));
    // test MysteryFunction2 n = 2
    printf("MysteryFunction2 n = 2 %u\n", MysteryFunction2(2));
    // test MysteryFunction2 n = 3
    printf("MysteryFunction2 n = 3 %u\n", MysteryFunction2(3));
    // test MysteryFunction2 n = 4
    printf("MysteryFunction2 n = 4 %u\n", MysteryFunction2(4));
    
    long array[] = {5, 8, 2, 10, 6};
    int size = sizeof(array) / sizeof(array[0]);
    long result = MysteryFunction3(array, size);
    printf("MysteryFunction3 Result: %ld\n", result);
    
    // test MysteryFunction4 n = 1
    printf("MysteryFunction4 n = 1 tally = %d\n", MysteryFunction4(1));
    // test MysteryFunction4 n = 2
    printf("MysteryFunction4 n = 2 tally = %d\n", MysteryFunction4(2));
    // test MysteryFunction4 n = 3
    printf("MysteryFunction4 n = 3 tally = %d\n", MysteryFunction4(3));
    // test MysteryFunction4 n = 4
    printf("MysteryFunction4 n = 4 tally = %d\n", MysteryFunction4(4));
    
    // test MysteryFunction5 A = 1010, B = 0101, tally = 4    
    printf("MysteryFunction5 A = 10, B = 5, tally = %u\n", MysteryFunction5(10,5));
    // test MysteryFunction5 A = 1, B = 1, tally = 0
    printf("MysteryFunction5 A = 1, B = 1, tally = %u\n", MysteryFunction5(1,1));
    // test MysteryFunction5 A = 15, B = 14, tally = 1
    printf("MysteryFunction5 A = 15, B = 14, tally = %u\n", MysteryFunction5(15,14));
        
    
    return 0;
}

// * calculates the value of “a” raised to the power of “b”
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
long MysteryFunction1(
    long a, // rdi
	int b)  // rsi
{   
	long r = 1;     // movl $1, eax	
	
                    // movl %edx, %esi
	int i = b-1;	// leal -1(%rsi), %edx	
	
	// The while loop encapsulates jmp statements.
	
	while(i >= 0)    // testl %esi, %esi
	{
		r *= a;     // imulq %rdi, %rax
		
				    // movl %edx, %esi
		i--;        // leal -1(%rsi), %edx
	}

	return r;       // ret  # the return value is in eax (ie r)
}

// * This function examines the 32 bits of the parameter “num” from the least significant bit to the
// * most significant bit.  For each bit that is set to 1, it sets the corresponding bit, from the 
// * value -2147483648, in the result r. A new number is created where only the most significant bit 
// * of each set position is set.  The zeros from num are ignored and the corresponding generated 
// * number will set the corresponding bit by significance i.e. when looking at the 2^1 if the bit 
// * is 1, then the result will get storea zero in the result because the first bit in the 2^1 was 0.
// * This will process will continue the process up to 32 times. 1 iteration for each bit in the 
// * resulting int. I think this might be a pseudo random number generator.
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
unsigned int MysteryFunction2(unsigned int num /* rdi */)
{
    int r = 0; // the result.         
    int i = 0; // counter.

    while (1) 
    {
        i++;                          // addl	$1, %ecx  
                                      // cmpl	$31, %ecx                           
        if (i > 31)                   // ja	.L8
        {
            break;   // get out of the loop now when i is 32.
        }

        
        int buf = 1;                  // movl $1, %eax
        
        // Shift 1 to the left by the counter value
        buf = buf << (char)i;         // sall	%cl, %eax  
        
        // skip the bit if it's not in num.
                                     // testl	%edi, %eax
        if ((num & buf) != 0)        // je	.L6
        {            
            buf = -2147483648;
            
            // Shift sign bit to the right by the counter value            
            buf = buf >> (char)i;     // shrl	%cl, %eax
            
            // Set the bit in the result
            r |= buf;                 // orl	%eax, %edx  
        }
    }
    
    return r; 
}

// * this function is looking for the max in the array.
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
long MysteryFunction3(long* a, int n) 
{
    long r = *a; // movq (%rdi), %rcx
    

    // start with the second element because the first is already in r.
    // the for loop combines several instructions:
    // movl $1, %eax
    // cmpl %esi, %eax
    // jge .L14
    // addl $1, %eax
    for (int i = 1; i < n + 1; i++)
    {
        // get the next number.
        long buf = a[i]; // movq (%rdi,%rdx,8), %rdx

        // replace max when new max is found.
        // cmpq %rcx, %rdx
        // jle .L11
        if (buf > r)
        {
            r = buf; // movq %rdx, %rcx
        }
    }

    return r; // movq %rcx, %rax
}

// * The function examines the bits in the binary value of the number provided in the 
// * parameter “n”.  It keeps a count of all of the bits that are set to 1 e.g. if n 
// * is 1010 base 2 (10 decimal) then the returned value will be 2 because there are 2 
// * bits set to 1 in the number.
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int MysteryFunction4(unsigned long n) // rdi
{
    int r = 0;           // movl	$0, %eax
    
    // The while loop encapsulates jmp statements.    
    while (n != 0)      // testq	%rdi, %rdi
    {
        // count the bit in the 1s positions
                            // movl %edi, %edx
                            // andl $1, %edx
        r += (n & 1);       // addl %edx, %eax
        
        // shift right.
        n /= 2;            //shrq	%rdi
    }
    
    return r;
}

// * finds differing bits between “A” and “B” and tallies number of bits.
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
unsigned int MysteryFunction5(
    unsigned int a, // rdi
    unsigned int b) // rsi
{
    unsigned int c = 0;     // movl $0, %eax
    
    // find the differing bits in a and b
    a ^= b;                // xorl %esi, %edi
    
    // The while loop encapsulates jmp statements.
    while (a != 0)        // testq %rdi, %rdi
    {
        // count the bit in the 1s position
                         // movl %edi, %edx
        c += (a & 1);    // andl $1, %edi
        
        // shift right.
        a /= 2;          // sarl %edi
    }
    
    return c;
}