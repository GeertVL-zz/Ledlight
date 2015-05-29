#include "stdafx.h"
#include "RuntimeErrorStub.h"

static const char * message = "No Error";
static int parameter = -1;
static const char * file = nullptr;
static int line = -1;

void RuntimeErrorStub_Reset() {
	message = "No Error";
	parameter = -1;
}

const char * RuntimeErrorStub_GetLastError() {
	return message;
}

void RuntimeError(const char * m, int p, const char * f, int l) {
	message = m;
	parameter = p;
	file = f;
	line = l;
}

int RuntimeErrorStub_GetLastParameter() {
	return parameter;
}