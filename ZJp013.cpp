#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Time {
	int hour, minute;
	Time(int h = 0, int m = 0) :
			hour(h), minute(m) {
	}
};
Time operator-(const Time& lhs, const Time& rhs) {
	int H_diff = lhs.hour - rhs.hour, M_diff = lhs.minute - rhs.minute, com =
			M_diff < 0;
	return Time(H_diff - com, M_diff + com * 60);
}
bool operator<(const Time& lhs, const Time& rhs) {
	return (lhs.hour < rhs.hour)
			|| (lhs.hour == rhs.hour && lhs.minute < rhs.minute);
}
bool operator<(const pair<Time, Time>& lhs, const pair<Time, Time>& rhs) {
	return lhs.first < rhs.first;
}
int main() {
	int NumOfTimeSegment = 0;
	Time endTime;
	vector<pair<Time, Time> > timeSegment;
	char unused;
	for (int count = 1; cin >> NumOfTimeSegment; count++) {
		timeSegment.clear();
		for (int i = 0; i < NumOfTimeSegment; i++) {
			Time tmpstartTime, tmpendTime;
			cin >> tmpstartTime.hour >> unused >> tmpstartTime.minute;
			cin >> tmpendTime.hour >> unused >> tmpendTime.minute;
			if (i)
				timeSegment.push_back(
						make_pair(tmpstartTime - endTime, endTime));
			endTime = tmpendTime;
			for (; cin && cin.get() != '\n';)
				;
		}
		timeSegment.push_back(make_pair(Time(18, 00) - endTime, endTime));
		pair<Time, Time> MaxSegment = *max_element(timeSegment.begin(),
				timeSegment.end());
		cout << "Day #" << count << ": the longest nap starts at "
				<< MaxSegment.second.hour << ':' << setw(2) << setfill('0')
				<< MaxSegment.second.minute << " and will last for ";
		MaxSegment.first.hour ?
				cout << MaxSegment.first.hour << " hours and " : cout << "";
		cout << MaxSegment.first.minute << " minutes.";
		if (cin)
			cout << endl;
	}
	return 0;
}
