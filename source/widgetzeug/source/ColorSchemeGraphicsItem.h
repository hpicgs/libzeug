#pragma once

#include <QGraphicsObject>
#include <QList>

#include <widgetzeug/ColorScheme.h>


class QGraphicsRectItem;


namespace widgetzeug
{

/** @brief Specialized graphics representing a single color scheme.
 *
 * This class is intended for internal use only. As for now, it is exclusively
 * used by the \see ColorSchemePresetsWidget, for showing a list of selectable
 * scheme items. This class handles hovering, rendering specified number of 
 * colors, each discretely represented as quad in a vertical bar.
 */
class ColorSchemeGraphicsItem : public QGraphicsObject
{
    Q_OBJECT
 
public:
	static QImage image(QWidget * widget, const ColorScheme * scheme
		, uint classes, const QSize & size);

public:
	ColorSchemeGraphicsItem(const ColorScheme & scheme
		, QGraphicsItem * parent = nullptr);

    virtual ~ColorSchemeGraphicsItem();

    void setScheme(const ColorScheme & scheme);
    const ColorScheme * scheme();

    void setClasses(uint classes);
    int classes() const;
    
    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);
    ColorScheme::ColorVisionDeficiency deficiency() const;

	void setMargin(qreal margin);
	qreal margin() const;

	void setPadding(qreal padding);
    qreal padding() const;

    void setRectSize(const QSizeF & size);
    const QSizeF & rectSize() const;

    void setSelected(bool selected, bool signal = false);
    bool isSelected() const;
    
    void setDetailedTooltip(bool active);
    bool detailedTooltip() const;

    virtual QRectF boundingRect() const;

    virtual void paint(
        QPainter * painter
    ,   const QStyleOptionGraphicsItem * option
    ,   QWidget * widget = 0);
    
    void updateRects();

    void updateVisibility(ColorScheme::ColorSchemeTypes typeFilter, uint classesFilter);

protected:
    void updateBrushes();
    void updateTooltips();

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    
signals:
    void selected(const ColorScheme & scheme);

protected:    
    const ColorScheme * m_scheme;
    ColorScheme::ColorVisionDeficiency m_deficiency;

    QList<QGraphicsRectItem *> m_rects;
    QGraphicsRectItem * m_frame;

    QSizeF m_rectSize;
	qreal m_margin;  // per item
    qreal m_padding; // per rect

    uint m_classes;
    bool m_selected;
    bool m_detailedTooltip;

    static const QBrush s_selectedBrush;
    static const QBrush s_hoveredBrush;
    static const QPen s_pen;
};

} // namespace widgetzeug
