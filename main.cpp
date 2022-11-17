#include <iostream>
#include <fstream>

using namespace std;

struct base
{
    char full_name_depositor[30];
    unsigned short deposit_sum;
    char deposit_date[10];
    char full_name_advocate[22];
};

int main()
{
    FILE *in;
    in = fopen("testBase3.dat", "rb");

    base record[4000] = {0};

    int j = 0;
    j = fread((base*)record, sizeof(base), 4000, in);
    fclose(in);

    int b[4000];
    for (int i = 0; i < 4000; i++)
    {
        b[i] = i;
    }

    int k = 0;
    char ch = 'y';

    while (k < 200 && ch == 'y')
    {
        for (int i = 20*k; i < 20*(k + 1); i++)
        {
            cout << b[i] + 1 << ") " << endl;
            cout << record[i].full_name_depositor << endl;
            cout << record[i].deposit_sum << endl;
            cout << record[i].deposit_date << endl;
            cout << record[i].full_name_advocate << endl << endl;
        }

        cout << "Do you want to output the following 20 database records? (y/n) ";
        cin >> ch;
        cout << endl;

        if (ch != 'n' && ch != 'y')
        {
            cout << "Unable to recognize the command" << endl;
            cout << "Do you want to output the following 20 database records? (y/n) ";
            cin >> ch;
        }

        if (ch == 'n') break;

        k++;
    }

    return 0;
}
