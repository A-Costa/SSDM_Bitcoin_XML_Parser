parser: parser.c xml_functions.c functions.c
	gcc -o parser parser.c xml_functions.c functions.c -lmxml
	#gcc -o parser parser.c xml_functions.c functions.c -lpthread -lmxml -L/home/s1953583/mydata/LAB3/mini-xml/lib -I/home/s1953583/mydata/LAB3/mini-xml/include
