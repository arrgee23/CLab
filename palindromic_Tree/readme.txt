This is an implementation and few examples of use of palindromic trees.


the implementation and header files are eertree.c and eertree.h respectively.


cs1835-project1-prog1.c, cs1835-project1-prog2.c, cs1835-project1-prog3.c, cs1835-project1-prog4.c 
are the files that soves the following problems Respectively
a) Finding the number of subpalindromes, common to all k given strings.
(b) Finding the longest subpalindrome contained in all k given strings.
(c) For the strings S and T, finding the number of palindromes P having more occurrences
in S than in T.
(d) For the strings S and T, finding the number of equal palindromes, i.e., of triples (i, j, k)
such that S[i..i + k] = T[j..j + k] is a palindrome.


build instruction:
gcc eertree.c cs1835-project1-progX.c -o progX
here X stands for program number by filename


input convention:
the strings are given in files.  filename is supplied via command line.
the input files expects entries in FASTA format. First line and newlines are ignored.
All other characters are converted to upper case.


Some more instructions for extra outputs:

1. If you want to read further debug outputs please change the line in eertree.having
from
#undef DEBUG
to 
#define DEBUG

2. Use the printstrings function to print the palindromic substrings contained in the tree and their 
no of occuerences in each of the strings.