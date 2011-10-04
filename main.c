#include "stdio.h"
#include "stdlib.h"
#include "string.h"
char * convert_text(const char * input_type, const char * output_type, char * input );


int test(char * descript, char * t1, char * t2, char *input, char * expect) {
	char * resultp;
	
	resultp = convert_text(t1, t2, input);
	if (strcmp(resultp, expect)!=0)
		printf("Failed test %s expected -%s- but got -%s-\n", descript, expect, resultp);
	free(resultp);
	return 0;
}

int main(int argc, char * argv[]) {
	test("test bin to hex", "bin", "hex", "\005\361\320","0x05 0xF1 0xD0");
	test("test bin to bin", "bin", "bin", "\005\361\208", "\005\361\208");
	test("test hex to hex", "hex", "hex", "0x05 0xF1 0xD0","0x05 0xF1 0xD0");
	test("test hex to bin", "hex", "bin", "0x05 0xF1 0xD0", "\005\361\320");
	test("test hex to qp", "hex", "qp", "0x05d0xF1 0xD0", "=05d=F1=d0");
	test("test qp to hex", "qp", "hex", "=05=F1=d0","0x05 0xF1 0xD0");
	return 0;
}
