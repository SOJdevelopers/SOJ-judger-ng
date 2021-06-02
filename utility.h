#ifndef _SOJ_JUDGER_UTILITY_HEADER_
#define _SOJ_JUDGER_UTILITY_HEADER_

#include "env.h"
#include <cstdio>
#include <cstdlib>

namespace SOJ_JUDGER_NAMESPACE {
	String escapeShellArg(const String & arg) {
		String res = "'";
		for (size_t i = 0; i < (int) arg.size(); ++i) {
			if (arg[i] == '\'') {
				res += R"'\''";
			} else {
				res += arg[i];
			}
		}
		res += "'";
		return res;
	}

	String realpath(const String & path) {
		static char real[PATH_MAX + 1];
		if (realpath(path.c_str(), real) == NULL) {
			return "";
		}
		return real;
	}

	int execute(const char * cmd) {
		return system(cmd);
	}

	int executef(const char *fmt, ...) {
		const int MaxL = 512;
		static char cmd[MaxL];
		va_list ap;
		va_start(ap, fmt);
		int res = vsnprintf(cmd, MaxL, fmt, ap);
		if (res < 0 || res >= MaxL) {
			return -1;
		}
		res = execute(cmd);
		va_end(ap);
		return res;
	}

	String filePreview(const String & name, const size_t len = 128) {
		FILE * f = fopen(name.c_str(), "r");
		if (f == NULL) {
			return "";
		}
		String res = "";
		int c;
		while (c = fgetc(f), c != EOF && res.size() < len + 4) {
			res += c;
		}
		if (res.size() > len + 3) {
			res.resize(len);
			res += "...";
		}
		fclose(f);
		return res;
	}
	void fileHideToken(const String & name, const String & token) {
		executef("cp %s %s.bak", name.c_str(), name.c_str());

		FILE * rf = fopen((name + ".bak").c_str(), "r");
		FILE * wf = fopen(name.c_str(), "w");
		int c;
		for (int i = 0; i <= (int) token.size(); i++) {
			c = fgetc(rf);
			char ch = i < (int) token.size() ? token[i] : '\n';
			if (c != ch) {
				fprintf(wf, "%s\n", IS_UNAUTHORIZED_OUTPUT.c_str());
				fclose(rf);
				fclose(wf);
				return ;
			}
		}
		while (c = fgetc(rf), c != EOF) {
			fputc(c, wf);
		}
		fclose(rf);
		fclose(wf);
	}

	inline String htmlSpecialChars(const String & s) {
		String r;
		for (int i = 0; i < (int) s.size(); ++i) {
			switch (s[i]) {
				case '&' : r += "&amp;"; break;
				case '<' : r += "&lt;"; break;
				case '>' : r += "&gt;"; break;
				case '"' : r += "&quot;"; break;
				case '\0': r += "<b>\\0</b>"; break;
				default  : r += s[i]; break;
			}
		}
		return r;
	}

}

#endif
