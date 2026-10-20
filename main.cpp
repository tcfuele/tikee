#include <fstream>
#include <iostream>
#include <chrono>
#include <string_view>

class TimeKeeper {
private:
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1>>;
	using fs = std::fstream;

	std::chrono::time_point<Clock> m_beg;
	const char* m_fileName;
	fs m_timeFile;
public:
	explicit TimeKeeper(const char* fileName = "logr_start_time.log") : m_fileName{fileName} {
		m_beg = Clock::now();
		m_timeFile.open(m_fileName, fs::in | fs::out | fs::binary);

		if (!m_timeFile) {
			std::cerr << "[logr] ERROR: No time logging file to write to!";
			std::exit(1);
		}
	};

	enum command {
		NO_COMMAND,
		START_TIMER,
		STOP_TIMER,
	};
};

void printTerminalUsageInfo(const char* binaryName) {
	std::cout << "Welcome to tikee! Usage:\n\n"
				 "  " << binaryName << " <command>\n\n"
				 "Available commands:\n\n"
				 "start    Start the timer\n"
				 "stop     Stops the timer\n"
				 "\ntype 'tikee --help' for more info!\n";
}

TimeKeeper::command getCmdInput(int argc, char* argv[]) {

	const char* binaryName { argv[0] };

	if (argc < 2) {
		printTerminalUsageInfo(binaryName);
		return TimeKeeper::NO_COMMAND;
	}

	for (int i = 1; i < argc; i++) {
		std::string_view argument = argv[i];

		if (argument == "-h" || 
			argument == "--help" ||
			argument == "help" ||
			argument == "-help") {

			printTerminalUsageInfo(binaryName);
			return TimeKeeper::NO_COMMAND;
		}
		else if (argument == "start") {
			std::cout << "starting\n";
			return TimeKeeper::START_TIMER;
		}
		else if (argument == "stop") {
			std::cout << "stopping\n";
			return TimeKeeper::STOP_TIMER;
		}

	}

	printTerminalUsageInfo(binaryName);
	return TimeKeeper::NO_COMMAND;
}

int main(int argc, char* argv[]) {

	TimeKeeper::command userCmd { getCmdInput(argc, argv) };

	if (userCmd == TimeKeeper::NO_COMMAND) {
		return 0;
	}

	/* TODO:
	 * if not started we start or error handle
	 * we want to create a file if we are tracking in some temp dir
	 * if file is present we are tracking, otherwise we through error
	 * if started and want to track we track or error handle
	 */

	/*
	auto const cacheTime = std::chrono::system_clock::now().time_since_epoch().count();
	writeTimeFile.write(reinterpret_cast<char const*>(&cacheTime), sizeof(cacheTime));
	writeTimeFile.close();

	std::ifstream readTimeFile{ "logr_temp.log", std::ios::binary };

	if (!readTimeFile) {
		std::cerr << "[logr] ERROR: No time logging file to write to!";
		return 1;
	}


	std::this_thread::sleep_for(std::chrono::seconds(120));

	std::chrono::system_clock::rep logFinishTime;
	if (!readTimeFile.read(reinterpret_cast<char*>(&logFinishTime), sizeof(logFinishTime))) {
		std::cerr << "[logr] ERROR: Can't read the log file!";
		return 1;
	}

	readTimeFile.close();

	std::chrono::system_clock::time_point const validFinishTime{ std::chrono::system_clock::duration{ logFinishTime } };
	std::time_t const writtenTime { std::chrono::system_clock::to_time_t(validFinishTime)};
	std::cout << std::ctime(&writtenTime) << '\n';
	*/


	return 0;
}
