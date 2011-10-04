#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
static char *convertHexToBin(char * input, int * bin_lenp) {
	enum { FIRST_ZERO, XSEP, H1, H2 } state= FIRST_ZERO;
	char * output_buf;
	unsigned char number= 0;
	int input_len=strlen(input);
	
	output_buf=malloc(input_len/3+1);
	while (*input) {
		if (isspace(*input))
			goto next;
		switch(state) {
			default: // FIRST_ZERO, make gcov happy
				number = 0;
				if (*input != '0')
					goto done;
				state = XSEP;	
				break;
			case XSEP: 
				if (*input != 'x' &&  *input != 'X')
					goto done;
				state = H1;	
				break;
			case H1:
				if (isdigit(*input)) {
					number = (*input - '0') <<4;
				}else if (*input >='a' && *input <= 'f'){
					number = (*input - 'a' +10) <<4;
				}else if (*input >='A' && *input <= 'F') {
					number = (*input - 'A' +10) <<4;
				} else 
					goto done;
				state = H2;
				break;
			case H2:
				if (isdigit(*input)) {
					number += (*input - '0');
				}else if (*input >='a' && *input <= 'f') {
					number += (*input - 'a' +10);
				}else if (*input >='A' && *input <= 'F') {
					number += (*input - 'A' +10);
				} else 
					goto done;
				output_buf[*bin_lenp] = number;
				(*bin_lenp)++;
				state= FIRST_ZERO;
				break;
		}
next:
		input++;
	}
done:
	output_buf[*bin_lenp] = 0x00;

	return output_buf;
}

static char *convertBinToHex(char * binaryp, int bin_len) {
	char * cur;
	char * output_buf=malloc(bin_len*5+1);
	int hasOne = 0;
	cur = output_buf;
	while (bin_len) {
		sprintf(cur, "0x%02X ", (*binaryp)&0xff);
		cur +=5;
		binaryp++;
		bin_len--;
		hasOne = 1;
	}
	if (hasOne)
		cur[-(1)]='\0';
	else 
		*cur='\0';
	return output_buf;
}
static char *convertQpToBin(char * input, int *bin_lenp) {
	char * cur;
	char * output_buf;
	int length = strlen(input); 
	output_buf=malloc(length+1);
	cur = output_buf;
	while (*input!='\0') {
		if (*input != '=') {
			*cur = *input;
		}else { 
			int number=0 ;
			input++;
			if (isdigit(*input)) {
				number = (*input - '0') <<4;
			}else if (*input >='a' && *input <= 'f'){
				number = (*input - 'a' +10) <<4;
			}else if (*input >='A' && *input <= 'F') {
				number = (*input - 'A' +10) <<4;
			} else 
				break;
			input++;
			if (isdigit(*input)) {
				number += (*input - '0');
			}else if (*input >='a' && *input <= 'f') {
				number += (*input - 'a' +10);
			}else if (*input >='A' && *input <= 'F') {
				number += (*input - 'A' +10);
			} else 
				break;
			*cur = number;

		}
		(*bin_lenp)++;
		input++;
		cur++;
	}
	return output_buf;
}
static char *convertBinToQp(char * binaryp, int bin_len) {
	char * cur;
	char * output_buf=malloc(bin_len*3 +1);
	cur = output_buf;
	while (bin_len) {
		if (isprint(*binaryp)) {
			*cur = *binaryp;
			cur++;	
		}
		else  {
			sprintf(cur, "=%02X", (*binaryp)&0xff);
			cur +=3;
		}	
		binaryp++;
		bin_len--;
	}
	*cur='\0';
	return output_buf;
}
char * convert_text(const char * input_type, const char * output_type, char * input ) {
	char * binaryp= NULL; 
	int bin_len=0;
	char * outputp= NULL; 
	if (0 == strcmp(input_type, "qp")) {
		binaryp = convertQpToBin(input, &bin_len);
	}else if (0 == strcmp(input_type, "bin")) {
		binaryp = strdup(input);
		bin_len = strlen (binaryp);
	}else if (0 == strcmp(input_type, "hex")) {
		binaryp = convertHexToBin(input, &bin_len);
	}
	if (0 == strcmp(output_type, "bin")) {
		outputp=  binaryp;
	}else if (0 == strcmp(output_type, "hex")) {
		outputp= convertBinToHex(binaryp, bin_len);
		free(binaryp);
	}else if (0 == strcmp(output_type, "qp")) {
		outputp= convertBinToQp(binaryp, bin_len);
		free(binaryp);
	}else  {
		free(binaryp);
		return strdup("");	
	}
	return outputp ;
}
