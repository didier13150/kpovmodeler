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


#ifndef PMHEIGHTFIELD_H
#define PMHEIGHTFIELD_H



#include "pmsolidobject.h"

class PMViewStructure;
class PMHeightFieldROAM;

/**
 * Class for povray height fields.
 */

class PMHeightField : public PMSolidObject
{
   typedef PMSolidObject Base;
public:
   /**
    * Height field type
    */
   enum HeightFieldType { HFgif, HFtga, HFpot, HFpng, HFpgm, HFppm, HFsys };
   /**
    * Creates an empty PMHeightField
    */
   PMHeightField( PMPart* part );
   /**
    * Copy constructor
    */
   PMHeightField( const PMHeightField& f );
   /**
    * deletes the PMHeightField
    */
   virtual ~PMHeightField();

   /** */
   virtual PMObject* copy() const override { return new PMHeightField( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;

   /** */
   virtual void serialize( QDomElement& e, QDomDocument& doc ) const override;
   /** */
   virtual void readAttributes( const PMXMLHelper& h ) override;
   /**
    * Returns a new @ref PMHeightFieldEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmheightfield" ); }

   /**
    * Returns the height field type
    */
   HeightFieldType heightFieldType() const { return m_hfType; }
   /**
    * Sets the height field type
    */
   void setHeightFieldType( HeightFieldType t );
   /**
    * Returns the file name
    */
   QString fileName() const { return m_fileName; }
   /**
    * Sets the file name
    */
   void setFileName( const QString& name );
   /**
    * Returns the hierarchy flag
    */
   bool hierarchy() const { return m_hierarchy; }
   /**
    * Sets the hierarchy flag
    */
   void setHierarchy( bool h );
   /**
    * Returns the smooth flag
    */
   bool smooth() const { return m_smooth; }
   /**
    * Sets the smooth flag
    */
   void setSmooth( bool s );
   /**
    * Returns the water level
    */
   double waterLevel() const { return m_waterLevel; }
   /**
    * Sets the water level
    */
   void setWaterLevel( double wl );

   /**
    * Sets the heightfield variance
    */
   static void setVariance( int v );
   /**
    * Returns the heightfield variance
    */
   static int variance() { return s_variance; }

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /** */
   virtual bool hasDisplayDetail() const override { return true; }
   /** */
   virtual void cleanUp() const override;

   static QString typeToString( HeightFieldType t );
   static HeightFieldType stringToType( const QString &str );

protected:
   /** */
   virtual bool isDefault() override;
   /** */
   virtual void createViewStructure() override;
   /** */
   virtual PMViewStructure* defaultViewStructure() const override;
   /** */
   virtual int viewStructureParameterKey() const override { return s_parameterKey + globalDetailKey(); }

private:
   /**
    * Creates the ROAM view structure
    */
   void roamViewStructure();

   /**
    * IDs for @ref PMMementoData
    */
   enum PMHeightFieldMementoID { PMHeightFieldTypeID, PMFileNameID,
                                 PMHierarchyID, PMSmoothID, PMWaterLevelID };

   HeightFieldType m_hfType;
   QString m_fileName;
   bool m_hierarchy;
   bool m_smooth;
   double m_waterLevel;

   bool m_modMap;
   PMHeightFieldROAM* m_pROAM;

   /**
    * The default view structure. It can be shared between height fields
    */
   static PMViewStructure* s_pDefaultViewStructure;
   static int s_variance;
   static int s_parameterKey;

   static PMMetaObject* s_pMetaObject;
};

#endif
