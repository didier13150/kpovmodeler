/*
**************************************************************************
                                 description
                             -------------------
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

#ifndef PMBLOBSPHEREEDIT_H
#define PMBLOBSPHEREEDIT_H



#include "pmdetailobjectedit.h"

class PMBlobSphere;
class PMVectorEdit;
class PMFloatEdit ;

/**
 * Dialog edit class for @ref PMBlobSphere
 */
class PMBlobSphereEdit : public PMDetailObjectEdit
{
   Q_OBJECT
   typedef PMDetailObjectEdit Base;
public:
   /**
    * Creates a PMBlobSphereEdit with parent and name
    */
   PMBlobSphereEdit( QWidget* parent );

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
   PMBlobSphere* m_pDisplayedObject;
   PMVectorEdit* m_pCentre;
   PMFloatEdit* m_pRadius;
   PMFloatEdit* m_pStrength;
};


#endif
