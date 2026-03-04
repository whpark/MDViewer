#include <format>

#include <QFileDialog>
#include <QDropEvent>
#include <QMessageBox>
#include <QMimeData>

#include "MDViewer.h"

MDViewer::MDViewer(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionLoad, &QAction::triggered, this, [this]() {
		auto str = QFileDialog::getOpenFileName(nullptr, "Open File", "", "Markdown Files (*.md);;All Files (*.*)");
		auto url = QUrl::fromLocalFile(str);
		LoadURL(url);
	});

	connect(ui.actionAbout, &QAction::triggered, this, [this]() {
		QMessageBox::about(nullptr, "About MDViewer", "MDViewer is a simple Markdown viewer built with Qt.\n\n2026-03-05. wh.park");
	});

	// on drop file
	setAcceptDrops(true);
}

MDViewer::~MDViewer() {
}

bool MDViewer::LoadURL(QUrl const& url) {
	std::filesystem::path path = url.toLocalFile().toStdWString();
	if (path.empty())
		return false;
	if (auto iter = std::ranges::find(s_exts, path.extension().string()); iter == s_exts.end()) {
		QMessageBox::warning(this, "Invalid File", "Please select a Markdown file with .md extension.");
		return false;
	}

	ui.textBrowser->setSource(url);

	setWindowTitle(QString::fromStdWString(std::format(L"MDViewer - {}", path.filename().wstring())));
	return true;
}

void MDViewer::dragEnterEvent(QDragEnterEvent* event) {
	if (auto urls = event->mimeData()->urls(); !urls.isEmpty()) {
		auto const& url = urls.first();
		std::filesystem::path path = url.toLocalFile().toStdWString();
		if (auto iter = std::ranges::find(s_exts, path.extension().string()); iter != s_exts.end()) {
			event->acceptProposedAction();
			return;
		}
	}

	event->ignore();
}

void MDViewer::dropEvent(QDropEvent* event) {
	if (auto urls = event->mimeData()->urls(); !urls.isEmpty()) {
		if (LoadURL(urls.first())) {
			event->acceptProposedAction();
			return;
		}
	}
	event->ignore();
}

