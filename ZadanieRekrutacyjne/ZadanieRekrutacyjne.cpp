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
    ofstream ofs("data.bin", ios::binary);
    char comunicate[1024];
    int k = 0;

    while (ifs.peek() != EOF)
    {
        char* temp = new char[sizeof(Record)];
        ifs.read(temp, sizeof(Record));

        Record* first_record = (Record*)temp;

        cout << first_record->numer_16_bit << " ";
        
        cout << bitset<8>(first_record->part_of_comunicate) << " ";
        comunicate[k] = first_record->part_of_comunicate;
        k++;

        //cout << first_record->padding << " ";

        cout << first_record->big_endian_32_bit << " ";

        cout << first_record->number_floating << " ";

        //cout << first_record->bit_field << " ";
        char* number_7_bit;
        for (int i = 7; i >= 1; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
            cout << ((first_record->bit_field[2] >> i) & 1);
        cout << endl;

        //Sprawdzamy, czy plik jest takiej samej wielkości
        char* tempOfs = new char[sizeof(Record)];
        tempOfs = (char*)(first_record);
        ofs.write(tempOfs,sizeof(Record));
        delete first_record;
    }

    ifs.close();
    ofs.close();    

    for (char i : comunicate) 
    {
        cout << bitset<8>(i);
    }
}


