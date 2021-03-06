/*****************************************************************************
   Major portions of this software are copyrighted by the Medical College
   of Wisconsin, 1994-2000, and are released under the Gnu General Public
   License, Version 2.  See the file README.Copyright for details.
******************************************************************************/

#include "mrilib.h"
#include "thd.h"

/*****************************************************************
  A datablock contains the information needed to access the
  data in memory.
******************************************************************/

/*---------------------------------------------------------------
   Count the number of in-memory sub-bricks actually stored in
   a datablock at this instant.  Returns -1 if an error.
-----------------------------------------------------------------*/

int THD_count_databricks( THD_datablock * dblk )
{
   int ibr , count ;

   if( ! ISVALID_DATABLOCK(dblk) || dblk->brick == NULL ) return -1 ;

   count = 0 ;
   for( ibr=0 ; ibr < dblk->nvals ; ibr++ )
     if( DBLK_BRICK(dblk,ibr) != NULL && DBLK_ARRAY(dblk,ibr) != NULL )
       count++ ;

   return count ;
}

/*---------------------------------------------------------------*/

int THD_count_potential_databricks( THD_datablock * dblk )
{
   int ibr , count ;

   if( ! ISVALID_DATABLOCK(dblk) || dblk->brick == NULL ) return -1 ;

   count = 0 ;
   for( ibr=0 ; ibr < dblk->nvals ; ibr++ )
     if( MRI_HAS_DATA(DBLK_BRICK(dblk,ibr)) ) count++ ;

   return count ;
}

/*---------------------------------------------------------------*/

int THD_subset_loaded( THD_3dim_dataset *dset , int nb , int *bb )
{
   int ii,kk , nvals ;

   if( !ISVALID_DSET(dset) || nb <= 0 || bb == NULL ) return 0 ;
   nvals = DSET_NVALS(dset) ;

   for( ii=0 ; ii < nb ; ii++ ){
     kk = bb[ii] ; if( kk < 0 || kk >= nvals ) return 0 ;
     if( !DSET_BRICK_LOADED(dset,kk) )         return 0 ;
   }
   return 1 ;
}
