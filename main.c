#include "stdio.h"
#include "stdlib.h"
#include "string.h"


char * convert_text(const char * input_type, const char * output_type, char * input );



int test(char * filename, int line, char * descript, char * t1, char * t2, char *input, char * expect) {
	char * resultp;
	int result=0;
	
	resultp = convert_text(t1, t2, input);
	if (strcmp(resultp, expect)!=0){
		printf("%s:%d:0 Failed test %s expected -%s- but got -%s-\n", filename, line, descript, expect, resultp);
		result = 1;
	}
done:
	free(resultp);
	return result;
}

int main(int argc, char * argv[]) {
	int result =0;
#define TEST(d,t1,t2,i,e) result = test (__FILE__, __LINE__,d, t1,t2, i,e )
	TEST("test bin to hex", "bin", "hex", "\005\361\320","FAILED");
	result =0;
	TEST("test bin to hex", "bin", "hex", "\005\361\320","0x05 0xF1 0xD0");
	TEST("test bin to bin", "bin", "bin", "\005\361\208", "\005\361\208");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 0xD0","0x05 0xF1 0xD0");
	TEST("test hex to bin", "hex", "bin", "0x05 0xF1 0xD0", "\005\361\320");
	TEST("test hex to bin", "hex", "bin", "0x05 0xf1 0xD0", "\005\361\320");
	TEST("test hex to qp", "hex", "qp", "0X05 0xF1 0xD0", "=05=F1=D0");
	TEST("test hex to qp", "hex", "qp", "0x05 0x0a 0xD0", "=05=0A=D0");
	TEST("test hex to qp", "hex", "qp", "0x05 0xFF 0xD0", "=05=FF=D0");
	TEST("test qp to hex", "qp", "hex", "=05=F1=d0","0x05 0xF1 0xD0");
	TEST("test bin to hex", "bin", "hex", "","");
	TEST("test bin to bin", "bin", "bin", "", "");
	TEST("test hex to hex", "hex", "hex", "","");
	TEST("test hex to bin", "hex", "bin", "", "");
	TEST("test hex to qp", "hex", "qp", "", "");
	TEST("test qp to hex", "qp", "hex", "","");
	TEST("test bin to hex", "bin", "hex", "\005\361\320","0x05 0xF1 0xD0");
	TEST("test bin to bin", "bin", "bin", "\005\361\208", "\005\361\208");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1X0xD0","0x05 0xF1");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF10xXD0","0x05 0xF1");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 00D0","0x05 0xF1");
	
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 0X{{","0x05 0xF1");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 0X0{","0x05 0xF1");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 0X0@","0x05 0xF1");
	TEST("test hex to hex", "hex", "hex", "0x05 0xF1 0X@0","0x05 0xF1");
	TEST("test hex to bin", "hex", "bin", "0x05 0xF1X", "\005\361");
	TEST("test hex to qp", "hex", "qp", "0x05 0xF1F", "=05=F1");
	TEST("test hex to qp", "hex", "qp", "0x05 0xF1 0x0a 0x52", "=05=F1=0AR");
	TEST("test qp to hex", "qp", "hex", "=05=F1F=d0=FA","0x05 0xF1 0x46 0xD0 0xFA");
	TEST("test qp to hex", "qp", "hex", "=05=0a=d0","0x05 0x0A 0xD0");
	TEST("test qp to hex", "qp", "hex", "=05=0a={0","0x05 0x0A");
	TEST("test qp to hex", "qp", "hex", "=05=0a=0{","0x05 0x0A");
	TEST("test qp to hex", "qp", "hex", "=05=0a=@0","0x05 0x0A");
	TEST("test qp to hex", "qp", "hex", "=05=0a=0@","0x05 0x0A");
	
	TEST("test qp to hex", "qp", "ddslas", "=05=F1F=d0","");
	TEST("test qp to hex", "adsdf", "hex", "=05=F1F=d0","");
#undef TEST
	return result;
}
