//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2002 by Luis Carvalho
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


#ifndef PMBLENDMAPMODIFIERS_H
#define PMBLENDMAPMODIFIERS_H



#include "pmtexturebase.h"
#include "pmcolor.h"
#include "pmvector.h"

/**
 * Class for povray blendmapmodifierss
 */
class PMBlendMapModifiers : public PMObject
{
   typedef PMObject Base;
public:
   /**
    * The type of the wave form
    */
   enum PMWaveFormType { RampWave, TriangleWave, SineWave, ScallopWave,
                         CubicWave, PolyWave };

   /**
    * Creates an PMBlendMapModifiers
    */
   PMBlendMapModifiers( PMPart* part );
   /**
    * Deletes the object
    */
   virtual ~PMBlendMapModifiers();

   /** */
   virtual PMObject* copy() const override { return new PMBlendMapModifiers( *this ); }

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
    * Returns a new @ref PMBlendMapModifiersEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /** */
   virtual QString pixmap() const override { return QString( "pmblendmapmodifiers" ); }

   /** */
   virtual void restoreMemento( PMMemento* s ) override;

   /** */
   bool isFrequencyEnabled() const { return m_enableFrequency; }
   /** */
   double frequency() const { return m_frequency; }
   /** */
   bool isPhaseEnabled() const { return m_enablePhase; }
   /** */
   double phase() const { return m_phase; }
   /** */
   bool isWaveFormEnabled() const { return m_enableWaveForm; }
   /** */
   PMWaveFormType waveFormType() const { return m_waveFormType; }
   /** */
   double waveFormExponent() const { return m_waveFormExponent; }

   /** */
   void enableFrequency( bool c );
   /** */
   void setFrequency( double c );
   /** */
   void enablePhase( bool c );
   /** */
   void setPhase( double c );
   /** */
   void enableWaveForm( bool c );
   /** */
   void setWaveFormType( PMWaveFormType c );
   /** */
   void setWaveFormExponent( double c );

private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMBlendMapModifiersMementoID { PMEnableFrequencyID, PMFrequencyID,
                         PMEnablePhaseID, PMPhaseID, PMEnableWaveFormID,
                         PMWaveFormTypeID, PMWaveFormExponentID };

   bool m_enableFrequency;
   double m_frequency;
   bool m_enablePhase;
   double m_phase;
   bool m_enableWaveForm;
   PMWaveFormType m_waveFormType;
   double m_waveFormExponent;

   static PMMetaObject* s_pMetaObject;
};


#endif
