/*
** Copyright (c) 2011 - 10^10^10, Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from Spot-On without specific prior written permission.
**
** SPOT-ON IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** SPOT-ON, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QPrintPreviewDialog>
#include <QPrinter>
#include <iostream>
#include "spot-on-defines.h"
#include "spot-on-pageviewer.h"

spoton_pageviewer::spoton_pageviewer(QWidget *parent):QMainWindow(parent)
{
  m_ui.setupUi(this);
  connect(m_ui.action_Print_Preview,
	  SIGNAL(triggered(void)),
	  this,
	  SLOT(slotPagePrintPreview(void)));
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle(tr("%1: Page Viewer").
		 arg(SPOTON_APPLICATION_NAME));
}

spoton_pageviewer::~spoton_pageviewer()
{
}

void spoton_pageviewer::setHtml(const QString &text)
{
  m_ui.textBrowser->setHtml(text);
}

void spoton_pageviewer::slotPagePrintPreview(void)
{
  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog printDialog(&printer, this);

#ifdef Q_OS_MAC
  printDialog.setAttribute(Qt::WA_MacMetalStyle, false);
#endif
  printDialog.setWindowModality(Qt::WindowModal);
  connect(&printDialog,
	  SIGNAL(paintRequested(QPrinter *)),
	  this,
	  SLOT(slotPrint(QPrinter *)));

  if(printDialog.exec() == QDialog::Accepted)
    m_ui.textBrowser->print(&printer);
}

void spoton_pageviewer::slotPrint(QPrinter *printer)
{
  if(!printer)
    return;

  m_ui.textBrowser->print(printer);
}
