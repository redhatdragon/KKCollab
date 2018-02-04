#pragma once

#include <stdlib.h>



struct BPString {
	char *str;
	int length;
	int maxLength;
};

inline void BPStringInit(struct BPString *_string) {
	_string->str = malloc(17);
	_string->str[16] = 0;
	_string->length = 0;
	_string->maxLength = 16;
}

inline void BPStringDestruct(struct BPString *_string) {
	free(_string->str);
}

inline void BPStringDouble(struct BPString *_string) {
	_string->maxLength *= 2;
	_string->str = (char *) realloc(_string->str, _string->maxLength);
}

void BStringReplace(struct BPString *_string, char *_str, int _length) {
	BPStringDestruct(_string);
	_string->length = _length;
	_string->maxLength = 16;
	while (_string->maxLength < _length) {
		_string->maxLength *= 2;
	}
	_string->str = (char*) malloc(_string->maxLength + 1);
	{
		int i = 0;
		while (i < _length) {
			_string->str[i] = _str[i];
			i++;
		}
		_string->str[i] = 0;
	}
}

void BPStringAppend(struct BPString *_string, struct BPString *_otherString) {
	if (_string->maxLength - _string->length <= _otherString->length) {
		{
			int i = 0;
			while (i < _otherString->length) {
				_string->str[_string->length + i] = _otherString->str[i];
			}
			_string->length += _otherString->length;
		}
	}
	else {
		while (1) {
			BPStringDouble(_string);
			if (_string->maxLength - _string->length <= _otherString->length) break;
		}
		{
			int i = 0;
			while (i < _otherString->length) {
				_string->str[_string->length + i] = _otherString->str[i];
			}
			_string->length += _otherString->length;
		}
	}
}