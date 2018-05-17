CC=g++
CFLAGS=-c -g -Wall  `pkg-config --cflags --libs glib-2.0`
LDFLAGS=-ldb_cxx-5.3 -lssl -lcrypto  `pkg-config --cflags --libs glib-2.0`
SOURCES=src/view/Safe.cpp src/model/BaseModel.cpp src/model/Key.cpp src/model/Document.cpp src/dao/KeyDao.cpp src/controller/KeyController.cpp src/controller/ReportController.cpp src/dao/DocumentDao.cpp src/controller/DocumentController.cpp src/service/SignatureService.cpp src/service/report/CsvReport.cpp src/service/report/TxtReport.cpp src/service/report/XmlReport.cpp src/service/ReportService.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE="safe"

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name *.o | xargs rm
