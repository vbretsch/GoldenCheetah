/*
 * Copyright (c) 2014 Damien Grauser (Damien.Grauser@pev-geneve.ch)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef _GC_AllPlotInterval
#define _GC_AllPlotInterval 1

#include "GoldenCheetah.h"
#include "AllPlotWindow.h"

#include <qwt_plot.h>
#include <qwt_scale_widget.h>

class AllPlotIntervalCanvasPicker: public QObject
{
    Q_OBJECT
    G_OBJECT

public:
    AllPlotIntervalCanvasPicker(QwtPlot *plot);
    virtual bool eventFilter(QObject *, QEvent *);
    virtual bool event(QEvent *);

signals:
    void pointClicked(QwtPlotIntervalCurve *, int);
    void pointHover(QwtPlotIntervalCurve *, int);

private:
    QwtPlotCanvas *canvas;
    void select(const QPoint &, bool);
    QwtPlot *plot() { return (QwtPlot *)parent(); }
    const QwtPlot *plot() const { return (QwtPlot *)parent(); }
    QwtPlotIntervalCurve *d_selectedCurve;
    int d_selectedPoint;
};

class AllPlotInterval : public QwtPlot
{
    Q_OBJECT
    G_OBJECT

    public:

        AllPlotInterval(QWidget *parent, Context *context);

        void setDataFromRide(RideItem *_rideItem);

        bool bydist;




    public slots:
        void intervalHover(RideFileInterval chosen);
        void intervalCurveHover(QwtPlotIntervalCurve *); // for tooltip
        void intervalCurveClick(QwtPlotIntervalCurve *curve);



    protected:
        void recalc();
        void sortIntervals();
        void refreshIntervalCurve();
        void refreshIntervalMarkers();

        Context *context;
        RideItem *rideItem;

        QList< QList<RideFileInterval> > intervalLigns;

        QVector<QwtPlotMarker*>                         markers;
        //QVector<QwtPlotIntervalCurve*>  curves;
        QMap<RideFileInterval, QwtPlotIntervalCurve*>   curves;

    private:

        AllPlotIntervalCanvasPicker *canvasPicker; // allow point selection/hover
        LTMToolTip *tooltip;

};



#endif