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
    char comunicate[1025];
    int k = 0;

    if (ifs.good())
    {
        while (ifs.peek() != EOF)
        {
            char* temp = new char[sizeof(Record)];
            ifs.read(temp, sizeof(Record));
            Record* first_record = (Record*)temp;
            comunicate[k] = first_record->part_of_comunicate;
            k++;

            ofs << first_record->numer_16_bit << ";";
            ofs << first_record->big_endian_32_bit << ";";
            ofs << first_record->number_floating << ";";

            unsigned short number_7_bit = 0;
            for (int i = 7; i >= 1; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
                number_7_bit += (unsigned short)((first_record->bit_field[2] >> i) & 1);
            ofs << number_7_bit << "\n";
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


