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
    static base** index_arr[];

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
    static void index();
};

unsigned int base::n;
base* base::arr[MAX];
//base** base::index_arr[MAX];

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


/*///??
void base::index()
{
    for (int i = 0; i < n; i++)
    {
        index_arr[i] = &arr[i];
        //cout << i+1 << endl;
    }
}*/


int main()
{
    base::read();
    base::display();
    //base::index();

    return 0;
}
