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

#ifndef PMTRANSLATECONTROLPOINT_H
#define PMTRANSLATECONTROLPOINT_H




#include "pmcontrolpoint.h"

/**
 * Control points for translation
 */
class PMTranslateControlPoint : public PMControlPoint
{
public:
   /**
    * Creates a PMTranslateControlPoint with id.
    */
   PMTranslateControlPoint( const PMVector& translation, int id );
   /**
    * Deletes the PMTranslateControlPoint
    */
   virtual ~PMTranslateControlPoint() { }
   
   /** */
   virtual PMVector position() const override { return m_translation; }
   
   /**
    * Sets the translation
    */
   void setTranslation( PMVector trans ) { m_translation = trans; }
   /**
    * Returns the translation
    */
   PMVector translation() const { return m_translation; }

   /** */
   virtual PMCPDisplayType displayType() const override { return CPCross; }
   /** */
   virtual void snapToGrid() override;
protected:
   /** */
   virtual void graphicalChangeStarted() override;
   /** */
   virtual void graphicalChange( const PMVector& startPoint,
                                 const PMVector& viewNormal,
                                 const PMVector& endPoint ) override;
private:
   PMVector m_translation, m_originalTranslation;
};

#endif
