#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <windows.h>

using namespace std;

const unsigned int LD_NAME = 30;
const unsigned int L_DATE = 10;
const unsigned int LA_NAME = 22;
const unsigned int MAX = 4000;

bool wrong_key = false;

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
    int index;
    search_res_queue *next;
} *res;

//tree
struct tree
{
    int index;
    tree *left;
    tree *right;
    int balance;
} *btree;

int index[MAX + 1];
base *arr[MAX]; //array of pointers
int n; //current number of records

//for queue
search_res_queue *qhead;
search_res_queue *qtail;
int qn;

void read_base() //to RAM
{
    int i = 0;

    ifstream in;
    in.open("testBase3.dat", ios::binary);
    if (!in)
    {
        cout << "Unable to open the file!\n";
        exit(0);
    }
    else cout << "The file is open\n";

    while(i < MAX)
    {
        arr[i] = new base;
        in.read((char*)arr[i], sizeof(base));
        if (in.eof()) break;
        i++;
    }

    in.close();
    n = i;

    cout << "Read " << i << " records\n" << endl;;
}

void display() //20 records
{
    for (int i = 0; i < MAX; i++)
    {
        int k = 0;
        char ch = 'y';

        while (k < 200 && ch == 'y')
        {
            for (int i = 20*k; i < 20*(k + 1); i++)
            {
            cout << setw(5) << i + 1 << ")"; //print the number of record
            cout << setw(31) << arr[index[i]] -> full_name_depositor;
            cout << setw(10) << arr[index[i]] -> deposit_sum;
            cout << setw(10) << arr[index[i]] -> deposit_date;
            cout << setw(23) << arr[index[i]] -> full_name_advocate << endl;
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
        base* x = arr[index[L]];
        int t = index[L];
        int i = L;

        while (true)
        {
            int j;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j > number - 1) break;

            if ((j < number - 1) && ((arr[index[j + 1]] -> deposit_sum) <= (arr[index[j]] -> deposit_sum))) j = j + 1;

            if ((x -> deposit_sum) <= (arr[index[j]] -> deposit_sum)) break;

            index[i] = index[j];
            i = j;
        }
        index[i] = t;

        L = L - 1;
    }

    int R = number - 1;
    int temp;
    int t;

    while (R >= 1)
    {
        temp = index[0];
        index[0] = index[R];
        t = index[R];
        index[R] = temp;

        R = R - 1;

        // building (1, R) pyramid
        base* x = arr[t];
        int i = 0;

        while (true)
        {
            int j;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j > R) break;

            if ((j < R) && ((arr[index[j + 1]] -> deposit_sum) <= (arr[index[j]] -> deposit_sum))) j = j + 1;

            if ((x -> deposit_sum) <= (arr[index[j]] -> deposit_sum)) break;

            index[i] = index[j];
            i = j;
        }
        index[i] = t;

    }
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

    return atoi(arr1) - atoi(arr2);
}

void heapsort(int first, int last) //sort by deposit date
{
    int compare1, compare2;
    int L = first + (last - first)/2;

    while (L >= first)
    {
        // building (L, n) pyramid
        base* x = arr[index[L]];
        int t = index[L];
        int i = L - first;

        while (true)
        {
            int j;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j + first > last) break;

            compare1 = comparision(arr[index[j + 1 + first]] -> deposit_date,  arr[index[j + first]] -> deposit_date);
            if ((j + first < last) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[index[j + first]] -> deposit_date);
            if ( compare2 <= 0) break;

            index[i + first] = index[j + first];
            i = j;
        }
        index[i + first] = t;

        L = L - 1;
    }

    int R = last;
    int temp;
    int t;

    while (R >= first + 1)
    {
        temp = index[first];
        index[first] = index[R];
        t = index[R];
        index[R] = temp;

        R = R - 1;

        // building (1, R) pyramid
        int i = 0;
        base* x = arr[t];

        while (true)
        {
            int j;
            int compare1, compare2;

            if (i == 0) j = 1;
            else j = 2*i;

            if (j + first > R) break;

            compare1 = comparision(arr[index[j + 1 + first]] -> deposit_date,  arr[index[j + first]] -> deposit_date);
            if ((j + first < R) && (compare1 <= 0)) j = j + 1;

            compare2 = comparision(x -> deposit_date, arr[index[j + first]] -> deposit_date);
            if (compare2 <= 0) break;

            index[i + first] = index[j + first];
            i = j;
        }
        index[i + first] = t;
    }
}

void final_sorting() //sort by deposit sum & deposit date
{
    int a = 0, b, temp;
    while (a < MAX - 1)
    {
        temp = a;

        while (arr[index[a]] -> deposit_sum == arr[index[a + 1]] -> deposit_sum && a < MAX - 1) a++;

        b = a;
        a = temp;

        heapsort(a, b);

        a = b + 1;
    }
}

int queue_is_empty() {return qhead == nullptr ? 1 : 0;} //is queue empty?

void set_next_item(search_res_queue *next) //set the next queue item
{
    if (queue_is_empty()) qhead = next;
    else qtail -> next = next;

    qtail = next;
    qtail -> next = nullptr;
}

void add_to_queue(int index) //add record to the queue
{
    search_res_queue *p = new search_res_queue;
    p -> index = index;
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

    while(p)
    {
        cout << setw(6) << p -> index << ")";
        cout << setw(30) << arr[p -> index] -> full_name_depositor;
        cout << setw(10) << arr[p -> index] -> deposit_sum;
        cout << setw(10) << arr[p -> index] -> deposit_date;
        cout << setw(23) << arr[p -> index] -> full_name_advocate << endl;

        p = p -> next;
    }
}

void search_to_queue(unsigned short key) //search by deposit sum and add records to the queue
{
    cout << "Key = " << key << endl;
    int L = 0, R = MAX - 1, m, a = -1, b;

    while(L < R)
    {
        m = L + floor((R - L)/2);

        if((arr[index[m]] -> deposit_sum) > key)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }

    if((arr[index[L]] -> deposit_sum) == key) a = L;

    if(a >= 0)
    {
        int i = a, c = 0;
        while ((arr[index[i]] -> deposit_sum) == key && i < MAX + 1)
        {
            add_to_queue(index[i]);
            i++;
            c++;
        }
        cout << "Records: " << c << endl;
    }
    else
    {
        wrong_key = true;
        cout << "The element with a key = " << key << " does not exist" << endl << endl;
    }

}

void delete_tree(tree *p)
{
    if (p != nullptr)
    {
        p -> left = p -> right = nullptr;
        p -> balance = 0;
        delete(p);
    }
    p = nullptr;
}

int name_comparision(char* str1, char* str2)
{
    for (int i = 0; str1[i] != '\0'; i++)
    {
        if(str1[i] > str2[i])
        {
            return 1;
        }

        if(str1[i] < str2[i])
        {
            return -1;
        }
    }
    return 0;
}

void create_tree(int i, tree **p)
{
    bool VR = true, HR = true;
    tree *q;

    if((*p) == nullptr)
    {
        *p = new tree;
        (*p) -> index = i;
        (*p) -> left = (*p) -> right = nullptr;
        (*p) -> balance = 0;
        VR = true;
    }

    else
    {
        if(name_comparision(arr[i] -> full_name_advocate, arr[(*p) -> index] -> full_name_advocate) <= 0)
        {
            create_tree(i, &(*p) -> left);
            if(VR)
            {
                if((*p) -> balance == 0)
                {
                    q = (*p) -> left;
                    (*p) -> left = q -> right;
                    q -> right = (*p);
                    (*p) = q;
                    q -> balance = 1;
                    VR = false;
                    HR = true;
                }
                else
                {
                    (*p) -> balance = 0;
                    VR = true;
                    HR = false;
                }
            }
            else HR = false;
        }
        else
        {
            if(name_comparision(arr[i] -> full_name_advocate, arr[(*p) -> index] -> full_name_advocate) > 0)
            {
                create_tree(i, &(*p) -> right);
                if(VR)
                {
                    (*p) -> balance = 1;
                    VR = false;
                    HR = true;
                }
                else
                {
                    if(HR)
                    {
                        if((*p) -> balance > 0)
                        {
                            q = (*p) -> right;
                            (*p) -> right = q -> left;
                            (*p) -> balance = 0;
                            q -> balance = 0;
                            q -> left = (*p);
                            (*p) = q;
                            VR = true;
                            HR = false;
                        }
                        else HR = false;
                    }
                }
            }
        }
    }
}

void display_tree(tree *p)
{
    if(p)
    {
        display_tree(p -> left);
        cout << setw(5) << p -> index << ")"; //print the number of record
        cout << setw(31) << arr[p -> index] -> full_name_depositor;
        cout << setw(10) << arr[p -> index] -> deposit_sum;
        cout << setw(10) << arr[p -> index] -> deposit_date;
        cout << setw(23) << arr[p -> index] -> full_name_advocate << endl;
        display_tree(p -> right);
    }
}

tree *search_in_tree(char key[LA_NAME], tree *p)
{
    while(p)
    {
        if(name_comparision(key, arr[p -> index] -> full_name_advocate) < 0)
        {
            p = p -> left;
        }

        if(name_comparision(key, arr[p -> index] -> full_name_advocate) > 0)
        {
            p = p -> right;
        }

        else
        {
            return p;
            break;
        }
    }
}

void display_tree_search(char key[LA_NAME], tree *p)
{
    if(p)
    {
        display_tree_search(key, p -> left);
        if(name_comparision(key, arr[p -> index] -> full_name_advocate) == 0)
        {
            cout << setw(5) << p -> index << ")"; //print the number of record
            cout << setw(31) << arr[p -> index] -> full_name_depositor;
            cout << setw(10) << arr[p -> index] -> deposit_sum;
            cout << setw(10) << arr[p -> index] -> deposit_date;
            cout << setw(23) << arr[p -> index] -> full_name_advocate << endl;
        }
        display_tree_search(key, p -> right);
    }
}

int main()
{
    for (int i = 0; i < MAX; i++) index[i] = i;

    read_base();
    cout << setw(40) << "---UNSORTED BASE--" << endl;
    display();
    heapsort(MAX);
    final_sorting();
    cout << setw(40) << "---SORTED BASE--" << endl;
    display();

    cout << setw(40) << "---QUEUE---" << endl;
    delete_queue();
    int sum = 0;
    cout << "Enter the sum: " << endl;
    cin >> ws;
    cin >> sum;
    search_to_queue(sum);
    display_queue();
    cout << endl;
    if (wrong_key == true) exit(0);

    cout << setw(40) << "---TREE---" << endl;
    delete_tree(btree);
    btree = nullptr;
    res = qhead;
    while (res)
    {
        create_tree(res -> index, &btree);
        res = res -> next;
    }
    display_tree(btree);

    cout << setw(40) << "---SEARCH---" << endl;
    char key[LA_NAME];
    cout << "Enter advocate's name: " << endl;
    cin >> ws;
    cin.getline(key, LA_NAME);
    tree *date_search;
    date_search = search_in_tree(key, btree);
    display_tree_search(key, date_search);

    return 0;
}
