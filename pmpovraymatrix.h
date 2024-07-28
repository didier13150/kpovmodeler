//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2002 by Andreas Zehender
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


#ifndef PMPOVRAYMATRIX_H
#define PMPOVRAYMATRIX_H



#include "pmobject.h"

/**
 * Class for povray matrix transformations.
 */

class PMPovrayMatrix : public PMObject
{
   typedef PMObject Base;
public:
   /**
    * Creates an identity matrix
    */
   PMPovrayMatrix( PMPart* part );
   /**
    * Copy constructor
    */
   PMPovrayMatrix( const PMPovrayMatrix& m );
   /**
    * deletes the object
    */
   virtual ~PMPovrayMatrix();

   /** */
   virtual PMObject* copy() const override { return new PMPovrayMatrix( *this ); }
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
    * Returns a new @ref PMPovrayMatrixEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /** */
   virtual QString pixmap() const override { return QString( "pmmatrix" ); }

   /**
    * Returns the matrix values.
    */
   PMVector values() const { return m_values; }
   /**
    * Sets the matrix values. Has to be a vector with size 12.
    */
   void setValues( const PMVector& v );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /** */
   virtual bool hasTransformationMatrix() const override { return true; }
   /** */
   virtual PMMatrix transformationMatrix() const override;

private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMMatrixMementoID { PMMatrixID };
   PMVector m_values;

   static PMMetaObject* s_pMetaObject;
};

#endif
