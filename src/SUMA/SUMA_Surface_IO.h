#ifndef SUMA_SURFACE_IO_INCLUDED
#define SUMA_SURFACE_IO_INCLUDED

SUMA_Boolean SUMA_SureFit_Read_Coord (char * f_name, SUMA_SureFit_struct *SF);
SUMA_Boolean SUMA_SureFit_Read_Topo (char * f_name, SUMA_SureFit_struct *SF);
void SUMA_Show_SureFit (SUMA_SureFit_struct *SF, FILE *Out);
SUMA_Boolean SUMA_Free_SureFit (SUMA_SureFit_struct *SF);
SUMA_Boolean SUMA_FreeSurfer_Read (char * f_name, SUMA_FreeSurfer_struct *FS);
SUMA_Boolean SUMA_Free_FreeSurfer (SUMA_FreeSurfer_struct *FS);
void SUMA_Show_FreeSurfer (SUMA_FreeSurfer_struct *FS, FILE *Out);
SUMA_Boolean SUMA_Ply_Read (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_Ply_Write (char * f_name, SUMA_SurfaceObject *SO); 
SUMA_Boolean SUMA_VEC_Write (SUMA_SFname *Fname, SUMA_SurfaceObject *SO);
SUMA_Boolean SUMA_FS_Write (char *fileNm, SUMA_SurfaceObject *SO, char *firstLine);
SUMA_Boolean SUMA_SureFit_Write (SUMA_SFname *Fname, SUMA_SurfaceObject *SO);



#endif
