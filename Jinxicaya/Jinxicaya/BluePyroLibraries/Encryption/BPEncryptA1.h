#pragma once

#include "../IOFile.h"

void BPEncryptA1(char *str, char *key) {
	int strLength;
	int keyLength;
	FOR(int i = 0, 1, i++)
		if(str[i] == 0){
			strLength = i;
			break;
		}
	FOR_END

	FOR(int i = 0, 1, i++)
		if(key[i] == 0){
			keyLength = i;
			break;
		}
	FOR_END

	int j = 0;

	FOR(int i = 0, i < strLength, i++)
		if (j == keyLength) j=0;
		str[i] += key[j];
		j++;
	FOR_END
}

void BPDecryptA1(char *str, char *key) {
	int strLength;
	int keyLength;
	FOR(int i = 0, 1, i++)
		if(str[i] == 0){
			strLength = i;
			break;
		}
	FOR_END

	FOR(int i = 0, 1, i++)
		if(key[i] == 0){
			keyLength = i;
			break;
		}
	FOR_END

	int j = 0;

	FOR(int i = 0, i < strLength, i++)
		if (j == keyLength) j=0;
		str[i] -= key[j];
		j++;
	FOR_END
}