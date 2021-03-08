
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#define SUCCESS (0)
#define EPARGS	(-1)
#define EFOPEN	(-2)
#define EFREAD	(-3)
#define EFWRITE (-4)
#define EALLOC	(-5)

static const char encoding_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

struct options {
	char* input;
	char* output;
};


void printError(FILE* stream, const int err, ...) {
	va_list args;
	char* msg;


	fprintf(stream, "Error code: %d\n", err);

	switch (err) {
	case EPARGS:	msg = "Usage: %s -i [input file] -o [output file]\n"; break;
	case EFOPEN:	msg = "Can't open file: %s\n"; break;
	case EFREAD:	msg = "Can't read from file: %s\n"; break;
	case EFWRITE:	msg = "Can't write in file: %s\n"; break;
	case EALLOC:	msg = "Error allocate memory\n"; break;
	default:		msg = "Unknown error\n"; break; }

	va_start(args, err);
	vfprintf(stream, msg, args);
	va_end(args);

	return;
}

int parsArg(int argc, char** argv, struct options* out) {
	bool err = false;
	bool i_flag = false;
	bool o_flag = false;
	int i;


	for (i = 1; !err && i < argc && argv[i][0] == '-'; ++i) {
		switch (argv[i][1]) {
		case 'i':
			if (i_flag || ++i >= argc) {
				err = true;
				break;
			}
			out->input = argv[i];
			i_flag = true;
			break;

		case 'o':
			if (o_flag || ++i >= argc) {
				err = true;
				break;
			}
			out->output = argv[i];
			o_flag = true;
			break;

		default:
			err = true;
			break;
		}
	}

	if (err || !(i_flag && o_flag)) {
		out->input = (char*)NULL;
		out->output = (char*)NULL;
		return EPARGS;
	}

	return SUCCESS;
}

int getDataFromFile(const char* file_name, char** ptr_data) {
	FILE* fd;
	char* data;
	size_t data_size;
	int err;


	fd = fopen(file_name, "r");
	if (fd == (FILE*)NULL) {
		*ptr_data = (char*)NULL;
		return EFOPEN;
	}

	err = fseek(fd, 0, SEEK_END);
	if (err) {
		fclose(fd);
		*ptr_data = (char*)NULL;
		return err;
	}
	data_size = (size_t)ftell(fd);
	err = fseek(fd, 0, SEEK_SET);
	if (err) {
		fclose(fd);
		*ptr_data = (char*)NULL;
		return err;
	}

	data = (char*)malloc(sizeof(char) * (data_size + 1));
	if (data == (char*)NULL) {
		fclose(fd);
		*ptr_data = (char*)NULL;
		return EALLOC;
	}

	if (fread(data, sizeof(char), data_size, fd) < data_size) {
		fclose(fd);
		free(data);
		*ptr_data = (char*)NULL;
		return EFREAD;
	}
	fclose(fd);
	data[data_size] = '\0';

	*ptr_data = data;
	return SUCCESS;
}

int writeDataToFile(const char* file_name, const char* data) {
	FILE* fd;


	fd = fopen(file_name, "w");
	if (fd == (FILE*)NULL) {
		return EFOPEN;
	}

	if (fprintf(fd, "%s\n", data) < 0) {
		fclose(fd);
		return EFWRITE;
	}

	fclose(fd);
	return SUCCESS;
}

char* encodeBase64(const char* data, const size_t data_lenght) {
	char* encode_data;
	size_t encode_lenght;
	size_t i, j;

	unsigned char bit8[3];
	unsigned long bitmask;
	int mod[] = { 0, 2, 1 };


	encode_lenght = 4 * ((data_lenght + 2) / 3);
	encode_data = (char*)malloc(sizeof(char) * (encode_lenght + 1));
	if (encode_data == (char*)NULL) {
		return (char*)NULL;
	}

	for (i = 0, j = 0; i < data_lenght; /*empty*/) {
		bit8[0] = i < data_lenght ? (unsigned char)data[i++] : 0;
		bit8[1] = i < data_lenght ? (unsigned char)data[i++] : 0;
		bit8[2] = i < data_lenght ? (unsigned char)data[i++] : 0;

		bitmask = (bit8[0] << 16) + (bit8[1] << 8) + bit8[2];

		encode_data[j++] = encoding_table[(bitmask >> 3 * 6) & 63];
		encode_data[j++] = encoding_table[(bitmask >> 2 * 6) & 63];
		encode_data[j++] = encoding_table[(bitmask >> 1 * 6) & 63];
		encode_data[j++] = encoding_table[(bitmask >> 0 * 6) & 63];
	}

	for (i = 0; i < mod[data_lenght % 3]; ++i) {
		encode_data[encode_lenght - 1 - i] = '=';
	}
	encode_data[encode_lenght] = '\0';

	return encode_data;
}


int main(int argc, char** argv, char** envp) {
	struct options opt;
	char* data;
	char* encode_data;
	int err;


	err = parsArg(argc, argv, &opt);
	if (err) {
		printError(stderr, err, argv[0]);
		return err;
	}

	err = getDataFromFile(opt.input, &data);
	if (err) {
		if (data != (char*)NULL) {
			free(data);
		}
		printError(stderr, err, opt.input);
		return err;
	}

	encode_data = encodeBase64(data, strlen(data));
	if (encode_data == (char*)NULL) {
		free(data);
		printError(stderr, EALLOC);
		return EALLOC;
	}

	err = writeDataToFile(opt.output, encode_data);
	if (err) {
		printError(stderr, err, opt.output);
	}

	printf("INPUT:\n%s\nOUTPUT:\n%s\n", data, encode_data);

	free(data);
	free(encode_data);
	return SUCCESS;
}

