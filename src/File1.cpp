// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdint.h>

using namespace std;

int main(int argc, char* argv[]) {
	const char* filename_1;
	const char* filename_2;

	/*filename_1 = "etalon.ips";
	filename_2 = "out.ips"; */

	if (argc != 3) {
		printf(
			"Please specify the parameters: Comparison_ips <path_first_file> <path_second_file>\n");
		printf("Press any key to continue...\n");
		getch();
		return 0;
	}

	filename_1 = argv[1];
	filename_2 = argv[2];

	FILE *f1, *f2;
	f1 = fopen(filename_1, "rb");
	f2 = fopen(filename_2, "rb");

	if (!f1) {
		cout << "No find file: " << filename_1 << endl;
		cout << endl << "\nPress any key to continue...";
		getch();
		return 0;
	}
	if (!f2) {
		cout << "No find file: " << filename_2 << endl;
		cout << endl << "\nPress any key to continue...";
		getch();
		return 0;
	}
	cout << "Open files: " << filename_1 << ", " << filename_2 << endl;
	fseek(f1, 0, SEEK_END);
	fseek(f2, 0, SEEK_END);
	int sz1, sz2, sz;
	sz1 = ftell(f1);
	sz2 = ftell(f2);
	cout << "Size first file: " << sz1 << endl;
	cout << "Size second file: " << sz2 << endl;
	fseek(f1, 9, SEEK_SET);
	fseek(f2, 9, SEEK_SET);
	if (sz1 >= sz2) {
		sz = sz1;
	}
	else {
		sz = sz2;
	}

	// ------------------------main_block---------------------------------------
	unsigned int len_ips_1;
	unsigned int len_ips_2;
	unsigned int len_ips;
	unsigned char byte_1;
	unsigned char byte_2;
	int countAllByte = 0;
	while (!feof(f1) && !feof(f2)) {
		fread(&len_ips_1, 4, 1, f1);
		fread(&len_ips_2, 4, 1, f2);
		if (len_ips_1 >= len_ips_2) {
			len_ips = len_ips_1;
		}
		else {
			len_ips = len_ips_2;
		}
		for (unsigned int i = 0; i < len_ips; i++) {
			fread(&byte_1, sizeof(char), 1, f1);
			fread(&byte_2, sizeof(char), 1, f2);
			if (byte_1 != byte_2) {
				cout << "\nNo coincidence!";
				cout << "\nPackege: " << countAllByte;
				cout << "\nByte: " << i;
				cout << "\nBit:";
				for (int j = 0; j < 8; j++) {
					bool a, b;
					if (byte_1 & 0x01)
						a = 1;
					else
						a = 0;
					if (byte_2 & 0x01)
						b = 1;
					else
						b = 0;

					if (a != b) {
						cout << " " << j;
					}
					byte_1 = byte_1 >> 1;
					byte_2 = byte_2 >> 1;
				}
				cout << endl << "\nPress any key to continue...";
				getch();
				return 0;
			}
		}
		countAllByte += 1;
	}

	// -------------------------------------------------------------------------
	fclose(f1);
	fclose(f2);
	cout << "\nFiles are identical!";
	cout << endl << "\nPress any key to continue...";
	getch();
	return 0;
}
// ---------------------------------------------------------------------------
