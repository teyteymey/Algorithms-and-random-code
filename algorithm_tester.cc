/*
* By: Tatiana Meyer
* B7-PE 19-20
*/

/*
*   ------- EJECUCION EN LINUX --------
*   > g++ -o test.o algorithm_tester.cc
*   > ./test.o
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>
#include <stdlib.h>     /* qsort */

using namespace std;

int compare (const void * a, const void * b){ //de menor a mayor
    return ( *(int*)a - *(int*)b );
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int test_qs(int n_vec){
    ofstream myfile;
    std::string s = std::to_string(n_vec);
    myfile.open ("qs_"+ s +".txt");
    for(int i= 0; i <= 20; i++){
        vector<int> vec_int(n_vec, (rand() % 10000));

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        qsort(&vec_int[0], 20, sizeof(int), compare);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        myfile << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "\n";

    }
    myfile.close();
    return 0;
}

int test_ms(int n_vec){
    ofstream myfile;
    std::string s = std::to_string(n_vec);
    myfile.open ("ms_"+ s +".txt");
    for(int i= 0; i <= 20; i++){
        vector<int> vec_int(n_vec, (rand() % 10000));

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        mergeSort(&vec_int[0], 0, vec_int.size() - 1);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        myfile << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "\n";

    }
    myfile.close();
    return 0;
}

int main (int argc, char** argv) {
    int func, size;
    cout << "Que funcion quieres probar? 1:QS  2:MS" << endl;
    cin >> func;
    cout << "De que tamaño?" << endl;
    cin >> size;
    if (func == 1){
        test_qs(size);
        return 1;
    }else if(func == 2){
        test_ms(size);
        return 1;
    }else{
        cout << "ERROR!" << endl;
        return 0;
    }
}

/*
Pasando el numero del tamaño del vector a testear, crea 20 vectores de tamaño n con valores random
de 0 a 9999.

para cada uno ejecuta qs y guarda el tiempo de ejec en un .txt
con esos valores podemos usar R para realizar el estudio de eficacia.
*/
