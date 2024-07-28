//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2001 by Andreas Zehender
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


#ifndef PMSCALEEDIT_H
#define PMSCALEEDIT_H



#include "pmdialogeditbase.h"

class PMScale;
class PMVectorEdit;

/**
 * Dialog edit class for @ref PMScale
 */
class PMScaleEdit : public PMDialogEditBase
{
   Q_OBJECT
   typedef PMDialogEditBase Base;
public:
   /**
    * Creates a PMScaleEdit with parent and name
    */
   PMScaleEdit( QWidget* parent );

   /** */
   virtual void displayObject( PMObject* o ) override;

   /** */
   virtual bool isDataValid() override;
protected:
   /** */
   virtual void createTopWidgets() override;
   /** */
   virtual void saveContents() override;

private:
   PMScale* m_pDisplayedObject;
   PMVectorEdit* m_pVector;
};


#endif
