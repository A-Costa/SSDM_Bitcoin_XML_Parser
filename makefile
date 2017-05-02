parser: parser.c xml_functions.c functions.c
	gcc -o parser parser.c xml_functions.c functions.c -lmxml
