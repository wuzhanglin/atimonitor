#pragma once

#include <QWidget>

class QTBackgroundWidget : public QWidget
{
public:
	QTBackgroundWidget(QWidget* parent = NULL);
	~QTBackgroundWidget();

	void backGroundColor(const QColor& color);
	const QColor& backGroundColor() const;

	void maskImage(const QString& maskImage);// The mask image filling color should be white.

protected:
	virtual void resizeEvent(QResizeEvent * resizeEvent); // Set the irregular widget area by using the mask image.

private:
	void init();
	void setColorStyle(const QColor& color);
	void setMaskImage(const QSize& size);

private:
	QColor m_color;
	QString m_maskImagePath;

};