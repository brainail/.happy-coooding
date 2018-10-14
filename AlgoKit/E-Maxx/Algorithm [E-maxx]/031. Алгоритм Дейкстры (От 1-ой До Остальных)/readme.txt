
const int INF = 1000000000;

int main() {
	int n;
	vector < vector < pair<int,int> > > g (n);
	int s = ...; 

	vector<int> d (n, INF),  p (n);
	d[s] = 0;
	set < pair<int,int> > q;
	q.insert (make_pair (d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase (q.begin());

		for (size_t j=0; j<g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				q.erase (make_pair (d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert (make_pair (d[to], to));
			}
		}
	}
}


const int INF = 1000000000;

int main() {
	int n;
	vector < vector < pair<int,int> > > g (n);
	int s = ...; 

	vector<int> d (n, INF),  p (n);
	d[s] = 0;
	priority_queue < pair<int,int> > q;
	q.push (make_pair (0, s));
	while (!q.empty()) {
		int v = q.top().second,  cur_d = -q.top().first;
		q.pop();
		if (cur_d > d[v])  continue;

		for (size_t j=0; j<g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push (make_pair (-d[to], to));
			}
		}
	}
}

��� �ࠢ���, �� �ࠪ⨪� ����� � \rm priority\_queue ����뢠���� ��᪮�쪮 ����॥ ���ᨨ � \rm set.

���������� �� pair

����� ��� ������� ������ �ந�����⥫쭮���, �᫨ � ���⥩���� ��� �� �࠭��� �� ����, � ⮫쪮 ����� ���設. �� �⮬, ����⭮, ���� ��ॣ�㧨�� ������ �ࠢ����� ��� ���設: �ࠢ������ ��� ���設� ���� �� ����ﭨ� �� ��� d[].

��᪮��� � १���� ५���樨 ����稭� ����ﭨ� �� �����-� ���設� �������, � ���� ��������, �� "ᠬ� �� ᥡ�" ������� ������ �� �����ந���. ���⮬�, ��� ����� ����������, �� 㤠����/��������� ������ � ���⥩��� � ����� ५���樨 �� ����, �� �ਢ���� � ࠧ��襭�� �������� ������. ��-�०���� ��। ५���樥� ���� 㤠���� �� �������� ������ ���設� \rm to, � ��᫥ ५���樨 ��⠢��� �� ���⭮ - ⮣�� ������� ᮮ⭮襭�� ����� ����⠬� �������� ������ �� ��������.

� ��᪮��� 㤠���� ������ ����� �� \rm set, �� ����� �� \rm priority\_queue, � ����砥���, �� ��� ��� �ਬ���� ⮫쪮 � \rm set. �� �ࠪ⨪� �� ����⭮ 㢥��稢��� �ந�����⥫쭮���, �ᮡ���� ����� ��� �࠭���� ����ﭨ� �ᯮ������� ����訥 ⨯� ������ (��� \rm long\ long ��� \rm double).