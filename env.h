#ifndef _SOJ_JUDGER_ENV_HEADER_
#define _SOJ_JUDGER_ENV_HEADER_
#include <string>

#define SOJ_JUDGER_NAMESPACE sj
#define SOJ_DATA_PATH SOJ_WORK_PATH "/data"
#define SOJ_RESULT_PATH SOJ_WORK_PATH "/result"
#define SOJ_GETSET(a, b) \
	decltype(a) get##b() { return a; } \
	SOJ_CURRENT_CLASS & set##b(decltype(a) x) { a = x; return *this; }

namespace SOJ_JUDGER_NAMESPACE {
	typedef std::string String;

	// IS : Info String
	const String IS_UNAUTHORIZED_OUTPUT = "Unauthorized output";
	const String IS_ACCEPTED            = "Accepted";
	const String IS_ACCEPTABLE          = "Acceptable Answer";
	const String IS_WRONGANSWER         = "Wrong Answer";
	const String IS_DEFAULT             = "default";
	const String IS_RS_MLE              = "Memory Limit Exceeded";
	const String IS_RS_TLE              = "Time Limit Exceeded";
	const String IS_RS_OLE              = "Output Limit Exceeded";
	const String IS_RS_RE               = "Runtime Error";
	const String IS_RS_DGS              = "Dangerous Syscalls";
	const String IS_RS_JGF              = "Judgement Failed";
	const String IS_RS_UKE              = "Unknown Result";
	const String IS_JUDGER_JGF          = "Checker Judgement Failed";
	const String IS_VAL_JGF             = "Validator Judgement Failed";
	const String IS_COMP_FAILED         = "Compile Failed";

}
#endif
