# KMapProgramming
This is a C/C++ program to read in a Boolean equation, making the corresponding Karnaugh Map and computing the minimum form of sum of product.

# Mask Operation
This program scans the Karnaugh Map to get all-ones matrix using different sizes of masks.

Mask scanning started from the max-sized mask **by descent order**.

That is to say, scanning from Mask16(4x4) -> Mask8(2x4, 4x2) -> Mask4(1x4, 2x2, 4x1) -> Mask2(1x2, 2x1) -> Mask1(1x1).

The program uses a boolean variable called **is_coverd** to indicate whether a mask covering an all-ones matrix.

If finding an all-ones matrix by the mask, storing the **checkcode** of the mask into a **linked list**.

Checkcode is a struct member to check whether the mask is included in bigger one, which is a 16-bit value of an integer to represent the ones indices of the mask by its bit value.

Once an all-ones matrix is coverd by a mask, the program will traverse the checkcode of all nodes in the linked list.

By **bitwise AND operaton** between two sets of checkcode, we can examine if the bigger mask is inclusive of the smaller one.

For example,

Bigger Mask: MaskA = [0, 4, 12, 8, 1, 5, 13, 9], with checkcode_A = 0b0011001100110011

Smaller Mask:  MaskB = [0, 4, 12, 8]with checkcode_B = 0b0001000100010001

checkcode_A AND checkcode_B = 0b0011001100110011 & 0b0001000100010001 = 0b0001000100010001 = checkcode_B(Smaller Mask)

If the result of the AND operaton is equal to the checkcode of the smaller mask, then we can find out that it is included in the bigger mask.

# Remark
**The program is taking the test and needs to optimizing. Hence, remark this is not the final version.
The updated version will be uploaded if I modify the content.**

Please put the source code file and test.txt in the same directory before compiling or executing.
