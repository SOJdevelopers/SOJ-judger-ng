#ifndef _SOJ_JUDGER_RUN_HEADER_
#define _SOJ_JUDGER_RUN_HEADER_

#include "env.h"
#include "limit.h"
#include <cstdarg>

namespace SOJ_JUDGER_NAMESPACE {
#define SOJ_CURRENT_CLASS RunConfig
	class RunConfig {
	private:
		int timeLimit;
		int realTimeLimit;
		int memoryLimit;
		int outputLimit;
		int stackLimit;
		String inputFileName;
		String outputFileName;
		String errorFileName;
		String resultFileName;
		String workPath;
		std::vector <String> extraReadableFiles;
		std::vector <String> extraWritableFiles;
		bool allowProc;
		bool safeMode;
		bool needShowTraceDetails;
		std::vector <String> argv;

		void initConfig() {
			timeLimit = realTimeLimit = memoryLimit = outputLimit = stackLimit = 0,
			inputFileName = outputFileName = errorFileName = resultFileName = "/dev/null",
			workPath = "", allowProc = needShowTraceDetails = false, safeMode = true;
		}
	public:
		RunConfig () {initConfig();}

		RunConfig (const String &res, const String &in, const String &out,
					const String &err, const RunLimit &limit, const std::vector <String> &arg) :
					stackLimit(0), inputFileName(in), outputFileName(out),
					errorFileName(err), resultFileName(res), argv(arg) {
			setLimit(limit);
		}

		SOJ_GETSET(timeLimit, TimeLimit);
		SOJ_GETSET(realTimeLimit, RealTimeLimit);
		SOJ_GETSET(memoryLimit, MemoryTimeLimit);
		SOJ_GETSET(outputLimit, OutputTimeLimit);
		SOJ_GETSET(stackLimit, StackLimit);

		RunLimit getLimit() const {
			return RunLimit(timeLimit, realTimeLimit, memoryLimit, outputLimit);
		}

		RunConfig & setLimit(const RunLimit &limit) {
			timeLimit = limit.time, realTimeLimit = limit.realtime;
			memoryLimit = limit.memory, outputLimit = limit.output;
		}

		SOJ_GETSET(inputFileName, InputFileName);
		SOJ_GETSET(outputFileName, OutputFileName);
		SOJ_GETSET(errorFileName, ErrorFileName);
		SOJ_GETSET(resultFileName, ResultFileName);
		SOJ_GETSET(workPath, WorkPath);

		SOJ_GETSET(extraReadableFiles, ExtraReadableFiles);
		SOJ_GETSET(extraWritableFiles, ExtraWritableFiles);

		SOJ_GETSET(allowProc, AllowProc);
		SOJ_GETSET(safeMode, SafeMode);
		SOJ_GETSET(needShowTraceDetails, NeedShowTraceDetails);
		SOJ_GETSET(argv, Argv);

		RunConfig & setNameWithArgv(const String &name, ...) {
			argv.clear();
			argv.emplace_back(name);
			va_list vl;
			va_start(vl, name);
			for (const char *arg = va_arg(vl, const char *); arg; arg = va_arg(vl, const char *)) {
				argv.emplace_back(arg);
			}
			va_end(vl);
		}

		String toString() const {
			String ret;
			ret = "--res=" + escapeShellArg(resultFileName);
			ret += " --in=" + escapeShellArg(inputFileName);
			ret += " --out=" + escapeShellArg(outputFileName);
			ret += " --err=" + escapeShellArg(errorFileName);
			ret += " --tl=" + std::to_string(timeLimit);
			ret += " --rtl=" + std::to_string(realTimeLimit);
			ret += " --ml=" + std::to_string(memoryLimit);
			ret += " --ol=" + std::to_string(outputLimit);
			if (stackLimit) ret += " --sl=" + std::to_string(stackLimit);
			ret += " --work-path=" + escapeShellArg(workPath);
			if (allowProc) ret += " --allow-proc";
			if (!safeMode) ret += " --unsafe";
			if (needShowTraceDetails) ret += " --show-trace-details";
			for (const String &fn : extraReadableFiles)
				ret += " --add-readable=" + escapeShellArg(fn);
			for (const String &fn : extraWritableFiles)
				ret += " --add-writable=" + escapeShellArg(fn);
			for (const String &arg : argv)
				ret += ' ' + escapeShellArg(arg);
			return ret;
		}
	};
	#undef SOJ_CURRENT_CLASS
}
#endif
