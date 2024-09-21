#include <windows.h>
#include<stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Define a function pointer for our imported
 * function.
 * This reads as "introduce the new type f_funci as the type:
 *                pointer to a function returning an int and
 *                taking no arguments.
 *
 * Make sure to use matching calling convention (__cdecl, __stdcall, ...)
 * with the exported function. __stdcall is the convention used by the WinAPI
 */

struct AES_ctx
{
	uint8_t RoundKey[176];
};

typedef int(__stdcall* f_funci)(int a, int b);
typedef int(__stdcall* f_init)(struct AES_ctx* ctx, const uint8_t* key);
typedef int(__stdcall* f_encrypt)(const struct AES_ctx* ctx, uint8_t* buf);
typedef int(__stdcall* f_decrypt)(const struct AES_ctx* ctx, uint8_t* buf);
typedef int(__stdcall* f_des)(uint64_t input, uint64_t key, char mode);


HINSTANCE hGetProcIDDLL;

static void phex(uint8_t* str)
{

	uint8_t len = 16;
	unsigned char i;
	for (i = 0; i < len; ++i)
		printf("%.2x", str[i]);
	printf("\n");
}

static int aes_encrypt_decrpyt_ecb(void)
{

	hGetProcIDDLL = LoadLibrary(TEXT("Aes_encryption_decryption.dll"));

	if (!hGetProcIDDLL) {
		printf("could not load the dynamic library\n");
		return EXIT_FAILURE;
	}


	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	uint8_t out[] = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };
	uint8_t in[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
	struct AES_ctx ctx;


	printf("Plain text:\n");
	phex(in);
	f_init AES_init_ctx = (f_init)GetProcAddress(hGetProcIDDLL, "AES_init_ctx");
	f_encrypt  AES_ECB_encrypt = (f_encrypt)GetProcAddress(hGetProcIDDLL, "AES_ECB_encrypt");
	f_encrypt  AES_ECB_decrypt = (f_encrypt)GetProcAddress(hGetProcIDDLL, "AES_ECB_decrypt");

	if (!AES_init_ctx) {
		printf("could not locate the function\n");
		return 1;
	}

	if (!AES_ECB_encrypt) {
		printf("could not locate the function\n");
		return 1;
	}

	if (!AES_ECB_decrypt) {
		printf("could not locate the function\n");
		return 1;
	}

	AES_init_ctx(&ctx, key);
	AES_ECB_encrypt(&ctx, in);

	printf("key:\n");
	phex(key);


	printf("ECB encrypt:\n");
	phex(in);

	AES_ECB_decrypt(&ctx, in);
	printf("ECB decrypt:\n");
	phex(in);


	return 0;

	/*if (0 == memcmp((char*)out, (char*)in, 16)) {
	printf("SUCCESS!\n");
	return(0);
}
else {
	printf("FAILURE!\n");
	return(1);
}*/
}



static int des_encrypt_decrypt()
{
	hGetProcIDDLL = LoadLibrary(TEXT("Des_encryption_decryption.dll"));

	if (!hGetProcIDDLL) {
		printf("could not load the dynamic library\n");
		return EXIT_FAILURE;
	}

	int i;

	uint64_t input = 0x9474B8E8C73BCA7D;
	uint64_t key = 0x0000000000000000;
	uint64_t result = input;

	f_des  des = (f_des)GetProcAddress(hGetProcIDDLL, "des");
	if (!des) {
		printf("could not locate the function\n");
		return 1;
	}


	/*
	 * TESTING IMPLEMENTATION OF DES
	 * Ronald L. Rivest
	 * X0:  9474B8E8C73BCA7D
	 * X16: 1B1A2DDB4C642438
	 *
	 * OUTPUT:
	 * E: 8da744e0c94e5e17
	 * D: 0cdb25e3ba3c6d79
	 * E: 4784c4ba5006081f
	 * D: 1cf1fc126f2ef842
	 * E: e4be250042098d13
	 * D: 7bfc5dc6adb5797c
	 * E: 1ab3b4d82082fb28
	 * D: c1576a14de707097
	 * E: 739b68cd2e26782a
	 * D: 2a59f0c464506edb
	 * E: a5c39d4251f0a81e
	 * D: 7239ac9a6107ddb1
	 * E: 070cac8590241233
	 * D: 78f87b6e3dfecf61
	 * E: 95ec2578c2c433f0
	 * D: 1b1a2ddb4c642438  <-- X16
	 */
	for (i = 0; i < 16; i++) {

		if (i % 2 == 0) {

			result = des(result, result, 'e');
			printf("E: %016llx\n", result);

		}
		else {

			result = des(result, result, 'd');
			printf("D: %016llx\n", result);

		}
	}


	result = des(input, key, 'e');
	printf("E: %016llx\n", result);

	result = des(result, key, 'd');
	printf("D: %016llx\n", result);

	exit(0);
}

int main()
{

	// AES implementation taken from https://github.com/kokke/tiny-AES-c/blob/master/test.c
	aes_encrypt_decrpyt_ecb();

	//Des implementation taken from https://github.com/dhuertas/DES/blob/master/des.c
	des_encrypt_decrypt();
	return EXIT_SUCCESS;
}

