#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MDViewer.h"

class QDragEnterEvent;
class QDropEvent;

class MDViewer : public QMainWindow {
	Q_OBJECT

public:
	MDViewer(QWidget* parent = nullptr);
	~MDViewer();

public:
	bool LoadURL(QUrl const& url);
protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

private:
	Ui::MDViewerClass ui;
};

