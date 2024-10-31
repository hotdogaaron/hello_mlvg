// mlvg test application
// Copyright (C) 2019-2022 Madrona Labs LLC
// This software is provided 'as-is', without any express or implied warranty.
// See LICENSE.txt for details.

#include "helloMadronaView.h"

HelloMadronaView::HelloMadronaView(TextFragment appName, size_t instanceNum) :
  AppView(appName, instanceNum)
{
}

HelloMadronaView::~HelloMadronaView ()
{
}

#pragma mark AppView

void HelloMadronaView::layoutView(DrawContext dc)
{
  Vec2 gridDims = getSizeInGridUnits();
  int gx = gridDims.x();
  int gy = gridDims.y();
  
  // set grid size of entire view, for background and other drawing
  _view->setProperty("grid_units_x", gx);
  _view->setProperty("grid_units_y", gy);
}

void HelloMadronaView::initializeResources(NativeDrawContext* nvg)
{
    _drawingProperties.setProperty("background", colorToMatrix({ 0.8, 0.8, 0.8, 1.0 }));
    _drawingProperties.setProperty("draw_background_grid", true);
    _drawingProperties.setProperty("mark", colorToMatrix({ 0.01, 0.01, 0.01, 1.0 }));
}

void HelloMadronaView::onMessage(Message msg)
{
// We don't take to orders round these parts.
}

