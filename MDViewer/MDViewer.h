#pragma once

#include <string_view>
#include <array>

#include <QtWidgets/QMainWindow>
#include "ui_MDViewer.h"
#include "QDocumentWindow.h"

class QDragEnterEvent;
class QDropEvent;

using namespace std::literals;

class MDViewer : public QDocumentWindow {
	Q_OBJECT

public:
	using this_t = MDViewer;
	using base_t = QDocumentWindow;

public:
	inline static std::array s_exts {".md"sv, ".txt"sv, ".html"sv, ".htm"sv};

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

