#include <bits/stdc++.h>
using namespace std;

struct point {int x, y;} p1, p2, p3;

vector <point> v1, v2, v4, v5, v6;
vector <pair<int, int>> v3;

// XY座標排序，X比Y先排 
bool compare(point a, point b) {
	return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

// 向量OA外積向量OB，大於零表示從OA到OB為逆時針旋轉
int cross(point o, point a, point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 兩點距離平方
int length(point a, point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// 以o點為中心點，a點較遠，b點較近
bool far(point o, point a, point b) {
	return length(o, a) > length(o, b);
}

// 角度相同時，距離長度的判斷
bool compare_angle(point a, point b) {
	int c = cross(v1[0], a, b);
	return c > 0 || (c == 0 && length(v1[0], a) < length(v1[0], b));
}

// 包裹法
void gw() {
	int start = 0;
	for (int i = 0; i < v1.size(); i++)
		if (compare(v1[i], v1[start]))
			start = i;
	v2.push_back(v1[start]);	// 記錄起點
	int current = start;		// 當前的點
	while (1) {
		/* 尋找下一個要被包覆的點：
		   一、找出最外圍的一點
		   二、多點共線，則找最遠的一點 */ 
		int next = current;
		for (int i = 0; i < v1.size(); i++) {
			int c = cross(v2.back(), v1[i], v1[next]);
			if (c > 0 || c == 0 && far(v2.back(), v1[i], v1[next]))
				next = i;
		}
		if (next == start) break;	// 回到起點結束 
		v2.push_back(v1[next]);		// 記錄找到的點
		current = next;				// 前往下一個點
	}
}

// 葛立恆掃描法
void gs() {
	swap(v1[0], *min_element(v1.begin(), v1.end(), compare));	// 最低最左的點為起點
	sort(v1.begin() + 1, v1.end(), compare_angle);				// 其餘各點依角度排序
	for (int i = 0; i < v1.size(); i++) {
		if (i < 2) {
			v6.push_back(v1[i]); 
			continue;
		}
		while (v6.size() >= 2 && cross(v6[v6.size() - 2], v6[v6.size() - 1], v1[i]) <= 0) {
			v6.pop_back();
		}
		v6.push_back(v1[i]);
	}
}

// 安德魯演算法
void aa() {
	sort(v3.begin(), v3.end()); 				// 點的排序 
	for (int i = 0; i < v3.size(); i++) { 		// 包上半部
		point p1 {.x = v3[i].first, .y = v3[i].second};
		if (i < 2) {
			v4.push_back(p1);
			continue;
		}
		while (v4.size() >= 2) {
			point p2 {.x = v4[v4.size() - 1].x, .y = v4[v4.size() - 1].y};
			point p3 {.x = v4[v4.size() - 2].x, .y = v4[v4.size() - 2].y};
			if (cross(p2, p3, p1) > 0) break;
			v4.pop_back();
		}
		v4.push_back(p1);
	} 
	for (int i = v3.size() - 1; i >= 0 ; i--) { // 包下半部
		point p1 {.x = v3[i].first, .y = v3[i].second};
		if (i > v3.size() - 2) {
			v5.push_back(p1); 
			continue;
		}
		while (v5.size() >= 2) {
			point p2 {.x = v5[v5.size() - 1].x, .y = v5[v5.size() - 1].y};
			point p3 {.x = v5[v5.size() - 2].x, .y = v5[v5.size() - 2].y};
			if (cross(p2, p3, p1) > 0) break;
			v5.pop_back();
		}
		v5.push_back(p1);
	}
}

int main() {
	int n, x, y; 	// 輸入點座標 
	cout << "< 請輸入點的總數 >\n點的個數：";
	cin >> n;
	if (n == 0) cout << "\\\\無點可包//"; 
	cout << '\n';
	for (int i = 0; i < n; i++) {
		cout << "第 " << i + 1 << " 個座標：\n";
		cout << "  x = "; 
		cin >> x;
		cout << "  y = ";
		cin >> y;
		point p {.x = x, .y = y};
		v1.push_back(p);
		v3.push_back(make_pair(x, y));
	}
	
	gw(); 	// 包裹法
	gs(); 	// 葛立恆掃描法
	aa(); 	// 安德魯演算法
	
	cout << "\n< 執行結果 >\n";	 // 輸出執行結果 
	cout << "使用「包裹法」得到的凸包：\n";
	for (int i = 0; i < v2.size(); i++) {
		cout << "(" << v2[i].x << ", " << v2[i].y << ")";
		if (i < v2.size() - 1) cout << ",";
	}
	cout << "\n使用「葛立恆掃描法」得到的凸包：\n";
	for (int i = 0; i < v6.size(); i++) {
		cout << "(" << v6[i].x << ", " << v6[i].y << ")";
		if (i < v6.size() - 1) cout << ",";
	}
	cout << "\n使用「安德魯演算法」得到的凸包：\n";
	for (int i = 0; i < v4.size(); i++) {
		cout << "(" << v4[i].x << ", " << v4[i].y << ")";
		if (i < v4.size() - 1) cout << ",";
	}
	if (v5.size() > 2) cout << ",";
	for (int i = 1; i < v5.size() - 1; i++) {
		cout << "(" << v5[i].x << ", " << v5[i].y << ")";
		if (i < v5.size() - 2) cout << ",";
	}
}
