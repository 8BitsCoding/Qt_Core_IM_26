#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>
#include <qrandom.h>

/*
UTF-8 is a variable width character encoding capable of encoding all 1,112,064 valid code points in 
Unicode using one to four 8-bits bytes.
The encoding is defined by Unicode standard, and was originally designed by Ken Thopson and Rob Pike.
Called "Unicode"
*/

QString makeData() {
	QString data;

	data.append("Unicode test\r\n");
	for (int i = 0; i < 10; i++) {
		int number = QRandomGenerator::global()->bounded(1112064);
		data.append(number);
	}
	data.append(10);		// \r
	data.append(13);		// \n
	// data.append("\r\n");

	return data;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString data = makeData();
	QString path = QDir::currentPath() + QDir::separator() + "data.txt";

	QFile file(path);
	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);

		stream.setCodec("UTF-8");
		stream << data;
		stream.flush();

		file.close();
	}

	qInfo() << "Done";
	qInfo() << "Unicode:" << data;
	qInfo("");
	qInfo() << "ASCII" << data.toLatin1();

	return a.exec();
}
