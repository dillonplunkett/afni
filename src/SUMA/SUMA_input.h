#ifndef SUMA_INPUT_INCLUDED
#define SUMA_INPUT_INCLUDED

#define SUMA_BRUSH_BLOCK 500

void SUMA_input(Widget w, XtPointer clientData, XtPointer callData);
int SUMA_MarkLineSurfaceIntersect (SUMA_SurfaceViewer *sv, SUMA_DO *dov);
void SUMA_momentum(XtPointer clientData, XtIntervalId *id);
SUMA_Boolean  SUMA_AddToBrushStroke (SUMA_SurfaceViewer *sv, int x, int y, GLdouble *NP, GLdouble *FP, SUMA_Boolean Show);
SUMA_Boolean  SUMA_CreateBrushStroke (SUMA_SurfaceViewer *sv);
void  SUMA_ClearBrushStroke (SUMA_SurfaceViewer *sv);
void SUMA_ShowBrushStroke (SUMA_SurfaceViewer *sv, FILE *out);
void SUMA_DrawBrushStroke (SUMA_SurfaceViewer *sv, SUMA_Boolean Incremental);
void SUMA_SetSVForegroundColor (SUMA_SurfaceViewer *sv, const char *Color);
SUMA_DRAWN_ROI * SUMA_ProcessBrushStroke (SUMA_SurfaceViewer *sv, SUMA_Boolean DoubleClick);
SUMA_Boolean SUMA_BrushStrokeToNodeStroke (SUMA_SurfaceViewer *sv);
SUMA_ROI_DATUM *SUMA_NodeStrokeToConnectedNodes (SUMA_SurfaceViewer *sv); 
SUMA_ROI_DATUM *SUMA_LinkTailNodeToNodeStroke (SUMA_SurfaceViewer *sv, SUMA_DRAWN_ROI *DrawnROI);
DListElmt * SUMA_PushActionStack (  DList *ActionStack, DListElmt *StackPos, 
                                    SUMA_ACTION_RESULT (*ActionFunction)(void *ActionData, SUMA_ACTION_POLARITY Pol), 
                                    void *ActionData, 
                                    void (*ActionDataDestructor)(void *Actiondata));
SUMA_ACTION_RESULT SUMA_AddToTailROIDatum (void *data, SUMA_ACTION_POLARITY Pol);
SUMA_ACTION_RESULT SUMA_AddToTailJunctionROIDatum (void *data, SUMA_ACTION_POLARITY Pol);
void SUMA_DestroyROIActionData (void *data);
SUMA_ROI_DATUM *SUMA_LinkThisNodeToNodeInStroke (SUMA_SurfaceViewer *sv, int NonSurf, DListElmt *El);
DListElmt * SUMA_UndoAction (DList *ActionStack, DListElmt *StackPos);
DListElmt * SUMA_RedoAction (DList *ActionStack, DListElmt *StackPos);
void SUMA_FreeBSDatum (void *bsd);
SUMA_BRUSH_STROKE_DATUM * SUMA_CreateBSDatum(void);
SUMA_ACTION_RESULT SUMA_AddFillROIDatum (void *data, SUMA_ACTION_POLARITY Pol);
SUMA_ACTION_RESULT SUMA_FinishedROI (void *data, SUMA_ACTION_POLARITY Pol);
void SUMA_LookAtCoordinates (char *s, void *data);

/*!
   \brief Macro to retrieve the first node and first triangle intersected by a brushstroke 
   Since not all elements of brushstroke have a surface node, the macro continues searching until
   a non-negative SurfNode is found. Note that SurfTri is not monitored.
   
   \param bs (DList *) containing brushstroke
   \param fn (int) the first SurfNode (>= 0) of the list
   \param ft (int) the value of SurfTri corresponding to fn 
   \param NE (DList_Elmt *) pointer to list element where the first SurfNode was found
*/
#define SUMA_BS_FIRST_SURF_NODE(bs, fn, ft, NE)   \
   {  \
      SUMA_BRUSH_STROKE_DATUM *m_bsd=NULL;  \
      \
      if (!dlist_size(bs)) {  \
         fn = -1; \
         ft = -1; \
      } else { \
         do {  \
            if (!NE) NE = dlist_head(bs);   \
            else NE = NE->next; \
            m_bsd = (SUMA_BRUSH_STROKE_DATUM *)NE->data;  \
            fn = m_bsd->SurfNode;   \
            ft = m_bsd->SurfTri; \
         } while ( (NE != dlist_tail(bs)) && fn < 0);   \
      }  \
   }

/*!
   \brief Find the next element in bs that contains a non-negative value for SurfNode
   returns NULL in El if failed to find such an element
*/
#define SUMA_BS_NEXT_SURF_NODE(bs, oEl, El) \
   {  \
      SUMA_BRUSH_STROKE_DATUM *m_bsd=NULL;  \
      \
      if (oEl == dlist_tail (bs))   {\
         El = NULL;  \
      }  else {   \
         El = oEl;   \
         do {  \
            El = El->next;   \
            m_bsd = (SUMA_BRUSH_STROKE_DATUM *)El->data; \
         }  while (El != dlist_tail(bs) && m_bsd->SurfNode < 0);  \
         if (m_bsd->SurfNode < 0) El = NULL; \
      }  \
   }

#define SUMA_BS_COUNT_SURF_NODES(bs, N_SurfNode)  \
   {  \
      SUMA_BRUSH_STROKE_DATUM *m_bsd=NULL;  \
      DListElmt *m_El=NULL;  \
      \
      N_SurfNode = 0;   \
      do {  \
            if (!m_El) m_El = dlist_head(bs);   \
            else m_El = m_El->next;   \
            m_bsd = (SUMA_BRUSH_STROKE_DATUM *)m_El->data; \
            if (m_bsd->SurfNode >= 0) ++N_SurfNode;   \
         } while (m_El != dlist_tail(bs));   \
   }

#define SUMA_REMOVE_NEXT_NON_DECIMATED(bs, Eli, Eln)   \
   {  \
      SUMA_BRUSH_STROKE_DATUM *m_bsd=NULL;  \
      SUMA_Boolean m_wasDecimated;  \
      do {  \
         Eln = Eli->next;   \
         m_bsd = (SUMA_BRUSH_STROKE_DATUM *)Eln->data; \
         if (m_bsd->Decimated) { \
            m_wasDecimated = YUP;   \
            dlist_remove (bs, Eln, (void *)(&m_bsd)); \
            SUMA_FreeBSDatum (m_bsd);  \
         } else {  \
            m_wasDecimated = NOPE;   \
         }  \
      } while (Eln != dlist_tail(bs) && m_wasDecimated);   \
      if (m_bsd->Decimated) Eln = NULL;   \
   }

#endif

            
