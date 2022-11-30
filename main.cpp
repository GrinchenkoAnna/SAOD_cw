#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const unsigned int LD_NAME = 30;
const unsigned int L_DATE = 10;
const unsigned int LA_NAME = 22;
const unsigned int MAX = 4000;

//records from the file
struct base
{
    char full_name_depositor[LD_NAME];
    unsigned short deposit_sum;
    char deposit_date[L_DATE];
    char full_name_advocate[LA_NAME];
};

//queue with search results
struct search_res_queue
{
    base *inf;
    search_res_queue *next;
};

/// add struct for tree

base *arr[MAX]; //array of pointers
int n; //current number of records

//for queue
search_res_queue *qhead;
search_res_queue *qtail;
int qn;

int queue_is_empty() {return qhead == nullptr ? 1 : 0;} //is queue empty?

void set_next_item(search_res_queue *next) //set the next queue item
{
    if (queue_is_empty()) qhead = next;
    else qtail -> next = next;

    qtail = next;
    qtail -> next = nullptr;
}

void add_to_queue(base *inf) //add record to the queue
{
    search_res_queue *p = new search_res_queue;
    p -> inf = inf;
    set_next_item(p);
    qn++;
}

void delete_queue() //make the queue empty
{
    qhead = qtail = nullptr;
    qn = 0;
}

void display_queue() //print the queue (all records)
{
    search_res_queue *p = qhead;

    int i = 0;
    char ch = 'y';

    while(p)
    {
        cout << p -> inf -> full_name_depositor << endl;
        cout << p -> inf -> deposit_sum << endl;
        cout << p -> inf -> deposit_date << endl;
        cout << p -> inf -> full_name_advocate << endl << endl;

        p = p -> next;
        i++;
    }
}

void read_base() //to RAM
{
    ifstream in;
    in.open("testBase3.dat", ios::binary);
    if (!in)
    {
        cout << "Unable to open the file!\n";
        exit(0);
    }
    else cout << "The file is open\n";

    n = 0;

    while(n < MAX)
    {
        arr[n] = new base;
        in.read((char*)arr[n], sizeof(base));
        if (in.eof()) break;
        n++;
    }

    cout << "Reading " << n << " records\n";
}

void display() //20 records
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
            cout << arr[i] -> full_name_depositor << endl;
            cout << arr[i] -> deposit_sum << endl;
            cout << arr[i] -> deposit_date << endl;
            cout << arr[i] -> full_name_advocate << endl << endl;
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

void heapsort(int number) //sort by deposit sum
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

    /*for (int k = 0; k < 4000; k++)
    {
        cout << k + 1 << ")" << endl; //print the number of record
        cout << arr[k] -> full_name_depositor << endl;
        cout << arr[k] -> deposit_sum << endl;
        cout << arr[k] -> deposit_date << endl;
        cout << arr[k] -> full_name_advocate << endl << endl;
    }*/
}

int comparision(char* str1, char* str2)
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

    //cout << "Comparision OK" << endl;
    return atoi(arr1) - atoi(arr2);
}

void heapsort(int first, int last) //sort by deposit date
{
    //cout << "First = " << first << ", last = " << last << endl;

    int L = first + (last - first)/2;
    //cout << "First L = " << L << endl;
    while (L >= first)
    {
        // building (L, n) pyramid
        base* x = arr[L];
        int i = L - first;
        //cout << "L = " << L << endl;

        while (true)
        {
            int j;
            if (i == 0) j = 1;
            else j = 2*i;
            //cout << "i1 = " << i << " j1 = " << j << endl;

            int compare1, compare2;

            if (j + first > last) break;

            compare1 = comparision(arr[j + 1 + first] -> deposit_date,  arr[j + first] -> deposit_date);
            if ((j + first < last) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[j + first] -> deposit_date);
            if ( compare2 <= 0) break;

            arr[i + first] = arr[j + first];
            i = j;
        }
        arr[i + first] = x;

        L = L - 1;
    }

    int R = last;
    //cout << "First R = " << R << endl;

    base* temp = nullptr;

    while (R >= first + 1)
    {
        temp = arr[first];
        arr[first] = arr[R];
        arr[R] = temp;

        R = R - 1;
        //cout << "R = " << R << endl;

        // building (1, R) pyramid
        int i = 0;
        base* x = arr[i + first];

        while (true)
        {
            int j;
            int compare1, compare2;

            if (i == 0) j = 1;
            else j = 2*i;
            //cout << "i2 = " << i << " j2 = " << j << endl;

            if (j + first > R) break;

            compare1 = comparision(arr[j + 1 + first] -> deposit_date,  arr[j + first] -> deposit_date);
            if ((j + first < R) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[j + first] -> deposit_date);
            if (compare2 <= 0) break;

            arr[i + first] = arr[j + first];
            i = j;
        }
        arr[i + first] = x;
    }
    //cout << "Heapsort OK" << endl;

    /*for (int k = first; k <= last; k++)
    {
        cout << k + 1 << ")" << endl; //print the number of record
        cout << arr[k] -> full_name_depositor << endl;
        cout << arr[k] -> deposit_sum << endl;
        cout << arr[k] -> deposit_date << endl;
        cout << arr[k] -> full_name_advocate << endl << endl;
    }*/
}

void final_sorting() //sort by deposit sum & deposit date
{
    int a = 0, b, temp;
    while (a < MAX - 2)
    {
        temp = a;
        //cout << "temp = " << temp << endl;;

        while (arr[a] -> deposit_sum == arr[a + 1] -> deposit_sum && a < MAX - 2) a++;

        b = a;
        a = temp;

        heapsort(a, b);

        a = b + 1;
    }
}

void sum_search(unsigned short key) //search by deposit sum and add records to the queue
{
    cout << "Key = " << key << endl;
    int L = 0, R = MAX - 1, m, a = -1, b;

    while(L < R)
    {
        m = L + floor((R - L)/2);

        if((arr[m] -> deposit_sum) > key)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }

    if((arr[L] -> deposit_sum) == key) a = L;

    if(a >= 0)
    {
        int i = a, c = 0;
        while ((arr[i] -> deposit_sum) == key && i < MAX - 1)
        {
            add_to_queue(arr[i]);
            i++;
            c++;
        }
        b = i - 1;
        cout << "Records: " << c << endl;
    }
    else cout << "The element with a key = " << key << " does not exist" << endl << endl;
}

int main()
{
    read_base();
    //display();

    heapsort(MAX);
    final_sorting();

    sum_search(5000);
    display_queue();

    return 0;
}
