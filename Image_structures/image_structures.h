//this function defines the image structures for use with patch match

#ifndef IMAGE_STRUCTURES_H
#define IMAGE_STRUCTURES_H

	#include <math.h>
	#include <float.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <sys/time.h>
    #include <ctime>
    #include <cstdlib> // C standard library
    #include <cstring>
    #include <climits>
    #include <string>
    #include <sstream>
    #include <fstream> // file I/O
    #include <iostream>
    #include <utility>
    #include <stdexcept>
    #include <vector>
    #include <queue>
    #include <bitset>
    #include <unistd.h>
	//#include <windows.h>
    //#include <omp.h>
        
    using std::runtime_error;

	#ifndef MY_PRINTF
	#define MY_PRINTF printf
	#endif
	
	#ifndef NCHANNELS
	#define NCHANNELS 3
	#endif
            
    /** PI */
	#ifndef M_PI
	#define M_PI   3.14159265358979323846
	#endif
            
    #ifndef BYTE_SIZE
	#define BYTE_SIZE 8
	#endif
        
    #ifndef DESCRIPTOR_SIZE
	#define DESCRIPTOR_SIZE 128
	#endif
    
    #ifndef mxPOINTER_CLASS
    #define mxPOINTER_CLASS mxUINT64_CLASS
    #endif
    
    #ifndef IMAGE_INDEXING
	#define IMAGE_INDEXING 0
	#endif
	
	#ifndef ROW_FIRST
	#define ROW_FIRST 0
	#endif
	
	#ifndef COLUMN_FIRST
	#define COLUMN_FIRST 1
	#endif
	
	#ifndef VERBOSE_MODE
	#define VERBOSE_MODE 0
	#endif
            
    #ifndef ASSERT
    #define ASSERT(cond) if (!(cond)) { std::stringstream sout; \
        sout << "Error (line " << __LINE__ << "): " << #cond; \
        throw runtime_error(sout.str()); }
    #endif

    #define GET_VALUE get_value_nTuple_volume
	#define NDIMS 3
	typedef struct coordinate
	{
		int x;
		int y;
		int t;
	}coord;
    
    //various typedefs
    typedef std::pair<float,float> pairFloat;
    typedef std::pair<int,float> pairIntFloat;
    typedef std::vector<pairIntFloat> vectorPairIntFloat;
    
    typedef float imageDataType;

	class nTupleVolume
	{
        private:
            imageDataType *values;
        
        public:
            int nTupleSize;
            int xSize;
            int ySize;
            int tSize;
            int patchSizeX;
            int patchSizeY;
            int patchSizeT;
            int hPatchSizeX;
            int hPatchSizeY;
            int hPatchSizeT;
            int nElsTotal;

            int nX;
            int nY;
            int nT;
            int nC;

			int nDims;
                        
            int indexing;
            int destroyValues;
            
            nTupleVolume(); //create an empty volume
            nTupleVolume(nTupleVolume *imgVolIn);
            nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, int tSizeIn, int indexingIn);
            nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, int indexingIn);
            nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, int tSizeIn, int patchSizeXIn, int patchSizeYIn, int patchSizeTIn, int indexingIn);
            nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, int tSizeIn, int patchSizeXIn, int patchSizeYIn, int patchSizeTIn, int IndexingIn, imageDataType* valuesIn);
            //special case for an image (temporal dimension equal to 1)
            nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, 
            int patchSizeXIn, int patchSizeYIn, int indexingIn);
            //special case for an image (temporal dimension equal to 1)
			nTupleVolume(int nTupleSizeIn, int xSizeIn, int ySizeIn, int patchSizeXIn, int patchSizeYIn, int indexingIn, imageDataType* valuesIn);
            ~nTupleVolume();

            imageDataType get_value(int x, int y, int t, int z);
            //special case for an image (temporal dimension equal to 1)
            imageDataType get_image_value(int x, int y, int z);
            imageDataType* get_value_ptr(int x, int y, int t, int z);
            imageDataType* get_data_ptr();
            void set_value(int x, int y, int t, int z, imageDataType value);
            //special case for an image (temporal dimension equal to 1)
            void set_image_value(int x, int y, int z, imageDataType value);
            
            void set_all_image_values(imageDataType value);
            void add(imageDataType addScalar);
            void multiply(imageDataType multiplyFactor);
            imageDataType sum_nTupleVolume();
            
            imageDataType max_value();
            imageDataType min_value();
            imageDataType mean_value();
            void absolute_value();
            void binarise();
	};
	
    typedef struct paramPM
	{
		//patch sizes
        int patchSizeX;
        int patchSizeY;
        int patchSizeT;
		int nIters;	//number of propagation/random search steps in patchMatch
		int w;		//maximum search radius
		float alpha; //search radius shrinkage factor (0.5 in standard PatchMatch)
		float maxShiftDistance;		//maximum absolute search distance
        int partialComparison;		//indicate whether we only compare partial patches (in the case where some patches are partially occluded)
        int fullSearch;		//full (exhaustive) search instead of PatchMatch
        //texture attributes
        nTupleVolume *normGradX;
        nTupleVolume *normGradY;
        int verboseMode;
	}patchMatchParameterStruct;
	
	typedef nTupleVolume** nTupleVolumePyramid;
	
    typedef struct multiScaleFeaturePyramid
	{
        nTupleVolumePyramid normGradX;
        nTupleVolumePyramid normGradY;
        int nLevels;
	}featurePyramid;
    
float min_float(float a, float b);
float max_float(float a, float b);
int min_int(int a, int b);
int max_int(int a, int b);

char* int_to_string(int value);

float rand_float_range(float a, float b);
int rand_int_range(int a, int b);
float round_float(float a);

long getMilliSecs();

float pow_int(float a, int b);

void show_patch_match_parameters(patchMatchParameterStruct *patchMatchParams);
int check_patch_match_parameters(patchMatchParameterStruct *patchMatchParams);

int check_in_boundaries( nTupleVolume *imgVol, int x, int y, int t);
int check_in_inner_boundaries( nTupleVolume *imgVol, int x, int y, int t, const patchMatchParameterStruct *params);
void clamp_coordinates(nTupleVolume* imgVolA, int *x, int *y, int *t);

//copy nTupleValues from imgVolA(xA,yA,tA) to imgVolB(xB,yB,tB)
void copy_pixel_values_nTuple_volume(nTupleVolume *imgVolA, nTupleVolume *imgVolB, int xA, int yA, int tA, int xB, int yB, int tB);
//copy nTupleValues from imgVolA(x1,y1,0) to imgVolB(x2,y2,0)
void copy_pixel_values_nTuple_image(nTupleVolume *imgVolA, nTupleVolume *imgVolB, int x1, int y1, int x2, int y2);

nTupleVolume* copy_image_nTuple(nTupleVolume *imgVol);

imageDataType calculate_residual(nTupleVolume *imgVol, nTupleVolume *imgVolPrevious, nTupleVolume *occVol);

#endif
