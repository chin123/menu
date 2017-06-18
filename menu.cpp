#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Usage:\n";
		std::cout << "./menu filename classname objectname\n";
		exit(0);
	}
	std::ifstream ifile(argv[1]);
	if (!ifile) {
		std::cout << "File open error.\n";
		exit(0);
	}
	int cnt = 0;
	// global lists for the menu, the methods needed and the arguements for these methods.
	char menu[100][100], method[100][100], args[100][100];
	while (!ifile.eof()) {
		char t[100]; // stores the current line being parsed
		ifile.getline(t, 90);
		char *pos = strstr(t, ") { //"); // looking for methods with a comment
		if (pos != NULL) {
			char name[100]; // stores the method name
			char *j = strstr(t,"(") - 1; // just before the closing bracket is the method name
			int i = 0;
			for (;*j != ' '; j--, i++)
				name[i] = *j;
			name[i] = '\0';
			for (int i = 0; i < strlen(name)/2; i++) {
				char temp;
				temp = name[i];
				name[i] = name[strlen(name) - 1 - i];
				name[strlen(name) - 1 - i] = temp;
			}
			strcpy(method[cnt], name);
			strcpy(menu[cnt], pos + strlen(") { // "));
			char targ[100];
			char *pos2 = strstr(t,"(") + 1;
			for (i = 0; *pos2 != ')';i++,pos2++)
				targ[i] = *pos2;
			targ[i] = '\0';
			strcpy(args[cnt], targ);
			cnt++;
		}
	}
	ifile.close();
	std::fstream file(argv[1], std::ios::app);
	char program[] = "\nint main() {\n\tint op;\n\tdo {\n\t\tsystem(\"clear\");\n\t\tcout << \"Menu\\n\";\n";
	file.write(program,strlen(program));
	for (int i = 0; i < cnt; i++) {
		char t[] = "\t\tcout << \"";
		strcat(t,menu[i]);
		strcat(t, "\\n\";\n");
		file.write(t,strlen(t));
	}
	char exit[100];
	sprintf(exit, "\t\tcout << \"%d. Exit\\n\";\n", cnt+1);
	file.write(exit,strlen(exit));
	file << "\t\tcout << \"Choose an option: \";\n";
	file << "\t\tcin >> op;\n";
	file << "\t\t" << argv[2] << " " << argv[3] << ";\n";
	// global lists for all found datatypes, variables of a datatype, and all variables found
	char datatype[100][100], vars[100][100], uniqvars[100][100];
	// cdata stores the number of datatypes and cvar the number of variables
	int cdata = 0, cvar = 0;
	for (int i = 0; i < cnt; i++) {
		if (args[i][0] == '\0') // We should skip empty arg lists
			continue;
		char *s = (char *)args[i];
		while (*s) {
			char td[100], tv[100];
			int c = 0;
			for (; *s != ' ' && *s != '\0'; s++)
				td[c++] = *s;
			td[c] = '\0';
			c = 0;
			s++;
			for (; *s != ',' && *s != '\0'; s++)
				tv[c++] = *s;
			tv[c] = '\0';
			s+=2;
			int f = 0;
			for (int i = 0; i < cvar; i++) {
				if (strcmp(uniqvars[i],tv) == 0) {
					f = 1;
					break;
				}
			}
			if (!f) {
				strcpy(uniqvars[cvar],tv);
				cvar++;
				for (c = 0; c < cdata; c++) {
					if (strcmp(datatype[c],td) == 0) {
						strcat(vars[c], ",");
						strcat(vars[c], tv);
						break;
					}
				}
				if (c == cdata) { // create new datatype
					strcpy(datatype[cdata], td);
					strcpy(vars[cdata], tv);
					cdata++;
				}
			}
		}
	}
	for (int i = 0; i < cdata; i++) {
		file << "\t\t" << datatype[i] << " " << vars[i] << ";\n";
	}
	file << "\t\tswitch (op) {\n";
	for (int i = 0; i < cnt; i++) {
		file << "\t\t\tcase " << i + 1 << ":\n";
		if (args[i][0] != '\0') { // time to parse the args
			char *a = args[i];
			char varlist[100][100];
			int vc = 0;
			while (*a) {
				a = strstr(a," ");
				if (a == NULL)
					break;
				a++;
				int wc = 0;
				while (*a != ',' && *a != '\0') {
					varlist[vc][wc++] = *a++;
				}
				varlist[vc][wc] = '\0';
				a+=2;
				vc++;
			}
			for (int j = 0; j < vc; j++) {
				file << "\t\t\t\tcout << \"Enter the value of " << varlist[j] << ": \";\n";
				file << "\t\t\t\tcin >> " << varlist[j] << ";\n";
			}
			file << "\t\t\t\t" << argv[3] << "." << method[i] << "(";
			for (int j = 0; j < vc; j++) {
				file << varlist[j];
				if (j != vc - 1)
					file << ", ";
			}
			file << ");\n";
		} else {
			file << "\t\t\t\t" << argv[3] << "." << method[i] << "();\n";
		}
		file << "\t\t\t\t" << "break;\n";
	}
	file << "\t\t\tcase " << cnt + 1 << ":\n";
	file << "\t\t\t\tcout << \"Goodbye.\\n\";\n";
	file << "\t\t\t\tbreak;\n";
	file << "\t\t\tdefault:\n\t\t\t\tcout << \"Invalid option.\\n\";\n\t\t\t\tbreak;\n";
	file << "\t\t}\n";
	file << "\t\tgetchar();\n\t\tgetchar();\n";
	file << "\t} while (op != " << cnt + 1 << ");\n";
	file << "\treturn 0;\n";
	file << "}\n";
	file.close();
	return 0;
}
