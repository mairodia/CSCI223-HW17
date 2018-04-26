// ============================================================================
// File: qsortints.c (Spring 2018)
// ============================================================================
// Programmer: Jennifer King
// Date: 4/25/2018
// Project: qsort
// Professor: Scott Edwards
// Class: CSCI 223F | TR 4:30PM
//
// Write a program that lets the user allocate a dynamic array of ints and
// populate it with unsorted values. Then use the qsort function to sort the
// array in ascending, then descending order.
// ============================================================================

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <time.h>

// defined constants
#define TRUE                    1
#define FALSE                   0
#define SORTED_ASC_FNAME        "ascending.txt"
#define SORTED_DESC_FNAME       "descending.txt"
#define UNSORTED_FNAME          "unsorted.txt"

// function prototypes
int*    AllocInts(int  numInts);
int     SortDown(const void* vptr1, const void* vptr2);
int     SortUp(const void* vptr1, const void* vptr2);
int     WriteInts(const char  *fname, const int  array[], int  numElems);


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    int         *arrayPtr;
    auto    int         numElems;

    // ask the user how many ints they want
    printf("How many ints do you want? ");
    if(0 == scanf("%d", &numElems))
    {
        puts("Error reading number of ints...");
        exit(EXIT_FAILURE);
    }
    // allocate an array of ints and fill it with random values
    arrayPtr = AllocInts(numElems);

    // write the unsorted array to an output file
    if(WriteInts(UNSORTED_FNAME, arrayPtr, numElems) == TRUE)
    {
        puts("Random ints saved to unsorted.txt...");
    }
    else
    {
        puts("Error occured while saving ints to unsorted.txt...");
    }

    // sort the array in ascending order and write it to a file
    qsort(arrayPtr, numElems, sizeof(int), SortUp);

    if(WriteInts(SORTED_ASC_FNAME, arrayPtr, numElems) == TRUE)
    {
        puts("Random ints saved to ascending.txt...");
    }
    else
    {
        puts("Error occured while saving ints to ascending.txt...");
    }

    // sort the array in descending order and write it to a file
    qsort(arrayPtr, numElems, sizeof(int), SortDown);

    if(WriteInts(SORTED_DESC_FNAME, arrayPtr, numElems) == TRUE)
    {
        puts("Random ints saved to descending.txt...");
    }
    else
    {
        puts("Error occured while saving ints to descending.txt...");
    }
    // release the array
    free(arrayPtr);

    return 0;

}  // end of "main"



// ==== AllocInts =============================================================
//
// This function uses the formal parameter to allocate an array of ints from the
// heap and fill it up with random integer values.
//
// Input:
//      numInts [IN]        -- the number of elements to allocate for the array
//
// Output:
//      The base address of the populated array, or NULL if an error occurs.
//
// ============================================================================

int*    AllocInts(int  numInts)
{
    int* array;
    array = malloc(numInts * sizeof(int));
    int *ptr;
    ptr = array;

    if(NULL == array)
    {
        puts("Wasn't able to allocate data.");
        ptr = NULL;
        return ptr;
    }

    srand(time(NULL));

    for(int index = 0; index < numInts; index++)
    {
        array[index] = rand();
    }

    return ptr;
}  // end of "AllocInts"



// ==== SortDown ==============================================================
//
// This is the comparison function for qsort so that the array can be sorted
// in descending order.
//
// Input:
//      vptr1 [IN]          -- a void pointer containing the address of a single
//                             array element
//
//
// Output:
//      A negative value if the first parameter is greater than the second
//      parameter, or a positive value if the first parameter is less than
//      the second parameter, or a value of zero if the parameters are equal.
//
// ============================================================================

int     SortDown(const void* vptr1, const void* vptr2)
{
     const  int *ptr1 = vptr1;
     const  int *ptr2 = vptr2;
     auto   int value1;
     auto   int value2;

     value1 = *ptr1;
     value2 = *ptr2;

     return (value2 - value1);


}  // end of "SortUp"



// ==== SortUp ================================================================
//
// This is the comparison function for qsort so that the array can be sorted
// in ascending order.
//
// Input:
//      vptr1 [IN]          -- a void pointer containing the address of a single
//                             array element
//
//      vptr2 [IN]          -- a void pointer containing the address of a single
//                             array element
//
// Output:
//      A negative value if the first parameter is less than the second
//      parameter, or a positive value if the first parameter is greater than
//      the second parameter, or a value of zero if the parameters are equal.
//
// ============================================================================

int     SortUp(const void* vptr1, const void* vptr2)
{
    const   int *ptr1;
    ptr1 = vptr1;
    const   int *ptr2;
    ptr2 = vptr2;
    auto    int value1;
    auto    int value2;

    value1 = *ptr1;
    value2 = *ptr2;

    if(value1 > value2)
    {
        return 1;
    }
    else if(value1 < value2)
    {
        return -1;
    }
    else
    {
        return 0;
    }

}  // end of "SortUp"



// ==== WriteInts =============================================================
//
// This function writes the contents of the caller's array to an output file.
//
// Input:
//      fname [IN]          -- the name of the output file to open
//
//      array [IN]          -- the base address of the integer array to write
//                             to the output file
//
//      numElems [IN]       -- the number of elements in the array
//
// Output:
//      A value of TRUE if everything goes okay, FALSE otherwise.
//
// ============================================================================

int     WriteInts(const char  *fname, const int  array[], int  numElems)
{
    auto FILE* file;

    file = fopen(fname, "w");

    if(file == NULL)
    {
        printf("Error opening %s.\n", fname);
        return FALSE;
    }

    for(int index = 0; index < numElems; index++)
    {
        fprintf(file, "%d\n", array[index]);
    }
    fclose(file);

    return TRUE;


}  // end of "WriteInts"
