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


//结构体1：任务结构体，存储任务信息
struct taskInTime {
	int id;      		//唯一标识任务
	ll timestamp;		//时间戳，任务到达时间
	string taskName;	//任务名字
	ll exeTime;		//执行时间
	int workShopCnt;	//可以进入的车间数
	vector<string> ws;	//可以进入的车间名

	//有任务执行结束
	ll startTime;		// 开始执行的时间
	string finishws;	// 完成的车间
	ll finishTime;		// 执行结束的时间

};

// 结构体2：还未处理的任务
struct Unfinishedtask
{
	int taskID;			// 任务ID
	ll exeTime;
	string taskName;
	ll arrivalTime;		// 到达顺序

	Unfinishedtask(int id, ll time, string name, ll atime) : taskID(id), exeTime(time), taskName(name), arrivalTime(atime) {}

	//堆顶是执行时间最短的任务，如果相同，则取字典序最大的
	struct SFcompare
	{
		bool operator()(const Unfinishedtask& a, const Unfinishedtask& b) const
		{
			if (a.exeTime == b.exeTime) return a.taskName > b.taskName;
			return a.exeTime < b.exeTime;
		}
	};

	//堆顶是执行时间最长的任务，如果相同，则取字典序最大的
	struct LFcompare
	{
		bool operator()(const Unfinishedtask& a, const Unfinishedtask& b) const
		{
			if (a.exeTime == b.exeTime) return a.taskName > b.taskName;
			return a.exeTime > b.exeTime;
		}
	};
};



// //堆顶是时间戳最小的任务
// class TFcompare{
// public:
// 	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
// 		return a.timestamp > b.timestamp;
// 	}
// };

// //堆顶是执行时间最短的任务，如果相同，则取字典序最大的
// class SFcompare{
// public:
// 	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
// 		if (a.exeTime == b.exeTime) return a.taskName < b.taskName;
// 		return a.exeTime > b.exeTime;
// 	}
// };
//
// //堆顶是执行时间最长的任务，如果相同，则取字典序最大的
// class LFcompare{
// public:
// 	bool operator()(const struct taskInTime& a, const struct taskInTime& b) {
// 		if (a.exeTime == b.exeTime) return a.taskName < b.taskName;
// 		return a.exeTime < b.exeTime;
// 	}
// };

//结构体2：车间
struct workshop{
	string type;		//车间取未完成任务的类型：TF, SF, LF
	string name;		//车间名字

	bool IsExetask;		//是否有任务在执行
	int exetask;		//执行任务的序号
	ll availTime;		// 车间合法时间


	workshop(string a, string b) {
		type = a; name = b;
		IsExetask = 0;
		exetask = -1;
	}
	//待执行任务
	//如果是TF类型：取时间最早的任务，用队列存储即可
	queue<int> TF_Q;

	//如果是SF类型：取执行时间最短的任务，用set集合，顺便去重
	set<Unfinishedtask, Unfinishedtask::SFcompare> SF_Q;

	//如果是LF类型：取执行时间最长的任务
	set<Unfinishedtask, Unfinishedtask::LFcompare> LF_Q;

	//检查车间是否空闲
	bool IsEmpty()
	{
		return exetask == -1;
	}

	// 检查车间有没有待处理任务
	bool hasUnfinishedTask()
	{
		if (type == "TF") return !(TF_Q.empty());
		if (type == "LF") return !(LF_Q.empty());
		if (type == "SF") return !(SF_Q.empty());
		return false;
	}

	// 车间下一个待处理任务
	int peek()
	{
		if (!hasUnfinishedTask()) return -1;
		if (type == "TF") return TF_Q.front();
		if (type == "LF") return LF_Q.begin()->taskID;
		if (type == "SF") return SF_Q.begin()->taskID;
		return -1;
	}

	void pop()
	{
		if (!hasUnfinishedTask()) return;
		if (type == "TF") TF_Q.pop();
		else if (type == "LF") LF_Q.erase(LF_Q.begin());
		else if (type == "SF") SF_Q.erase(SF_Q.begin());
	}

	void push(int id, const taskInTime& t)
	{
		if (type == "TF") TF_Q.push(id);
		else
		{
			Unfinishedtask tmp(id, t.exeTime, t.taskName, (ll)id);
			if (type == "SF") SF_Q.insert(tmp);
			else if (type == "LF") LF_Q.insert(tmp);
		}
	}

};

map<string, workshop*> mp;
vector<taskInTime> vt;

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

// 结构体3：任务处理
struct event
{
	int type;				// 0到达，1完成
	ll timestamp;			// 对应的时间戳
	int taskID;				// 关联任务
	string wsName;			// 关联车间
};

class TimeCompare{
public:
	bool operator()(const event& a, const event& b) {
		if (a.timestamp == b.timestamp) return a.type < b.type;
		return a.timestamp > b.timestamp;
	}
};

//时间轴
priority_queue<event, vector<event>, TimeCompare> timeLine;

struct finishTask{
	ll timestamp;
	ll finishTime;
	string taskName;
};

class ansCompare{
public:
	bool operator()(const struct finishTask& a, const struct finishTask& b) {
		if (a.finishTime != b.finishTime) return a.finishTime > b.finishTime;
		return a.timestamp > b.timestamp;
	}
};
priority_queue<finishTask, vector<finishTask>, ansCompare> FT;


void execWS(string& wsName, ll curTime)
{
	workshop* ws = mp[wsName];

	// 当车间空闲的时候
	if (ws->IsEmpty() && ws->hasUnfinishedTask())
	{
		int id = ws->peek(); ws->pop();

		taskInTime& now = vt[id];
		ws->exetask = id;
		ws->availTime = curTime + now.exeTime;
		now.startTime = curTime;

		timeLine.push({1, ws->availTime, id, now.finishws});

	}
}


int main()
{
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string name, type; cin >> name >> type;
		mp[name] = new workshop(type, name);
	}
	cin.ignore();

	// 初始化任务
	for (int i = 0; i < m; i++)
	{
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
		temp.id = i;
		vt.push_back(temp);

		timeLine.push({0, temp.timestamp, i, ""});
	}

	while (!timeLine.empty())
	{
		event now = timeLine.top(); timeLine.pop();

		if (now.type == 0)
		{
			int NowId = now.taskID;
			taskInTime& nowTask = vt[NowId];

			// 开始分配车间
			string wn = "";
			int p = nowTask.workShopCnt;
			for (int j = 0; j < p; j++ )
			{
				string tmp = nowTask.ws[j];
				ll pp = 100 / p;

				if (j == p - 1 || pp > myrand())
				{
					wn = tmp; break;
				}
			}
			nowTask.finishws = wn;

			// 将任务添加到待处理的队列中
			workshop* autows = mp[wn];
			autows->push(nowTask.id, nowTask);

			execWS(wn, now.timestamp);
		}
		else
		{
			string ws_name = now.wsName;
			workshop* ws = mp[ws_name];
			int fid = ws->exetask;
			if (fid != -1) vt[now.taskID].finishTime = now.timestamp;


			ws->exetask = -1;

			execWS(ws_name, now.timestamp);
		}
	}

	for (auto& task : vt)
	{
		if (task.finishTime != -1)
		{
			FT.push({task.timestamp, task.finishTime, task.taskName});
		}
	}

	while (!FT.empty())
	{
		finishTask temp = FT.top(); FT.pop();
		cout << temp.finishTime << " " << temp.taskName << "\n";
	}
	return 0;
}