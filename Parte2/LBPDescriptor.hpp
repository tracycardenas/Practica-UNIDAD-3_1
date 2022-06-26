
#include <iostream>
#include <cstdlib>
#include <vector>

#include <opencv2/core/core.hpp>
#include <sstream> // Librería para manejo de flujos de texto y datos. Permite realizar conversiones de tipo.
#include <fstream> // Librería para manejo de archivos (lectura y escritura)

#include <filesystem>

using namespace std;
using namespace cv;

#define compab_mask_inc(ptr,shift) \
{ value |= ((unsigned int)(cntr - *ptr) & 0x80000000) \
>> (31-shift); ptr++; }

class LBPDescriptor{

    private:
        int* LBP8(const int*, int , int);

    public:
        LBPDescriptor();
        vector<int> histogramaLBP(Mat);
        vector<string> listarDir(string);
};