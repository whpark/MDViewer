#include "MDViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	std::locale l("ko_kr.utf-8");
	auto gl = std::locale::global(l);

	QApplication app(argc, argv);
	MDViewer window;
	window.show();
	if (argc > 1) {
		auto url = QUrl::fromLocalFile(argv[1]);
		window.LoadURL(url);
	}
	return app.exec();
}
