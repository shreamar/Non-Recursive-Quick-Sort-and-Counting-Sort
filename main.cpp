/**Amar Shrestha
 * 9/6/2020
 * CS4412
 * Project 2
**/

//header files
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <array>
#include <cmath>
#include <chrono>

//prototype
void nonRecursiveQuickSort_v1(unsigned int *list, int listLength);

void nonRecursiveQuickSort_v2(unsigned int *list, int listLength);

void nonRecursiveQuickSort_v3(unsigned int *list, int listLength);

void fooSort(unsigned int* list, int listLength);

void sortingTesting_Wrapper();

int main() {
    sortingTesting_Wrapper();
    return 0;
}

/**
 * Amar Shrestha - 9/4/2020
 * Wrapper function to test efficiency of several different sorting algorithms**/
void sortingTesting_Wrapper() {
    //size of array to be sorted
    const unsigned long long fooLength = 100000;
    unsigned int *foo1 = new unsigned int[fooLength];
    unsigned int *foo2 = new unsigned int[fooLength];

    //fill the array with random numbers
    for (int k = 0; k < fooLength; k++) {
        srand(time(NULL) + k); //initializes random number generator with seed time+k

        const unsigned long long RANGE = pow(2,32);
        //4294967296 = 2^32 is range of unsigned int
        foo1[k] = (RANGE + rand()) % RANGE; //random numbers between 0 to 4294967295
        foo2[k] = foo1[k]; //makes exact copy of foo1 into foo2
    }

    nonRecursiveQuickSort_v3(foo2, fooLength); //sort foo2 so foo2 is identical to foo1 but sorted

    //make copy of unsorted array to be used for testing
    unsigned int *foo1_v2 = new unsigned int[fooLength];
    for (int i = 0; i < fooLength; i++) {
        foo1_v2[i] = foo1[i];
    }

    //clock timer: https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/

    std::cout<<"Array Size: "<<fooLength<<std::endl;

    //non-recursive quick sort pivot: left, foo1
    auto start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v1(foo1, fooLength);
    auto end = std::chrono::steady_clock::now();
    std::cout << "foo1: Non-recursive Quick Sort (pivot:left): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //non-recursive quick sort pivot: left, foo2
    start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v1(foo2, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo2: Non-recursive Quick Sort (pivot:left): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //deallocate foo1 from heap as it is already sorted and not needed anymore
    delete[] foo1;

    //make copy of unsorted array to be used for testing
    unsigned int *foo1_v3 = new unsigned int[fooLength];
    for (int i = 0; i < fooLength; i++) {
        foo1_v3[i] = foo1_v2[i];
    }

    //non-recursive quick sort pivot: middle, foo1
    start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v2(foo1_v2, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo1: Non-recursive Quick Sort (pivot:middle): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //non-recursive quick sort pivot: middle, foo2
    start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v2(foo2, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo2: Non-recursive Quick Sort (pivot:middle): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //deallocate foo1_v2 from heap as it is already sorted and not needed anymore
    delete[] foo1_v2;

    //make copy of unsorted array to be used for testing
    unsigned int *foo1_v4 = new unsigned int[fooLength];
    for (int i = 0; i < fooLength; i++) {
        foo1_v4[i] = foo1_v3[i];
    }

    //non-recursive quick sort pivot: random, foo1
    start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v3(foo1_v3, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo1: Non-recursive Quick Sort (pivot:random): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //non-recursive quick sort pivot: random, foo2
    start = std::chrono::steady_clock::now();
    nonRecursiveQuickSort_v3(foo2, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo2: Non-recursive Quick Sort (pivot:random): "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //deallocate foo1_v3 from heap as it is already sorted and not needed anymore
    delete[] foo1_v3;

    //fooSort foo1
    start = std::chrono::steady_clock::now();
    fooSort(foo1_v4, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo1: FooSort: "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //fooSort foo2
    start = std::chrono::steady_clock::now();
    fooSort(foo2, fooLength);
    end = std::chrono::steady_clock::now();
    std::cout << "foo2: FooSort: "
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / pow(10, 9) << "s"
              << std::endl;

    //deallocate foo1_v4 from heap as it is already sorted and not needed anymore
    delete[] foo1_v4;
}

/**Amar Shrestha - 9/1/2020
 * Verson 1: modified to be C++ compatible
 * quick sort where pivot is left most element of array
 * takes an array of number and array length as arguments
**/
/***************************************************************
          dvb S17 - non recursive Quick Sort based on C bible (K&R the C programming
          Language - 2nd ed p87). left and right initialized to 0 and length-1.
          stackTop index to top element in leftRightStack. Thus for "push", increment
          and then access (leftRightStack[++stackTop]) and for "pop" access then
          decrement (leftRightStack[stackTop--]);
          ********************************************************************/
void nonRecursiveQuickSort_v1(unsigned int *list, int listLength) {
    int lastsmall, foo, left = 0, right = listLength - 1;

    /*maximum numbers of recursions in quick sort is equal to length of the array
     * and every partition requires two stack spaces (i.e. left and right) - Amar S. (9/1/20)*/
    int *leftRightStack = new int[listLength * 2]; //is this big enough!?!?!?

    int stackTop = -1; // index to top element in stack
    leftRightStack[++stackTop] = left; // push left then right.
    leftRightStack[++stackTop] = right;
    while (stackTop >= 0) {
        right = leftRightStack[stackTop--]; // pop right then left
        left = leftRightStack[stackTop--];
        if (left < right) {
            lastsmall = left;
            for (int i = left + 1; i <= right; i++) {
                if (list[i] < list[left]) {
                    lastsmall++;
                    foo = list[i];
                    list[i] = list[lastsmall];
                    list[lastsmall] = foo;
                }
            }
            foo = list[left];
            list[left] = list[lastsmall];
            list[lastsmall] = foo;

            // qSort(list, left, lastsmall - 1);
            leftRightStack[++stackTop] = left;
            leftRightStack[++stackTop] = lastsmall - 1;

            // qSort(list, lastsmall + 1, right);
            leftRightStack[++stackTop] = lastsmall + 1;
            leftRightStack[++stackTop] = right;
        }
    }
    //deallocate leftRightStack from heap
    delete[] leftRightStack;
}

/**Amar Shrestha - 9/1/20
Non-recursive Quick Sort
Pivot element: middle element of the array
**/
void nonRecursiveQuickSort_v2(unsigned int list[], int listLength) {
    int lastsmall, foo, left = 0, right = listLength - 1;

    /*maximum numbers of recursions in quick sort is equal to length of the array
     * and every partition requires two stack spaces (i.e. left and right) - Amar S. (9/1/20)*/
    int *leftRightStack = new int[listLength * 2]; //is this big enough!?!?!?

    int stackTop = -1; // index to top element in stack
    leftRightStack[++stackTop] = left; // push left then right.
    leftRightStack[++stackTop] = right;
    while (stackTop >= 0) {
        right = leftRightStack[stackTop--]; // pop right then left
        left = leftRightStack[stackTop--];

        if (left < right) {
            //take middle element of the array as pivot element
            int pivotIndex = (left + right) / 2;
            //move the pivot element to the left most part of the array
            foo = list[pivotIndex];
            list[pivotIndex] = list[left];
            list[left] = foo;

            lastsmall = left;
            for (int i = left + 1; i <= right; i++) {
                if (list[i] < list[left]) {
                    lastsmall++;
                    foo = list[i];
                    list[i] = list[lastsmall];
                    list[lastsmall] = foo;
                }
            }
            foo = list[left];
            list[left] = list[lastsmall];
            list[lastsmall] = foo;

            // qSort(list, left, lastsmall - 1);
            leftRightStack[++stackTop] = left;
            leftRightStack[++stackTop] = lastsmall - 1;

            // qSort(list, lastsmall + 1, right);
            leftRightStack[++stackTop] = lastsmall + 1;
            leftRightStack[++stackTop] = right;
        }
    }
    //deallocate leftRightStack from heap
    delete[] leftRightStack;
}

/**Amar Shrestha - 9/1/20
Non-recursive Quick Sort
Pivot element: random element of the array
**/
void nonRecursiveQuickSort_v3(unsigned int *list, int listLength) {
    int lastsmall, foo, left = 0, right = listLength - 1;

    /*maximum numbers of recursions in quick sort is equal to length of the array
     * and every partition requires two stack spaces (i.e. left and right) - Amar S. (9/1/20)*/
    int *leftRightStack = new int[listLength * 2]; //is this big enough!?!?!?

    int stackTop = -1; // index to top element in stack
    leftRightStack[++stackTop] = left; // push left then right.
    leftRightStack[++stackTop] = right;
    while (stackTop >= 0) {
        right = leftRightStack[stackTop--]; // pop right then left
        left = leftRightStack[stackTop--];

        if (left < right) {
            //take random element of the array as pivot element
            int pivotIndex = (rand() % (right - left + 1)) + left;
            //move the pivot element to the left most part of the array
            foo = list[pivotIndex];
            list[pivotIndex] = list[left];
            list[left] = foo;

            lastsmall = left;
            for (int i = left + 1; i <= right; i++) {
                if (list[i] < list[left]) {
                    lastsmall++;
                    foo = list[i];
                    list[i] = list[lastsmall];
                    list[lastsmall] = foo;
                }
            }
            foo = list[left];
            list[left] = list[lastsmall];
            list[lastsmall] = foo;

            // qSort(list, left, lastsmall - 1);
            leftRightStack[++stackTop] = left;
            leftRightStack[++stackTop] = lastsmall - 1;

            // qSort(list, lastsmall + 1, right);
            leftRightStack[++stackTop] = lastsmall + 1;
            leftRightStack[++stackTop] = right;
        }
    }
    //deallocate leftRightStack from heap
    delete[] leftRightStack;
}

/**
 * Amar Shrestha - 9/1/2020
 * FooSort or counting sort that counts the frequency of elements in array then
 * traverse the frequency array to sort the elements
 * @param list
 * @param listLength
 */
void fooSort(unsigned int *list, int listLength) {
    //unsigned long long can store numbers upto 2^64-1
    //cannot use unsigned int because its limit is 2^32-1
    const unsigned long long freqCountLength = pow(2, 32);

    unsigned short *freqCount = new unsigned short[freqCountLength]; //0 to 2^32-1 is the range of unsigned int

    //initialize all elements to zero as freqCount is counter
    for (int i = 0; i < freqCountLength; i++) {
        freqCount[i] = 0;
    }

    for (int i = 0; i < listLength; i++) { //counts frequency of all unique elements from list array
        freqCount[list[i]]++;              //stores the frequency of each element in freqCount array
    }

    //puts back element in the original arrays using the frequency counting arrays
    int listIndex = 0;
    for (int j = 0; j < freqCountLength; j++) {
        if (freqCount[j] > 0) {
            for (int i = 0; i < freqCount[j]; i++) {
                list[listIndex++] = j;
            }
        }
    }

    //deallocate freqCount from heap
    delete[] freqCount;
}


