//this is the include function for the spatio-temporal patch-match

#ifndef PATCH_MATCH_H
#define PATCH_MATCH_H


	#include "common_patch_match.h"
	#include "patch_match_tools.h"

	void patch_match_ANN(nTupleVolume *imgVolA, nTupleVolume *imgVolB, nTupleVolume *shiftVol,
        nTupleVolume *imgVolOcc, nTupleVolume *imgVolMod, const patchMatchParameterStruct *params, nTupleVolume *firstGuessVol=NULL);
        
#endif
