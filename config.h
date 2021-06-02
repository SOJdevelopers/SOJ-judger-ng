#ifndef _SOJ_JUDGER_CONFIG_H_
#define _SOJ_JUDGER_CONFIG_H_

#include "env.h"
#include <map>
#include <fstream>
#include <cstdlib>

namespace SOJ_JUDGER_NAMESPACE {
	class Config {
	private:
		std::map<String, String> config;

	public:
		friend std::ostream & operator << (std::ostream & out, Config & conf) {
			for (auto it = conf.config.begin(); it != conf.config.end(); ++it) {
				out << it->first << " = " << it->second << '\n';
				// replace '\n' to std::endl when it not works
			}
			return out;
		}

		void loadFromFile(const String & filename) {
			std::ifstream fin(filename.c_str());
			if (!fin) { return; }
			String key, val;
			while (fin >> key >> val) {
				config[key] = val;
			}
		}

		class Result {
		private:
			String key;
			std::map<String, String> * conf;
		public:
			Result() { key = ""; }
			Result(String k, std::map<String, String> * c) :
				key(k), conf(c) {}
			Result operator [] (String num) {
				return Result(key + "_" + num, conf);
			}
			Result operator [] (int num) {
				return this->operator[] (std::to_string(num));
			}

			String get(const String & val = "") {
				if (conf->count(key)) return (*conf)[key];
				return val;
			}
			int getInt(int val = 0) {
				return atoi(get(std::to_string(val)).c_str());
			}
			double getDouble(double val = 0.0) {
				return atof(get(std::to_string(val)).c_str());
			}

			Result & set(const String & val) {
				if (!conf->count(key)) {
					(*conf)[key] = val;
				}
				return *this;
			}
			Result & set(int val) {
				return this->set(std::to_string(val));
			}
			Result & set(double val) {
				return this->set(std::to_string(val));
			}
		} ;
		Result operator [] (const String & key) {
			return Result(key, &config);
		}
	} ;
}
#endif
