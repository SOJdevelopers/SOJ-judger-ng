#include <cstdio>

const int MAX_BUFFER = 4 << 20;
char readChar() {
	static char buf[MAX_BUFFER];
	static char * cur = NULL, * end = NULL;
	if (cur == end) {
		cur = buf;
		end = buf + fread(buf, 1, MAX_BUFFER, stdin);
		if (end == cur) return EOF;
	}
	return *cur++;
}

char bufout[MAX_BUFFER];
char * curout = bufout;
void flushOutputBuffer() {
	fwrite(bufout, 1, curout - bufout, stdout);
	curout = bufout;
}
void putChar(char x) {
	*curout++ = x;
	if (curout == bufout + MAX_BUFFER)
		flushOutputBuffer();
}

int main() {
	int sta = -1, spa = 0, ch;
	while ((ch = readChar()) != EOF) {
		if (ch == '\r') continue;
		if (ch == '\n') {
			sta = -1;
			spa = 0;
			putChar('\n');
			continue;
		}
		if (ch == ' ') {
			++spa;
			continue;
		}
		while (spa) putChar(' '), --spa;
		putChar(ch);
		sta = 0;
	}
	if (sta != -1) putChar('\n');
	flushOutputBuffer();
    return 0;
}

