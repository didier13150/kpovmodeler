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


#ifndef PMSQEEDIT_H
#define PMSQEEDIT_H



#include "pmsolidobjectedit.h"

class PMSuperquadricEllipsoid;
class PMFloatEdit;

/**
 * Dialog edit class for @ref PMSuperquadricEllipsoid
 */
class PMSuperquadricEllipsoidEdit : public PMSolidObjectEdit
{
   Q_OBJECT
   typedef PMSolidObjectEdit Base;
public:
   /**
    * Creates a PMSuperquadricEllipsoidEdit with parent and name
    */
   PMSuperquadricEllipsoidEdit( QWidget* parent );

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
   PMSuperquadricEllipsoid* m_pDisplayedObject;
   PMFloatEdit* m_pValueE;
   PMFloatEdit* m_pValueN;
};


#endif
