//-----------------------------------------------------------------------------
// Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//-----------------------------------------------------------------------------

#pragma once

#include "Qt/ToolClips/TCExport.h"


#pragma warning(push)
#pragma warning(disable: 4127 4251 4275 4512 4800 )
#include <QHelpEvent>
#pragma warning(pop)

namespace ToolClips
{

class TCEventPrivate;
//-----------------------------------------------------------------------------
// class TCEvent
//-----------------------------------------------------------------------------
/** \brief This event is sent to the Qt control before the toolclip widget is 
* showing up. The toolclip will show up if either a matching toolclip key is 
* found for the widget or if the widget has a simple tooltip set. 
* If you don't want the advanced toolclips to show up you can just
* ignore the event by calling event->ignore() in your widgets event() function.
* If the event is ignored the procedure will fall back to the ordinary
* Qt tooltip mechanism, which means you'll recieve a QEvent::ToolTip event.
* The TCEvent provides the possibility to define a sensitive area on which
* the toolclip will show up or closes when the mouse has left the area.
* By default this area is the bounding rectangle of the widget receiving the
* toolclip. However sometimes this could just be a sub area or sub widget of 
* the widget receiving the toolclip.
*/
class TOOLCLIPS_EXPORT TCEvent : public QHelpEvent
{
public:

    /** \brief Constructs a TCEvent with the given toolclip reference widget.
    * \see QHelpEvent
    */
    TCEvent( QWidget* refWidget, const QPoint &pos, const QPoint &globalPos );
    ~TCEvent() override;

    /** \brief Defines a custom sensitive toolclip area on which the toolclip
    *  will show up or closes when the mouse has left the area.
    * Note: The area rectangle which should be defined in relative coordinates will 
    * be internally translated back to screen coordinates using the toolclip 
    * widget as base reference.
    * \param tcAreaRect The toolclip area in relative coordinates.
    * \see setToolClipRefWidget()
    */
    void setToolClipAreaRect( const QRect& tcAreaRect );

    /** \brief Returns the custom sensitive toolclip area, if set, otherwise an
    * invalid rectangle.
    * \see setToolClipAreaRect()
    */
    QRect toolClipAreaRect() const;

    /** \brief Defines a custom widget that is taken as reference for the sensitive
    * toolclip area. The toolclip area will be the bounding rectangle of the
    * reference widget. By default the reference widget will be the same widget
    * receiving the TCEvent.
    * \param refWidget The widget that should be taken as reference for
    * displaying the toolclip.
    * \see setToolClipRefWidget()
    */
    void setToolClipRefWidget( QWidget* refWidget );

    /** \brief Returns the toolclip reference widget on which the toolclip will
    * be displayed. By default the reference widget will be the same widget
    * receiving the TCEvent.
    * \see setToolClipRefWidget()
    */
    QWidget* toolClipRefWidget() const;

    /** \brief Returns the Qt generated event type of the TCEvent.
    * \see QEvent::registerEventType()
    */
    static QEvent::Type type();

    /** \brief Sets the key for which the toolclip widget should
    * display a toolclip.
    * If there is no matching toolclip found for the key, the toolclip
    * widget will display the simple tooltip.
    * By default the TCEvent's key is initialized with the
    * the reference widget's object name.
    * \param key The key for which the toolclip widget should
    * display a toolclip.
    * \see toolClipKey(), toolTip()
    */
    void setToolClipKey( const QString& key );

    /** \brief Returns the key for which the toolclip widget should 
    * display a toolclip.
    * If there is no matching toolclip found for the key, the toolclip
    * widget will display the simple tooltip.
    * By default the TCEvent's key is initialized with the
    * the reference widget's object name.
    * \see setToolClipKey(), toolTip()
    */
    QString toolClipKey() const;

    /** \brief Defines a simple tooltip which is displayed by the toolclip
    * widget if there is no matching toolclip key available.
    * By default the TCEvent's tooltip is initialized with the tooltip
    * of the reference widget.
    * \param tooltip The simple tooltip that should be shown if there is no
    * toolclip available.
    * \see toolTip()
    */
    void setToolTip( const QString& tooltip );

    /** \brief Returns a simple tooltip which is displayed by the toolclip
    * widget if there is no matching toolclip key available.
    * By default the TCEvent's tooltip is initialized with the tooltip
    * of the reference widget.
    * \see setToolTip()
    */
    QString toolTip() const;

    /** \brief Defines the alignment of the toolclip widget.
    * The toolclip can be aligned horizontally or vertically to the mouse
    * over area, which is either given by the bounding rectangle of the 
    * reference widget or, if specified, by the toolclip area rectangle.
    * By default the alignment will be vertically so that the toolclip is
    * shown beneath the mouse over area.
    * \param align The alignment of the toolclip widget to the mouse over area.
    * \see toolClipAlign(), setToolClipAreaRect(), setToolClipRefWidget()
    */
    void setToolClipAlign( Qt::Orientation align );

    /** \brief Returns the alignment of the toolclip widget.
    * The toolclip can be aligned horizontally or vertically to the mouse
    * over area, which is either given by the bounding rectangle of the
    * reference widget or, if specified, by the toolclip area rectangle.
    * By default the alignment will be vertically so that the toolclip is
    * shown beneath the mouse over area.
    * \see setToolClipAlign(), setToolClipAreaRect(), setToolClipRefWidget()
    */
    Qt::Orientation toolClipAlign() const;

private:
    Q_DISABLE_COPY( TCEvent );
    Q_DECLARE_PRIVATE( TCEvent );
    TCEventPrivate* d_ptr;
};
};
