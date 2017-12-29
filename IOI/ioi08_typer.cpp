#include <bits/stdc++.h>

using namespace std;

struct node
{
	bool fim;

	node *letra[30];

	string word;

	int maior;

	node()
	{
		for(int i = 0; i < 30; i++) letra[i] = NULL;

		fim = false;

		word = "";

		maior = 0;
	}
};

node *Trie = new node();

void Insert(node *root, string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(!root->letra[s[i] - 'a']) root->letra[s[i] - 'a'] = new node();

		root = root->letra[s[i] - 'a'];
	}

	root->fim = true;

	root->word = s;
}

queue<string> ans;

int get_max(node *&root)
{
	if(!root) return 0;

	int best = 0;

	if(root->fim) best = root->word.size();

	for(int i = 0; i < 30; i++)
	{
		best = max(best, get_max(root->letra[i]));
	}

	return root->maior = best;
}

void dfs(node *root, int deep)
{
	if(!root) return;

	if(root->fim) ans.push(root->word);

	vector< pair<int, int> > grafo;

	for(int i = 0; i < 30; i++)
	{
		if(root->letra[i]) grafo.push_back(make_pair(root->letra[i]->maior, i));
	}

	sort(grafo.begin(), grafo.end());

	for(int i = 0; i < grafo.size(); i++)
	{
		int id = grafo[i].second;

		dfs(root->letra[id], deep + 1);
	}
}

string save;

vector<char> resp;

void Print(string s)
{
	int equal = 0, id = 0;

	for(id = 0; id < s.size() && id < save.size() && s[id] == save[id]; id ++) equal ++;

	for(int i = 0; i < save.size() - equal; i++) resp.push_back('-');

	for(int i = id; i < s.size(); i++) resp.push_back(s[i]);

	resp.push_back('P');

	save = s;
}

int n;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++)
	{
		string s;

		cin>>s;

		Insert(Trie, s);
	}

	get_max(Trie);

	dfs(Trie, 0);

	while(!ans.empty())
	{
		Print(ans.front());

		ans.pop();
	}

	cout<<resp.size()<<'\n';

	for(int i = 0; i < resp.size(); i++) cout<<resp[i]<<"\n";
}	