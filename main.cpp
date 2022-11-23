#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

const unsigned int LD_NAME = 30;
const unsigned int L_DATE = 10;
const unsigned int LA_NAME = 22;
const unsigned int MAX = 4000;

class base
{
private:
    char full_name_depositor[LD_NAME];
    unsigned short deposit_sum;
    char deposit_date[L_DATE];
    char full_name_advocate[LA_NAME];

    static unsigned int n; //current number of records
    static base* arr[]; //array of pointers to the class

public:
    void putdata()
    {
        cout << full_name_depositor << endl;
        cout << deposit_sum << endl;
        cout << deposit_date << endl;
        cout << full_name_advocate << endl << endl;
    }

    static void read();
    static void display();

    static void heapsort(int number);
    static int comparision(char* str1, char* str2); /// TO DO
    static void heapsort(int first, int last);
    static void final_sorting();

};

unsigned int base::n;
base* base::arr[MAX];

void base::read()
{
    ifstream in;
    in.open("testBase3.dat", ios::binary);
    if (!in)
    {
        cout << "Unable to open the file!\n"; return;
    }
    else cout << "The file is open\n";

    n = 0;

    while(true)
    {
        arr[n] = new base;
        in.read((char*)arr[n], sizeof(base));
        if (in.eof()) break;
        n++;
    }

    cout << "Reading " << n << " records\n";
}

void base::display()
{
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        char ch = 'y';

        while (k < 200 && ch == 'y')
        {
            for (int i = 20*k; i < 20*(k + 1); i++)
            {
            cout << i + 1 << ")" << endl; //print the number of record
            arr[i] -> putdata();
            }

            cout << "Do you want to output the following 20 database records? (y/n) ";
            cin >> ch;
            cout << endl;

            while (ch != 'n' && ch != 'y')
            {
                cout << "\nUnable to recognize the command\n" << endl;
                cout << "Do you want to output the following 20 database records? (y/n) ";
                cin >> ch;
            }

            if (ch == 'n') break;

            k++;
         } break;
    }
}

void base::heapsort(int number)
{
    int L = (number - 1)/2;
    while (L >= 0)
    {
        // building (L, n) pyramid
        base* x = arr[L];
        int i = L;

        while (true)
        {
            int j;
            if (i == 0) j = 1;
            else j = 2*i;

            if (j > number - 1) break;

            if ((j < number - 1) && ((arr[j + 1] -> deposit_sum) <= (arr[j] -> deposit_sum))) j = j + 1;

            if ((x -> deposit_sum) <= (arr[j] -> deposit_sum)) break;

            arr[i] = arr[j];
            i = j;
        }
        arr[i] = x;

        L = L - 1;
    }

    int R = number - 1;
    base* temp = nullptr;

    while (R >= 1)
    {
        temp = arr[0];
        arr[0] = arr[R];
        arr[R] = temp;

        R = R - 1;

        // building (1, R) pyramid
        base* x = arr[0];
        int i = 0;

        while (true)
        {
            int j;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j > R) break;

            if ((j < R) && ((arr[j + 1] -> deposit_sum) <= (arr[j] -> deposit_sum))) j = j + 1;

            if ((x -> deposit_sum) <= (arr[j] -> deposit_sum)) break;

            arr[i] = arr[j];
            i = j;
        }
        arr[i] = x;
    }
    //for (int k = 0; k < 4000; k++) arr[k] -> putdata();
}

int base::comparision(char* str1, char* str2)
{
    char arr1[7];
    char arr2[7];

    arr1[0] = str1[6];
    arr1[1] = str1[7];
    arr1[2] = str1[3];
    arr1[3] = str1[4];
    arr1[4] = str1[0];
    arr1[5] = str1[1];

    arr2[0] = str2[6];
    arr2[1] = str2[7];
    arr2[2] = str2[3];
    arr2[3] = str2[4];
    arr2[4] = str2[0];
    arr2[5] = str2[1];

    /*for(int i = 0, j = 0; j < 6 && i < 10; i++)
    {
        if(str1[i] != '-' && str2[i] != '-')
        {
            arr1[j] = str1[i];
            arr2[j] = str2[i];
            //cout << "i = " << i  << " " << "j = " << j << endl;
            //cout << "arr1[j] = " << arr1[j]  << " " << "arr2[j] = " << arr2[j] << endl;
            j++;
        }
    }*/

    int data1, data2;
    sscanf(arr1, "%d", &data1);
    sscanf(arr2, "%d", &data2);

    //cout << "data1 = " << data1  << " " << "data2 = " << data2 << endl;
    //cout << "res = " << res << endl;

    return data1 - data2;
}

void base::heapsort(int first, int last)
{
    cout << "First = " << first << ", last = " << last << endl;

    int L = last/2;
    while (L >= first)
    {
        // building (L, n) pyramid
        base* x = arr[L];
        int i = L;

        while (true)
        {
            int j;
            if (i == 0) j = 1;
            else j = 2*i;

            int compare1, compare2;

            if (j > last) break;

            compare1 = comparision(arr[j + 1] -> deposit_date,  arr[j] -> deposit_date);
            if ((j < last) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[j] -> deposit_date);
            if ( compare2 <= 0) break;

            arr[i] = arr[j];
            i = j;
        }
        arr[i] = x;

        L = L - 1;
    }

    int R = last;
    base* temp = nullptr;

    while (R >= first + 1)
    {
        temp = arr[first];
        arr[first] = arr[R];
        arr[R] = temp;

        R = R - 1;

        // building (1, R) pyramid
        base* x = arr[first];
        int i = first;

        while (true)
        {
            int j;
            int compare1, compare2;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j > R) break;

            compare1 = comparision(arr[j + 1] -> deposit_date,  arr[j] -> deposit_date);
            if ((j < R) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[j] -> deposit_date);
            if (compare2 <= 0) break;

            arr[i] = arr[j];
            i = j;
        }
        arr[i] = x;
    }

    for (int k = first; k <= last; k++)
    {
        cout << k << ")" << endl;
        arr[k] -> putdata();
    }
}

void base::final_sorting() /// FIX! not sorting for deposit_sum < 50000 !
{
    int a = 0, b, temp;
    while (a < MAX)
    {
        temp = a;

        while ((arr[a] -> deposit_sum) == (arr[a + 1] -> deposit_sum)) a++;

        b = a;
        a = temp;

        cout << "*******************************************" << endl;
        cout << "a = " << a << ", b = " << b << endl;

        base::heapsort(a, b);

        a = b + 1;

        cout << "a = " << a << ", b = " << b << endl;
        cout << "*******************************************" << endl;

        getchar();
    }
}


int main()
{
    base::read();
    //base::display();
    base::heapsort(MAX);

    base::final_sorting();

    return 0;
}
