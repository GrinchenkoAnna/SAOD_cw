#include <iostream>
#include <fstream>

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
    //static void index();
    static void heapsort();
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
            cout << (i + 1) << ") " << endl; //print the number of record
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

void base::heapsort()
{
    int L = (MAX - 1)/2;
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

            if (j > MAX - 1) break;

            if ((j < MAX - 1) && ((arr[j + 1] -> deposit_sum) <= (arr[j] -> deposit_sum))) j = j + 1;

            if ((x -> deposit_sum) <= (arr[j] -> deposit_sum)) break;

            arr[i] = arr[j];
            i = j;
        }
        arr[i] = x;

        L = L - 1;
    }

    int R = MAX - 2;
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


int main()
{
    base::read();
    base::display();

    base::heapsort();
    base::display();

    return 0;
}
