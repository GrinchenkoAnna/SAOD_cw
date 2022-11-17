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

    for (int i = 0; i < 4000; i++)
    {
        cout << record[i].full_name_depositor << endl;
        cout << record[i].deposit_sum << endl;
        cout << record[i].deposit_date << endl;
        cout << record[i].full_name_advocate << endl << endl;
    }
    cout << sizeof(record) << endl;

    return 0;
}
