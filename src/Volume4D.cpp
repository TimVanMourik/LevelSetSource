#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <typeinfo>

#include "nifti1_io.h"
#include "Volume4D.hpp"

#define UNUSED(_variable) (void)_variable;

template <typename T>
Volume4D<T>::Volume4D(
        ) :
    m_loaded(true),
    m_volumes(0),
    m_numberOfVolumes(0)
{
}

template <typename T>
Volume4D<T>::Volume4D(
        const std::string& _fileName
        ) :
    m_fileName(_fileName),
    m_loaded(false)
{
}

template <typename T>
unsigned int Volume4D<T>::getNumberOfVolumes(
        )
{
    return m_numberOfVolumes;
}

template <typename T>
unsigned int Volume4D<T>::getSizeX(
        )
{
    return m_sizeX;
}

template <typename T>
unsigned int Volume4D<T>::getSizeY(
        )
{
    return m_sizeY;
}

template <typename T>
unsigned int Volume4D<T>::getSizeZ(
        )
{
    return m_sizeZ;
}

template <typename T>
void Volume4D<T>::loadFromFile(
        const std::string& _fileName
        )
{
    m_fileName = _fileName;
    loadFromFile();
}

template <typename T>
const Volume<T>& Volume4D<T>::volumeAt(
        unsigned int _i
        )
{
    return m_volumes[_i];
}

template <typename T>
void Volume4D<T>::loadFromFile()
{
    if(!std::ifstream(m_fileName.c_str()))
    {
        std::cerr << "Sorry, the file that you are trying to open seems not to exist. Please check if the path name is correct.\n";
        return;
    }
    nifti_image* inputNifti;

    //the options is passed on to 'fopen', so the option needs to be 'r' (read)
    char* options = (char*)"r";
    std::cerr << "Opening NifTI...\n";
    nifti_image_open(m_fileName.c_str(), options, &inputNifti);

//    std::cerr << "Loading NifTI data...\n";
    nifti_image_load(inputNifti);
    m_sizeX = inputNifti->nx;
    m_sizeY = inputNifti->ny;
    m_sizeZ = inputNifti->nz;

    m_numberOfVolumes = inputNifti->nt == 0 ? 1 : inputNifti->nt;
    m_volumes.resize(m_numberOfVolumes);
    long int currentDataLocation = (long int) inputNifti->data;
    for(unsigned int i = 0; i < m_numberOfVolumes; ++i)
    {
        m_volumes[i].resize(m_sizeX, m_sizeY, m_sizeZ);
        if(m_volumes[i].n_elem * sizeof(T) * m_numberOfVolumes != inputNifti->nvox * inputNifti->nbyper)
        {
            std::cerr << "My apologies, the size of the volume does not match the size of the input file. ";
            std::cerr << "The reason is most likely that the data type of the constructed volume does not match the data type of the input file. ";
            std::cerr << "In future releases this problem might be fixed automatically. However, for now an empty Volume is returned.\n";
            return;
        }
        ///@todo Thoroughly check the increment of the pointer, it's a bit tricky.
        try
        {
            memcpy(m_volumes[i].memptr(), (const void*) currentDataLocation, m_volumes[i].n_elem * sizeof(T));
        }
        catch (const std::exception&)
        {
            std::cerr << "Failure loading the file. Might it be a little too big for your system?\n";
            return;
        }
        currentDataLocation += m_volumes[i].n_elem * sizeof(T);
    }
    ///@todo see if the nifti needs to be closed again!
    std::cerr << "Volume4D loaded.\n";
}


//template <typename T>
//bool Volume4D<T>::saveAsNifti(
//        const std::string& _fileName,
//        const Matrix44& _matrix
//        )
//{
//    nifti_image* outputNifti = new nifti_image;
//    outputNifti->ndim = 3;
//    int dimension[8] = {(int)this->n_rows, (int)this->n_cols, (int)this->n_slices, 0, 0, 0, 0, 0};
//    outputNifti->nx = dimension[0];
//    outputNifti->ny = dimension[1];
//    outputNifti->nz = dimension[2];
//    outputNifti->nt = dimension[3];
//    outputNifti->nu = dimension[4];
//    outputNifti->nv = dimension[5];
//    outputNifti->nw = dimension[6];
//    outputNifti->dim[0] = dimension[0];
//    outputNifti->dim[1] = dimension[1];
//    outputNifti->dim[2] = dimension[2];
//    outputNifti->dim[3] = dimension[3];
//    outputNifti->dim[4] = dimension[4];
//    outputNifti->dim[5] = dimension[5];
//    outputNifti->dim[6] = dimension[6];
//    outputNifti->dim[7] = dimension[7];
//    outputNifti->nvox = (unsigned int)this->n_elem;
//    outputNifti->nbyper = sizeof(T);

//    outputNifti->datatype = getDataType();

//    int pixDimension[8] = {1, 1, 1, 0, 0, 0, 0, 0};
//    outputNifti->dx = pixDimension[0];
//    outputNifti->dy = pixDimension[1];
//    outputNifti->dz = pixDimension[2];
//    outputNifti->nt = pixDimension[3];
//    outputNifti->nu = pixDimension[4];
//    outputNifti->nv = pixDimension[5];
//    outputNifti->nw = pixDimension[6];
//    outputNifti->nw = pixDimension[7];
//    outputNifti->pixdim[0] = pixDimension[0];
//    outputNifti->pixdim[1] = pixDimension[1];
//    outputNifti->pixdim[2] = pixDimension[2];
//    outputNifti->pixdim[3] = pixDimension[3];
//    outputNifti->pixdim[4] = pixDimension[4];
//    outputNifti->pixdim[5] = pixDimension[5];
//    outputNifti->pixdim[6] = pixDimension[6];
//    outputNifti->pixdim[7] = pixDimension[7];

//    outputNifti->scl_slope = 1;
//    outputNifti->scl_inter = 0;

//    outputNifti->cal_min = 0;
//    outputNifti->cal_max = 0;

//    outputNifti->qform_code = 1;
//    outputNifti->sform_code = 1;

//    outputNifti->freq_dim = 1;
//    outputNifti->phase_dim = 1;
//    outputNifti->slice_dim = 1;

//    outputNifti->slice_code = 1;
//    outputNifti->slice_start = 1;
//    outputNifti->slice_end = 1;
//    outputNifti->slice_duration = 1;

//    mat44 eye;
//    eye.m[0][0] = _matrix(0, 0);    eye.m[0][1] = _matrix(0, 1);    eye.m[0][2] = _matrix(0, 2);    eye.m[0][3] = _matrix(0, 3);
//    eye.m[1][0] = _matrix(1, 0);    eye.m[1][1] = _matrix(1, 1);    eye.m[1][2] = _matrix(1, 2);    eye.m[1][3] = _matrix(1, 3);
//    eye.m[2][0] = _matrix(2, 0);    eye.m[2][1] = _matrix(2, 1);    eye.m[2][2] = _matrix(2, 2);    eye.m[2][3] = _matrix(2, 3);
//    eye.m[3][0] = _matrix(3, 0);    eye.m[3][1] = _matrix(3, 1);    eye.m[3][2] = _matrix(3, 2);    eye.m[3][3] = _matrix(3, 3);

//    nifti_mat44_to_quatern(eye,
//                           &outputNifti->quatern_b, &outputNifti->quatern_c, &outputNifti->quatern_d,
//                           &outputNifti->qoffset_x, &outputNifti->qoffset_y, &outputNifti->qoffset_z,
//                           &outputNifti->dx, &outputNifti->dy, &outputNifti->dz, &outputNifti->qfac);

////    std::cerr << outputNifti->qoffset_x << "\n";
////    std::cerr << outputNifti->qoffset_y << "\n";
////    std::cerr << outputNifti->qoffset_z << "\n";

//    outputNifti->qto_xyz = eye;
//    outputNifti->qto_ijk = nifti_mat44_inverse(eye);

//    outputNifti->sto_xyz = eye;
//    outputNifti->sto_ijk = nifti_mat44_inverse(eye);

////    printMat44(outputNifti->qto_xyz);
////    printMat44(outputNifti->qto_ijk);

//    outputNifti->toffset = 0;

//    outputNifti->xyz_units = NIFTI_UNITS_MM;
//    outputNifti->time_units = NIFTI_UNITS_SEC;

//    outputNifti->nifti_type = 1;

//    outputNifti->intent_code = 0;
//    outputNifti->intent_p1 = 0;
//    outputNifti->intent_p2 = 0;
//    outputNifti->intent_p3 = 0;
//    char intentName[16];
//    strcpy(outputNifti->intent_name, intentName);

//    char description[80];
//    strcpy(outputNifti->descrip, description);
//    char auxFile[24];
//    strcpy(outputNifti->aux_file, auxFile);

//    char* name = (char*) calloc(sizeof(char), strlen(_fileName.c_str()) + 8);
//    strcpy(name, _fileName.c_str());

//    outputNifti->fname = name;
//    outputNifti->iname = name;

//    //352 is the size of the header file
//    outputNifti->iname_offset = 352;
////    outputNifti->swapsize = 0;
////    outputNifti->byteorder = 0;

//    outputNifti->data = this->memptr();
//    outputNifti->num_ext = 0;

//    outputNifti->ext_list = 0;

////    std::cerr << "Nifti parameters set.\n";
//    nifti_image_write(outputNifti);
//    delete outputNifti;

//    return true;
//}

template <typename T>
int Volume4D<T>::getDataType(
        )
{
    T variableT;
    bool boolVariable;
    float floatVariable;
    double doubleVariable;
    if(strcmp(typeid(variableT).name(), typeid(boolVariable).name()) == 0)
    {
        return DT_BINARY;
    }
    else  if(strcmp(typeid(variableT).name(), typeid(floatVariable).name()) == 0)
    {
        return DT_FLOAT;
    }
    else  if(strcmp(typeid(variableT).name(), typeid(doubleVariable).name()) == 0)
    {
        return DT_DOUBLE;
    }
    else
    {
        return DT_UNKNOWN;
    }
    UNUSED(variableT);
    UNUSED(boolVariable);
    UNUSED(floatVariable);
    UNUSED(doubleVariable);
}

template <typename T>
Volume4D<T>::~Volume4D(
        )
{
}

template class Volume4D<double>;
template class Volume4D<float>;
