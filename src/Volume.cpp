#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <typeinfo>

#include "nifti1_io.h"
#include "Volume.hpp"

#define UNUSED(_variable) (void)_variable;

template <typename T>
Volume<T>::Volume(
        const unsigned int& _x,
        const unsigned int& _y,
        const unsigned int& _z
        ) try :
    arma::Cube<T>(_x, _y, _z),
    m_loaded(true)
//    boost::multi_array<T, 3>(boost::extents[_x][_y][_z], boost::fortran_storage_order())
{
    //constuctor of Volume
}
catch(std::bad_alloc& _error)
{
    std::cerr << "Failed to allocate memory for a new Volume. bad_alloc caught: " << _error.what() << "\n";
}

template <typename T>
Volume<T>::Volume(
        const std::string& _fileName
        ) :
    arma::Cube<T>(),
    m_fileName(_fileName),
    m_loaded(false)
//    boost::multi_array<T, 3>()
{

}

template <typename T>
void Volume<T>::loadFromFile(
        const std::string& _fileName
        )
{
    m_fileName = _fileName;
    loadFromFile();
}

template <typename T>
void Volume<T>::loadFromFile()
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

    unsigned int sizeX = inputNifti->nx;
    unsigned int sizeY = inputNifti->ny;
    unsigned int sizeZ = inputNifti->nz;

    this->resize(sizeX, sizeY, sizeZ);
//    this->resize(boost::extents[sizeX][sizeY][sizeZ]);
    ///@todo This crashes when the datatype of the nifti is different from T (when this.data is smaller than inputNifti.>data
    ///@todo Look into 4D niftis, does this still work?
//    if(this->num_elements() * sizeof(T) != inputNifti->nvox * inputNifti->nbyper)
    if(inputNifti->nt > 1)
    {
        std::cerr << "Warning: this seems to be a $D NifTI, but you're loading a single volume only.\n";
    }
    if(this->n_elem * sizeof(T) * inputNifti->nt != inputNifti->nvox * inputNifti->nbyper)
    {
        std::cerr << "My sincere apologies, the size of the volume does not match the size of the input file. ";
        std::cerr << "The reason is most likely that the data type of the constructed volume does not match the data type of the input file. ";
        std::cerr << "In future releases this problem might be fixed automatically. However, for now an empty Volume is returned.\n";
        return;
    }
    memcpy(this->memptr(), inputNifti->data, inputNifti->nvox * inputNifti->nbyper);
    nifti_image_unload(inputNifti);
    nifti_image_free(inputNifti);

    std::cerr << "Volume loaded.\n";
}

void printMat44(const mat44& _mat)
{
    std::cerr << _mat.m[0][0] << "\t" << _mat.m[0][1] << "\t" <<  _mat.m[0][2] << "\t" <<  _mat.m[0][3] << "\n" ;
    std::cerr << _mat.m[1][0] << "\t" << _mat.m[1][1] << "\t" <<  _mat.m[1][2] << "\t" <<  _mat.m[1][3] << "\n" ;
    std::cerr << _mat.m[2][0] << "\t" << _mat.m[2][1] << "\t" <<  _mat.m[2][2] << "\t" <<  _mat.m[2][3] << "\n" ;
    std::cerr << _mat.m[3][0] << "\t" << _mat.m[3][1] << "\t" <<  _mat.m[3][2] << "\t" <<  _mat.m[3][3] << "\n" ;
}

template <typename T>
bool Volume<T>::saveAsNifti(
        const std::string& _fileName,
        const Matrix44& _matrix
        )
{
    nifti_image* outputNifti = new nifti_image;
    outputNifti->ndim = 3;
    int dimension[8] = {(int)this->n_rows, (int)this->n_cols, (int)this->n_slices, 0, 0, 0, 0, 0};
    outputNifti->nx = dimension[0];
    outputNifti->ny = dimension[1];
    outputNifti->nz = dimension[2];
    outputNifti->nt = dimension[3];
    outputNifti->nu = dimension[4];
    outputNifti->nv = dimension[5];
    outputNifti->nw = dimension[6];
    outputNifti->dim[0] = dimension[0];
    outputNifti->dim[1] = dimension[1];
    outputNifti->dim[2] = dimension[2];
    outputNifti->dim[3] = dimension[3];
    outputNifti->dim[4] = dimension[4];
    outputNifti->dim[5] = dimension[5];
    outputNifti->dim[6] = dimension[6];
    outputNifti->dim[7] = dimension[7];
    outputNifti->nvox = (unsigned int)this->n_elem;
    outputNifti->nbyper = sizeof(T);

    outputNifti->datatype = getDataType();

    int pixDimension[8] = {1, 1, 1, 0, 0, 0, 0, 0};
    outputNifti->dx = pixDimension[0];
    outputNifti->dy = pixDimension[1];
    outputNifti->dz = pixDimension[2];
    outputNifti->nt = pixDimension[3];
    outputNifti->nu = pixDimension[4];
    outputNifti->nv = pixDimension[5];
    outputNifti->nw = pixDimension[6];
    outputNifti->nw = pixDimension[7];
    outputNifti->pixdim[0] = pixDimension[0];
    outputNifti->pixdim[1] = pixDimension[1];
    outputNifti->pixdim[2] = pixDimension[2];
    outputNifti->pixdim[3] = pixDimension[3];
    outputNifti->pixdim[4] = pixDimension[4];
    outputNifti->pixdim[5] = pixDimension[5];
    outputNifti->pixdim[6] = pixDimension[6];
    outputNifti->pixdim[7] = pixDimension[7];

    outputNifti->scl_slope = 1;
    outputNifti->scl_inter = 0;

    outputNifti->cal_min = 0;
    outputNifti->cal_max = 0;

    outputNifti->qform_code = 1;
    outputNifti->sform_code = 1;

    outputNifti->freq_dim = 1;
    outputNifti->phase_dim = 1;
    outputNifti->slice_dim = 1;

    outputNifti->slice_code = 1;
    outputNifti->slice_start = 1;
    outputNifti->slice_end = 1;
    outputNifti->slice_duration = 1;

    mat44 eye;
    eye.m[0][0] = _matrix(0, 0);    eye.m[0][1] = _matrix(0, 1);    eye.m[0][2] = _matrix(0, 2);    eye.m[0][3] = _matrix(0, 3);
    eye.m[1][0] = _matrix(1, 0);    eye.m[1][1] = _matrix(1, 1);    eye.m[1][2] = _matrix(1, 2);    eye.m[1][3] = _matrix(1, 3);
    eye.m[2][0] = _matrix(2, 0);    eye.m[2][1] = _matrix(2, 1);    eye.m[2][2] = _matrix(2, 2);    eye.m[2][3] = _matrix(2, 3);
    eye.m[3][0] = _matrix(3, 0);    eye.m[3][1] = _matrix(3, 1);    eye.m[3][2] = _matrix(3, 2);    eye.m[3][3] = _matrix(3, 3);

    nifti_mat44_to_quatern(eye,
                           &outputNifti->quatern_b, &outputNifti->quatern_c, &outputNifti->quatern_d,
                           &outputNifti->qoffset_x, &outputNifti->qoffset_y, &outputNifti->qoffset_z,
                           &outputNifti->dx, &outputNifti->dy, &outputNifti->dz, &outputNifti->qfac);

//    std::cerr << outputNifti->qoffset_x << "\n";
//    std::cerr << outputNifti->qoffset_y << "\n";
//    std::cerr << outputNifti->qoffset_z << "\n";

    outputNifti->qto_xyz = eye;
    outputNifti->qto_ijk = nifti_mat44_inverse(eye);

    outputNifti->sto_xyz = eye;
    outputNifti->sto_ijk = nifti_mat44_inverse(eye);

//    printMat44(outputNifti->qto_xyz);
//    printMat44(outputNifti->qto_ijk);

    outputNifti->toffset = 0;

    outputNifti->xyz_units = NIFTI_UNITS_MM;
    outputNifti->time_units = NIFTI_UNITS_SEC;

    outputNifti->nifti_type = 1;

    outputNifti->intent_code = 0;
    outputNifti->intent_p1 = 0;
    outputNifti->intent_p2 = 0;
    outputNifti->intent_p3 = 0;
    char intentName[16];
    strcpy(outputNifti->intent_name, intentName);

    char description[80];
    strcpy(outputNifti->descrip, description);
    char auxFile[24];
    strcpy(outputNifti->aux_file, auxFile);

    char* name = (char*) calloc(sizeof(char), strlen(_fileName.c_str()) + 8);
    strcpy(name, _fileName.c_str());

    outputNifti->fname = name;
    outputNifti->iname = name;

    //352 is the size of the header file
    outputNifti->iname_offset = 352;
//    outputNifti->swapsize = 0;
//    outputNifti->byteorder = 0;

    outputNifti->data = this->memptr();
    outputNifti->num_ext = 0;

    outputNifti->ext_list = 0;

//    std::cerr << "Nifti parameters set.\n";
    nifti_image_write(outputNifti);
    delete outputNifti;

    return true;
}

//template <typename T>
//Volume<T> Volume<T>::sqrt(
//        )
//{
//    /// @todo check the sizes
//    unsigned int sizeX = this->n_rows;
//    unsigned int sizeY = this->n_cols;
//    unsigned int sizeZ = this->n_slices;
//    Volume<T> root(sizeX, sizeY, sizeZ);
//    for(unsigned int x = 0; x < sizeX; ++x)
//    {
//        for(unsigned int y = 0; y < sizeY; ++y)
//        {
//            for(unsigned int z = 0; z < sizeZ; ++z)
//            {
//                root(x, y, z) = std::sqrt((*this)(x, y, z));
//            }
//        }
//    }
//    return root;
//}

template <typename T>
int Volume<T>::getDataType(
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

//template <typename T>
//Volume<T>& Volume<T>::operator+=(
//        const Volume<T>& _volume
//        )
//{
//    /// @todo check the sizes
//    unsigned int sizeX = this->n_rows;
//    unsigned int sizeY = this->n_cols;
//    unsigned int sizeZ = this->n_slices;

////    for(auto i = this->origin(); i < this->origin() + this->num_elements(); ++i)
////    {
////        (*this)[i] += _volume[i];
////    }

//    for(unsigned int x = 0; x < sizeX; ++x)
//    {
//        for(unsigned int y = 0; y < sizeY; ++y)
//        {
//            for(unsigned int z = 0; z < sizeZ; ++z)
//            {
//                (*this)(x, y, z) += _volume(x, y, z);
//            }
//        }
//    }
//    return (*this);
//}

//template <typename T>
//Volume<T>& Volume<T>::operator-=(
//        const Volume<T>& _volume
//        )
//{
//    /// @todo check the sizes
//    unsigned int sizeX = this->n_rows;
//    unsigned int sizeY = this->n_cols;
//    unsigned int sizeZ = this->n_slices;
//    for(unsigned int x = 0; x < sizeX; ++x)
//    {
//        for(unsigned int y = 0; y < sizeY; ++y)
//        {
//            for(unsigned int z = 0; z < sizeZ; ++z)
//            {
//                (*this)(x, y, z) -= _volume(x, y, z);
//            }
//        }
//    }
//    return (*this);
//}

//template <typename T>
//Volume<T>& Volume<T>::operator/=(
//        const Volume<T>& _volume
//        )
//{
//    float epsilon = 1e-14;
//    /// @todo check the sizes
//    unsigned int sizeX = this->n_rows;
//    unsigned int sizeY = this->n_cols;
//    unsigned int sizeZ = this->n_slices;
//    for(unsigned int x = 0; x < sizeX; ++x)
//    {
//        for(unsigned int y = 0; y < sizeY; ++y)
//        {
//            for(unsigned int z = 0; z < sizeZ; ++z)
//            {
//                (*this)(x, y, z) /= _volume(x, y, z) + epsilon;
//            }
//        }
//    }
//    return (*this);
//}

template <typename T>
Volume<T>::~Volume(
        )
{

}

template class Volume<double>;
template class Volume<float>;
