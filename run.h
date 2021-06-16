#ifndef _SOJ_JUDGER_RUN_HEADER_
#define _SOJ_JUDGER_RUN_HEADER_

#include "env.h"
#include "result.h"
#include "limit.h"
#include <cstdarg>
#include <vector>

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
	public:
		RunConfig () { RunConfig(RunLimit::DEFAULT); }

		RunConfig (const RunLimit &limit) { RunConfig("/dev/null", "/dev/null", "/dev/null", "/dev/null", limit, {}); }

		RunConfig (const String &res, const String &in, const String &out,
					const String &err, const RunLimit &limit, const std::vector <String> &arg) :
					stackLimit(0), inputFileName(in), outputFileName(out),
					errorFileName(err), resultFileName(res), argv(arg),
					allowProc(false), safeMode(true), needShowTraceDetails(false) {
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
			timeLimit = limit.getTime(), realTimeLimit = limit.getRealtime(),
			memoryLimit = limit.getMemory(), outputLimit = limit.getOutput();
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

		RunConfig & addReadable(const String &name) {return extraReadableFiles.emplace_back(name), *this;}
		RunConfig & addWritable(const String &name) {return extraWritableFiles.emplace_back(name), *this;}

		RunConfig & setNameWithArgv(const String &name, ...) {
			argv.clear();
			argv.emplace_back(name);
			va_list vl;
			va_start(vl, name);
			for (const char *arg = va_arg(vl, const char *); arg; arg = va_arg(vl, const char *)) {
				argv.emplace_back(arg);
			}
			va_end(vl);
			return *this;
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

		void run(RunResult &result) const {
			String cmd = <run_program_path> + ' ' + toString();
			if (execute(cmd)) {
				result.failedResult();
			} else {
				result.loadFromFile(resultFileName);
			}
		}
	};
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunWithInfoConfig
	class RunWithInfoConfig : public RunConfig {
	private:
	public:
		RunWithInfoConfig () { RunWithInfoConfig(RunLimit::DEFAULT); }

		RunWithInfoConfig (const RunLimit &limit) { RunConfig(limit); }

		void run(RunResult &result) {
			setErrorFileName(<name0>);
			RunConfig.run(result);
			result.loadFromFile(<name0>);
		}
	}
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunCheckerConfig
	class RunCheckerConfig : public RunWithInfoConfig {
	private:
	public:
		RunCheckerConfig () { RunCheckerConfig(RunLimit::CHECKER); }

		RunCheckerConfig (const RunLimit &limit) { RunWithInfoConfig(limit); }

		RunCheckerConfig & setupTestlib(String input, String output, String answer) {
			addReadable(input).addReadable(output).addReadable(answer);
			setArgv({input, output, answer});
			return *this;
		}

		void run(RunCheckerResult &result) { RunWithInfoConfig.run(result); }
	}
}
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunValidatorConfig
	class RunValidatorConfig : public RunWithInfoConfig {
	private:
	public:
		RunValidatorConfig () { RunValidatorConfig(RunLimit::VALIDATOR); }

		RunValidatorConfig (const RunLimit &limit) { RunWithInfoConfig(limit); }

		RunValidatorConfig & setupTestlib(String input) {
			setInputFileName(input);
			return *this;
		}

		void run(RunValidatorResult &result) { RunWithInfoConfig.run(result); }
	}
}
#undef SOJ_CURRENT_CLASS

	class RunCompilerConfig : public RunWithInfoConfig {
	private:
	
	public:
		RunCompilerConfig () { RunCompilerConfig(RunLimit::COMPILER); }

		RunCompilerConfig (const RunLimit &limit) { RunWithInfoConfig(limit); }

		void run(RunCompilerResult &result) { RunWithInfoConfig.run(result); }
	}
#endif
