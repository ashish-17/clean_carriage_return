HEADERS = -I../include
OBJECTS = app.cpp

default: app

app.o:
	g++ -o app.o $(OBJECTS) $(HEADERS)

app: 
	g++ -o app $(OBJECTS) $(HEADERS)

clean:
	-rm -f app.o app
