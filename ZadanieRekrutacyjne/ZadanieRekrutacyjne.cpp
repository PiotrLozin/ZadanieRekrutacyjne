#include <iostream>
#include <fstream>
#include <list>
#include <bitset>

using namespace std;

#pragma pack(push, 1)
struct Record
{
    short numer_16_bit;
    char part_of_comunicate;
    char padding;
    unsigned long big_endian_32_bit;
    float number_floating;
    char bit_field[8];
};
#pragma pack(pop)

int main()
{
    ifstream ifs("sample_data.bin", ios::binary);
    ofstream ofs("data.csv");
    list<char> comunicate;

    if (ifs.good())
    {
        while (ifs.peek() != EOF)
        {
            char* temp = new char[sizeof(Record)];
            ifs.read(temp, sizeof(Record));
            Record* first_record = (Record*)temp;
            comunicate.push_back( first_record->part_of_comunicate);
            char next_column_in_csv = ';'; // due to excel differences depending on settings, I put line end mark and next line mark into variables
            char next_line_in_csv = '\n';

            ofs << first_record->numer_16_bit << next_column_in_csv;
            ofs << first_record->big_endian_32_bit << next_column_in_csv;
            ofs << first_record->number_floating << next_column_in_csv;

            char number = 0;
            number = number | ((first_record->bit_field[1] << 2) & (~3));
            number = (number >> 1) & (~128);
            number = number | ((first_record->bit_field[2] >> 7) & 1);
            unsigned short number_7_bit = (unsigned short)number;
            ofs << number_7_bit << next_line_in_csv;

            delete first_record;
        }

        ofstream comunication("comunicate.txt");
        for (char i : comunicate)
        {
            comunication << i;
        }

        ifs.close();
        ofs.close();
        comunication.close();
    }
    else
    {
        cout << "Error due to bad file open";
    }
}


