/**********
Author: Florian Ballenegger 2020
Adapted from VCVS device code.
**********/
/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

/* actually load the current sensitivity information into the 
 * array previously provided 
 */

#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "nuladefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


int
NULAsLoad(GENmodel *inModel, CKTcircuit *ckt)
{
    NULAmodel *model = (NULAmodel *)inModel;
    NULAinstance *here;
    double   vc;

    /*  loop through all the voltage source models */
    for( ; model != NULL; model = NULAnextModel(model)) {

        /* loop through all the instances of the model */
        for (here = NULAinstances(model); here != NULL ;
                here=NULAnextInstance(here)) {

            if(here->NULAsenParmNo){

                vc = *(ckt->CKTrhsOld + here->NULAcontPosNode)
                        -  *(ckt->CKTrhsOld + here->NULAcontNegNode);

                *(ckt->CKTsenInfo->SEN_RHS[here->NULAbranch] + 
                        here->NULAsenParmNo) += vc;
            }
        }
    }
    return(OK);
}
