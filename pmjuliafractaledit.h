//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2002 by Andreas Zehender
    email                : zehender@kde.org
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMJULIAFRACTALEDIT_H
#define PMJULIAFRACTALEDIT_H



#include "pmsolidobjectedit.h"
//Added by qt3to4:

class PMJuliaFractal;
class PMVectorEdit;
class PMIntEdit;
class PMFloatEdit;
class QComboBox;

/**
 * Dialog edit class for @ref PMJuliaFractal
 */
class PMJuliaFractalEdit : public PMSolidObjectEdit
{
   Q_OBJECT
   typedef PMSolidObjectEdit Base;
public:
   /**
    * Creates a PMJuliaFractalEdit with parent and name
    */
   PMJuliaFractalEdit( QWidget* parent );

   /** */
   virtual void displayObject( PMObject* o ) override;

   /** */
   virtual bool isDataValid() override;
   
protected:
   /** */
   virtual void createTopWidgets() override;
   /** */
   virtual void saveContents() override;
   
protected slots:
   void slotAlgebraTypeSelected( int );
   void slotFunctionTypeSelected( int );

private:
   PMJuliaFractal* m_pDisplayedObject;
   PMVectorEdit* m_pJuliaParameter;
   QComboBox* m_pAlgebraType;
   QComboBox* m_pFunctionType;
   PMVectorEdit* m_pExponents;
   QLabel* m_pExponentsLabel;
   PMIntEdit* m_pMaxIterations;
   PMFloatEdit* m_pPrecision;
   PMVectorEdit* m_pSliceNormal;
   PMFloatEdit* m_pSliceDistance;
};


#endif
