#ifndef _SOJ_JUDGER_DEF_HEADER_
#define _SOJ_JUDGER_DEF_HEADER_

#include "env.h"

namespace SOJ_JUDGER_NAMESPACE {
	struct PointInfo {
		int num, scr, usm;
		double ust;
		string info, in, out, res;

		PointInfo(int _num, int _scr, double _ust, int _usm,
				  const string &_info,
				  const string &_in, const string &_out, const string &_res) :
			num(_num), scr(_scr), ust(_ust), usm(_usm),
			info(_info), in(_in), out(_out), res(_res) {
				if (info == IS_DEFAULT) {
					if (scr == 0) {
						info = IS_WRONGANSWER;
					} else if (scr == 100) {
						info = IS_ACCEPTED;
					} else {
						info = IS_ACCEPTABLE;
					}
				}
			}
	};
}
#endif
