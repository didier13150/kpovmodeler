/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2003 by Andreas Zehender
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

#ifndef PMPOVRAY31_FORMAT_H
#define PMPOVRAY31_FORMAT_H



#include "pmpovrayformat.h"

/**
 * Description class for POV-Ray 3.1
 */
class PMPovray31Format : public PMPovrayFormat
{
public:
   /**
    * Default constructor
    */
   PMPovray31Format();
   /**
    * Destructor
    */
   virtual ~PMPovray31Format();

   /** */
   virtual QString name() const override { return "povray31"; }
   /** */
   virtual QString description() const override { return "POV-Ray 3.1"; }
   /** */
   virtual int services() const override { return AllServices; }
   /** */
   virtual PMParser* newParser( PMPart*, QIODevice* ) const override;
   /** */
   virtual PMParser* newParser( PMPart*, const QByteArray& ) const override;
   /** */
   virtual PMSerializer* newSerializer( QIODevice* ) override;
   /** */
   virtual PMRenderer* newRenderer( PMPart* ) const override;
   /** */
   virtual QString mimeType() const override;
   /** */
   virtual QStringList importPatterns() const override;
   /** */
   virtual QStringList exportPatterns() const override;
};

#endif
