#ifndef _SOJ_JUDGER_DEF_HEADER_
#define _SOJ_JUDGER_DEF_HEADER_

#include "env.h"

namespace SOJ_JUDGER_NAMESPACE {
	class RunResult {
	private:
		int ust, usm;
		int time;     // time limit (millisecond) (strict)
		int realtime; // time limit (millisecond)
		int memory;   // memory limit (KiB)
		int output;   // output limit (KiB)
	public:
		RunLimit() :
			time(0), realtime(0), memory(0), output(0) { }
		explicit RunLimit(int _t, int _m, int _o) :
			time(_t), realtime(0), memory(_m), output(_o) { }
		explicit RunLimit(int _t, int _rt, int _m, int _o) :
			time(_t), realtime(_rt), memory(_m), output(_o) { }
		RunLimit & setTime(int x) { time = x; return *this; }

		_SOJ_GETSET(time, Time)

#define _SOJ_GETSET(a, b) \
			decltype(a) get##b() { return a; } \
			_SOJ_CURRENT_CLASS & set##b(decltype(a) x) { a = x; return *this; }

		int getTime() { return time; }
		RunLimit & setRealtime(int x) { realtime = x; return *this; }
		int getRealtime() { return realtime; }
		RunLimit & setMemory(int x) { memory = x; return *this; }
		int getMemory() { return memory; }
		RunLimit & setOutput(int x) { output = x; return *this; }
		int getOutput() { return output; }
		const static RunLimit DEFAULT   ;
		const static RunLimit JUDGER    ;
		const static RunLimit CHECKER   ;
		const static RunLimit INTERACTOR;
		const static RunLimit VALIDATOR ;
		const static RunLimit MARKER    ;
		const static RunLimit COMPILER  ;
	} ;
	const RunLimit RunLimit::DEFAULT    = RunLimit(1000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::JUDGER     = RunLimit(600000, 1 << 20, 1 << 17);
	const RunLimit RunLimit::CHECKER    = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::INTERACTOR = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::VALIDATOR  = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::MARKER     = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::COMPILER   = RunLimit(15000, 1 << 19, 1 << 16);
}
#endif
