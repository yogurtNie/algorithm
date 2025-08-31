//
// Created by 12472 on 25-5-19.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
/*车间有名称
车间每时刻最多执行一个任务，且原子地执行
任务有名称和执行时间
TF：选最早出现的任务执行（时间戳）
SF：选执行时间最短且字典序最大的任务执行（优先级队列）
LF：选执行时间最长且字典序最大的任务执行（优先级队列）
还需要一个bool数组标记任务是否执行

每个任务每次都有p的概率被分配到前k-1个区间，如果都没分配到，则必被分配到第k个区间
*/

static unsigned int seed = 1;

int myrand(void) {
    seed = seed * 1103515245 + 12345;
    return((unsigned int)(seed / 65536) % 100);
}


//结构体1：时间轴上的任务
struct taskInTime {
	int type;      		//0是指有新任务来，1是指有任务执行结束
	ll timestamp;		//时间戳，优先级队列按这个排序
	string taskName;	//任务名字

	//有新任务来
	ll exeTime;		//执行时间
	int workShopCnt;	//可以进入的车间数
	vector<string> ws;	//可以进入的车间名

	//有任务执行结束
	ll usedTimeStamp;	//曾经的时间戳
	string finishws;	//完成的车间

};



//堆顶是时间戳最小的任务
class TFcompare{
public:
	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
		return a.timestamp > b.timestamp;
	}
};

//堆顶是执行时间最短的任务，如果相同，则取字典序最大的
class SFcompare{
public:
	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
		if (a.exeTime == b.exeTime) return a.taskName < b.taskName;
		return a.exeTime > b.exeTime;
	}
};

//堆顶是执行时间最长的任务，如果相同，则取字典序最大的
class LFcompare{
public:
	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
		if (a.exeTime == b.exeTime) return a.taskName < b.taskName;
		return a.exeTime < b.exeTime;
	}
};

//结构体2：车间
struct workshop{
	string type;		//车间取未完成任务的类型：TF, SF, LF
	string name;		//车间名字

	bool IsExetask;		//是否有任务在执行
	string exetask;		//执行任务的名字

	workshop(string a, string b) {
		type = a; name = b;
		IsExetask = 0;
	}
	//待执行任务
	//如果是TF类型：取时间最早的任务
	priority_queue<taskInTime, vector<taskInTime>, TFcompare> TF_Q;

	//如果是SF类型：取执行时间最短的任务
	priority_queue<taskInTime, vector<taskInTime>, SFcompare> SF_Q;

	//如果是LF类型：取执行时间最长的任务
	priority_queue<taskInTime, vector<taskInTime>, LFcompare> LF_Q;

};

map<string, workshop*> mp;

//给任务分配车间
string assign(taskInTime& tk) {
	int len = tk.ws.size();
	if (len == 1) return tk.ws[0];
	//ll p = floor(100 / len);
	for (int i = 0; i < len - 1; i++) {
		ll p = floor(100 / (len - i));
		if (p > myrand()) return tk.ws[i];
	}
	return tk.ws[len - 1];
}

class TimeCompare{
public:
	bool operator()(const taskInTime& a, const taskInTime& b) {
		if (a.timestamp == b.timestamp) return a.type < b.type;
		return a.timestamp > b.timestamp;
	}
};

//时间轴
priority_queue<taskInTime, vector<taskInTime>, TimeCompare> timeLine;

struct finishTask{
	ll timestamp;
	ll finishTime;
	string taskName;
	string finishws;
};

class ansCompare{
public:
	bool operator()(const struct finishTask& a, const struct finishTask& b) {
		if (a.finishTime != b.finishTime) return a.finishTime > b.finishTime;
		return a.timestamp > b.timestamp;
	}
};
priority_queue<finishTask, vector<finishTask>, ansCompare> FT;

void check_and_schedule(workshop* w, ll current_time) {
	if (w->IsExetask) return; // 车间忙，无需处理

	taskInTime next;
	bool hasNext = false;
	if (w->type == "TF" && !w->TF_Q.empty()) {
		next = w->TF_Q.top(); w->TF_Q.pop();
		hasNext = true;
	} else if (w->type == "SF" && !w->SF_Q.empty()) {
		next = w->SF_Q.top(); w->SF_Q.pop();
		hasNext = true;
	} else if (w->type == "LF" && !w->LF_Q.empty()) {
		next = w->LF_Q.top(); w->LF_Q.pop();
		hasNext = true;
	}

	if (hasNext) {
		next.type = 1;
		next.timestamp = current_time + next.exeTime;
		next.usedTimeStamp = current_time;
		timeLine.push(next);
		w->IsExetask = true;
		w->exetask = next.taskName;
	}
}

//按时间轴执行
void exeFollowTime() {
	while (!timeLine.empty()) {
		taskInTime now = timeLine.top();
		timeLine.pop();

		//如果是新来的任务
		if (now.type == 0) {
			string wsName = assign(now);
			workshop* w = mp[wsName];
			now.finishws = wsName;
			// workshop* w = mp[now.finishws];

			//如果有正在执行的任务
			if (w->IsExetask) {
				if (w->type == "TF") {
					w->TF_Q.push(now);
				}
				else if (w->type == "SF") {
					w->SF_Q.push(now);
				}
				else {
					w->LF_Q.push(now);
				}
			}
			else {
				taskInTime next;
				next.type = 1;
				next.usedTimeStamp = now.timestamp;
				next.taskName = now.taskName;
				next.timestamp = now.timestamp + now.exeTime;
				next.finishws = now.finishws;
				timeLine.push(next);
				w->IsExetask = true;
				w->exetask = next.taskName;
			}
			check_and_schedule(w, now.timestamp);
		}

		//如果是执行完成任务
		else if (now.type == 1) {
			finishTask ans;
			ans.finishTime = now.timestamp;
			ans.taskName = now.taskName;
			ans.timestamp = now.usedTimeStamp;
			ans.finishws = now.finishws;
			FT.push(ans);		//加入答案集

			string wsName = now.finishws;
			workshop* w = mp[wsName];

			//从这个车间的待办任务中选下一个执行任务
			taskInTime next;
			bool hasNext = false;
			if (w->type == "TF") {
				if (!w->TF_Q.empty()) {
					next = w->TF_Q.top();
					w->TF_Q.pop();
					hasNext = true;
				}
			}
			else if (w->type == "SF") {
				if (!w->SF_Q.empty()) {
					next = w->SF_Q.top();
					w->SF_Q.pop();
					hasNext = true;
				}
			}
			else {
				if (!w->LF_Q.empty()) {
					next = w->LF_Q.top();
					w->LF_Q.pop();
					hasNext = true;
				}
			}
			//如果取到了新的任务，则继续有新的可完成任务
			if (hasNext) {
				next.type = 1;
				next.finishws = wsName;
				next.timestamp = now.timestamp + next.exeTime;
				next.usedTimeStamp = now.timestamp;
				timeLine.push(next);
				w->IsExetask = true;
				w->exetask = next.taskName;
			}
			else {
				w->IsExetask = false;
				w->exetask = "";
			}
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll n, m; cin >> n >> m;
	cin.ignore();
	//初始化车间
	for (int i = 0; i < n; i++) {
		string name, type;
		cin >> name >> type;
		mp[name] = new workshop(type, name);
	}
	cin.ignore();

	//初始化任务
	for (int i = 0; i < m; i++) {
		taskInTime temp;
		string str;
		getline(cin, str);
		istringstream ss(str);
		ss >> temp.timestamp >> temp.taskName >> temp.exeTime >> temp.workShopCnt;
		for (int j = 0; j < temp.workShopCnt; j++) {
			string t;
			ss >> t;
			temp.ws.push_back(t);
		}
		temp.type = 0;
		timeLine.push(temp);
	}
	exeFollowTime();
	while (!FT.empty()) {
		finishTask temp = FT.top(); FT.pop();
		cout << temp.finishTime << " " << temp.taskName << "\n";
	}

	//释放内存
	for (auto& ft : mp) {
		delete ft.second;
	}
	return 0;
}


