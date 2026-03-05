#include <iostream>
#include <vector>

namespace constants {
	const int MAX_HOURS = 23;
	const int MAX_MINUTES = 59;
	const int MAX_SECONDS = 59;
	const int SECONDS_IN_ONE_MINUTE = 60;
	const int SECONDS_IN_ONE_HOUR = 60 * SECONDS_IN_ONE_MINUTE;
	const int SECONDS_IN_ONE_DAY = 24 * SECONDS_IN_ONE_HOUR;

	const int DINNER_MIN_HOUR = 20;
	const int DINNER_MIN_MINUTES = 30;
	const int DINNER_MAX_HOUR = 22;

	const int PARTY_MIN_HOUR = 23;
	const int PARTY_MAX_HOUR = 6;
}

class Time {
private:
	unsigned hours;
	unsigned minutes;
	unsigned seconds;

	unsigned getTimeInSeconds() const {
		return hours * constants::SECONDS_IN_ONE_HOUR + minutes * constants::SECONDS_IN_ONE_MINUTE + seconds;
	}

	Time secondsToTime(unsigned totalSeconds) const {
		Time time{};

		totalSeconds %= constants::SECONDS_IN_ONE_DAY;

		unsigned hours = totalSeconds / constants::SECONDS_IN_ONE_HOUR;
		time.setHours(hours);
		totalSeconds %= constants::SECONDS_IN_ONE_HOUR;

		unsigned minutes = totalSeconds / constants::SECONDS_IN_ONE_MINUTE;
		time.setMinutes(minutes);

		totalSeconds %= constants::SECONDS_IN_ONE_MINUTE;
		time.setSeconds(totalSeconds);

		return time;
	}

public:
	Time() : hours(0), minutes(0), seconds(0) {

	}

	Time(unsigned hours, unsigned minutes, unsigned seconds) : Time() {
		if (!setHours(hours) || !setMinutes(minutes) || !setSeconds(seconds)) {
			std::cout << "Invalid time!" << std::endl;
		}
	}

	unsigned getHours() const {
		return hours;
	}

	unsigned getMinutes() const {
		return minutes;
	}

	unsigned getSeconds() const {
		return seconds;
	}

	bool setHours(unsigned hours) {
		if (hours > constants::MAX_HOURS) {
			return false;
		}

		this->hours = hours;
		return true;
	}

	bool setMinutes(unsigned minutes) {
		if (minutes > constants::MAX_MINUTES) {
			return false;
		}

		this->minutes = minutes;
		return true;
	}

	bool setSeconds(unsigned seconds) {
		if (seconds > constants::MAX_SECONDS) {
			return false;
		}

		this->seconds = seconds;
		return true;
	}

	Time timeToMidnight() const {
		unsigned timeInSeconds = getTimeInSeconds();

		unsigned secondsToMidnight = constants::SECONDS_IN_ONE_DAY - timeInSeconds;

		return secondsToTime(secondsToMidnight);
	}

	void addSecond() {
		unsigned totalSeconds = getTimeInSeconds();
		totalSeconds = (totalSeconds + 1) % constants::SECONDS_IN_ONE_DAY;
		*this = secondsToTime(totalSeconds);
	}

	bool isDinnerTime() const {
		unsigned timeInSeconds = getTimeInSeconds();
		unsigned dinnerMinSeconds = constants::SECONDS_IN_ONE_HOUR * constants::DINNER_MIN_HOUR + constants::SECONDS_IN_ONE_MINUTE * constants::DINNER_MIN_MINUTES;
		unsigned dinnerMaxSeconds = constants::SECONDS_IN_ONE_HOUR * constants::DINNER_MAX_HOUR;

		return timeInSeconds >= dinnerMinSeconds && timeInSeconds <= dinnerMaxSeconds;
	}

	bool isPartyTime() const {
		unsigned timeInSeconds = getTimeInSeconds();
		unsigned partyMinSeconds = constants::SECONDS_IN_ONE_HOUR * constants::PARTY_MIN_HOUR;
		unsigned partyMaxSeconds = constants::SECONDS_IN_ONE_HOUR * constants::PARTY_MAX_HOUR;

		return timeInSeconds >= partyMinSeconds || timeInSeconds <= partyMaxSeconds;
	}

	Time getTimeDiff(const Time& other) const {
		unsigned currTotalSeconds = getTimeInSeconds();
		unsigned otherTotalSeconds = other.getTimeInSeconds();
		unsigned diff = currTotalSeconds >= otherTotalSeconds ? currTotalSeconds - otherTotalSeconds : otherTotalSeconds - currTotalSeconds;

		return secondsToTime(diff);
	}

	int compare(const Time& other) const {
		unsigned currTotalSeconds = getTimeInSeconds();
		unsigned otherTotalSeconds = other.getTimeInSeconds();

		if (currTotalSeconds > otherTotalSeconds)
			return 1;
		else if (currTotalSeconds == otherTotalSeconds)
			return 0;
		else
			return -1;
	}

	void printTime() const {
		std::cout << (hours < 10 ? "0" : "") << hours << ":"
			<< (minutes < 10 ? "0" : "") << minutes << ":"
			<< (seconds < 10 ? "0" : "") << seconds << std::endl;
	}
};

void sortTimes(std::vector<Time>& times, bool (*predicate)(const Time&, const Time&)) {
	for (size_t i = 0; i < times.size() - 1; i++) {
		size_t minIndex = i;

		for (size_t j = i + 1; j < times.size(); j++) {
			if (predicate(times[j], times[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			Time temp = times[i];
			times[i] = times[minIndex];
			times[minIndex] = temp;
		}
	}
}

int main() {
	Time t1(23, 59, 59);
	Time t2(4, 5, 6);
	Time t3(26, 15, 2);
	t3.printTime();
	Time timeToMidnight = t1.timeToMidnight();
	timeToMidnight.printTime();
	t1.printTime();
	t1.addSecond();
	t1.printTime();
	t1.addSecond();
	t1.printTime();
	std::cout << t1.isDinnerTime() << std::endl;
	std::cout << t1.isPartyTime() << std::endl;
	Time t4 = t1.getTimeDiff(t2);
	t4.printTime();

	std::vector<Time> times = {
		{23, 4, 15},
		{0, 0, 3},
		{5, 7, 57},
		{1, 59, 59},
		{1, 59, 58},
		{23, 59, 59},
		{0, 0, 0},
		{20, 15, 0},
		{12, 1, 1},
		{0, 58, 0}
	};

	sortTimes(times, [](const Time& t1, const Time& t2) { return t1.compare(t2) < 0; });

	for (const auto& time : times) {
		time.printTime();
	}
}