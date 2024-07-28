//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2002 by Luis Carvalho
    email                : lpassos@mail.telepac.pt
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMSLOPE_H
#define PMSLOPE_H



#include "pmobject.h"

/**
 * Class for Repeat Slopes
 */

class PMSlope : public PMObject
{
   typedef PMObject Base;
public:
   /**
    * Creates a PMSlope
    */
   PMSlope( PMPart* part );
   /**
    * Copy constructor
    */
   PMSlope( const PMSlope& s );
   /**
    * deletes the PMSlope
    */
   virtual ~PMSlope();

   /** */
   virtual PMObject* copy() const override { return new PMSlope( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;
   /** */
   virtual void cleanUp() const override;

   /** */
   virtual void serialize( QDomElement& e, QDomDocument& doc ) const override;
   /** */
   virtual void readAttributes( const PMXMLHelper& h ) override;

   /**
    * Returns a new @ref PMSlopeEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmslope" ); }

   double height() const { return m_height; }
   void setHeight( double c );
   double slope() const { return m_slope; }
   void setSlope( double c );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMSlopeMementoID { PMHeightID, PMSlopeID };

   double m_height;
   double m_slope;

   static PMMetaObject* s_pMetaObject;
};

#endif
