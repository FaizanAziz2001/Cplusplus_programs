#pragma once
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
using namespace std;

class Twitter
{
	struct wall
	{
		string name, time;
		string tweet;
		int likes;
		int retweets;
		int id;
	};

	class Node
	{
		int id;
		string name, password;
		unordered_map<int, Node*> followers;
		unordered_map<int, Node*> following;
		map<string, wall, greater<string>> mywall;
		map<string, wall, greater<string>> timeline;
		friend class Twitter;
	public:
		Node(int i = 0, string n = "", string p = " ")
		{
			id = i;
			name = n;
			password = p;
		}
	};

	vector<Node*> Users;
	int num_of_id;
	Node* current_user;

	Node* SearchUser(string name)
	{
		for (auto temp : Users)
		{
			if (name == temp->name)
				return temp;
		}
		return nullptr;
	}

	string getTime()
	{
		char str[26];
		time_t result = time(NULL);
		ctime_s(str, sizeof(str), &result);
		return str;
	}
public:
	Twitter()
	{
		num_of_id = 0;
		LoadUsers();
		LoadFollowers();
		LoadFollowing();
		Load_Postsfromfile();
		srand(time(NULL));
	}

	void PostonmyWall()
	{
		string text;
		cout << "Something on your Mind: ";
		cin.ignore();
		getline(cin, text);

		wall temp;


		string time = getTime();
		time.pop_back();

		temp.tweet = text;
		temp.likes = rand() % 100;
		temp.retweets = rand() % 200;
		temp.name = current_user->name;
		temp.time = time;
		temp.id = current_user->id;


		current_user->mywall.insert(pair<string, wall>(time, temp));
	}

	void Login()
	{
		string name, password;

		while (true)
		{
			cout << "Enter your name: ";
			cin >> name;

			auto user = SearchUser(name);
			if (!user)
			{
				cout << "NO SUCH USER EXIST" << endl << endl;
				system("pause");
				continue;
			}
			cout << "Enter your password: ";
			cin >> password;

			if (user->password == password)
			{
				current_user = user;
				cout << "Log in Successful" << endl;
				break;
			}
		}
	}

	void Follow()
	{

		Node* search;
		string name;
		int id;
		cout << "Enter name to search: ";
		cin >> name;

		for (auto temp : Users)
		{
			if (temp == current_user)
				continue;
			if (temp->name.find(name) != std::string::npos)
			{
				cout << temp->id << "\t" << temp->name << endl;
			}
		}

		cout << "Enter id: ";
		cin >> id;
		search = Users[id];

		if (current_user->following.find(search->id) == current_user->following.end())
		{
			search->followers.insert(pair<int, Node*>(current_user->id, current_user));
			current_user->following.insert(pair<int, Node*>(search->id, search));
		}
		else
		{
			cout << "User already followed" << endl;
		}
	}

	void Unfollow()
	{
		if (current_user->following.empty())
		{
			cout << "You are currently following no one" << endl;
			return;
		}

		PrintFollowing();
		int id;
		cout << "Enter user id to unfollow: ";
		cin >> id;

		auto search_itr = current_user->following.find(id);
		auto current_user_itr = search_itr->second->followers.find(current_user->id);

		search_itr->second->followers.erase(current_user_itr);
		current_user->following.erase(search_itr);

	}

	void FollowBack()
	{
		if (current_user->followers.empty())
		{
			cout << "You are currently have 0 followers" << endl;
			return;
		}
		PrintFollowers();
		int id;
		cout << "Enter the user id to follow back:";
		cin >> id;

		auto search = Users[id];

		if (current_user->following.find(search->id) == current_user->following.end())
		{
			search->followers.insert(pair<int, Node*>(current_user->id, current_user));
			current_user->following.insert(pair<int, Node*>(search->id, search));
		}
		else
		{

			cout << "User already followed" << endl;

		}
	}

	void CreateAccount(string name, string password)
	{
		Node* User = new Node(num_of_id, name, password);
		auto check = SearchUser(name);
		if (!check)
		{
			Users.push_back(User);
			num_of_id++;
		}
		else
			cout << "User already exists";

		current_user = User;
	}

	void RemoveAccount()
	{
		char input;
		cout << "Are you sure you want to delete your account (Y/N): ";
		cin >> input;


		if (input == 'y' || input == 'Y')
		{

			for (auto temp : current_user->followers)
			{
				auto current_itr = temp.second->following.find(current_user->id);
				temp.second->following.erase(current_itr);
			}

			for (auto temp : current_user->following)
			{
				auto current_itr = temp.second->followers.find(current_user->id);
				temp.second->followers.erase(current_itr);
			}

			swap(Users[current_user->id], Users[Users.size() - 1]);
			Users[current_user->id]->id = current_user->id;
			Users.pop_back();
		}
	}

	void LoadUsers()
	{
		ifstream fin("Users.txt");
		int id;
		string name, password;
		while (fin.good())
		{
			fin >> id >> name >> password;
			if (fin.eof())
				break;
			CreateAccount(name, password);
		}
	}

	void LoadFollowers()
	{
		ifstream fin("followers.txt");
		int id;
		int input;
		while (fin.good())
		{
			fin >> id >> input;
			if (fin.eof())
				break;
			if (input == -1)
			{
				while (true)
				{
					fin >> input;
					if (input == -1)
						break;
					Users[id]->followers.insert(pair<int, Node*>(input, Users[input]));
				}
			}
		}
	}

	void LoadFollowing()
	{
		ifstream fin("Following.txt");
		int id;
		int input;
		while (fin.good())
		{
			fin >> id;
			if (fin.eof())
				break;
			fin >> input;
			if (input == -1)
			{
				while (true)
				{
					fin >> input;
					if (input == -1)
						break;
					Users[id]->following.insert(pair<int, Node*>(input, Users[input]));
				}
			}
		}
	}

	void Load_Postsfromfile()
	{
		ifstream fin("Posts.txt");
		int id;
		string data;
		wall temp;
		char input;
		while (fin.good())
		{
			fin >> id;
			if (fin.eof())
				break;
			fin.get();
			input = fin.get();
			if (input == '{')
			{
				while (true)
				{
					while (true)
					{
						input = fin.get();
						if (input == ',')
							break;
						data.push_back(input);
					}

					temp.tweet = data;
					data.clear();
					while (true)
					{
						input = fin.get();
						if (input == ',')
							break;
						data.push_back(input);
					}

					temp.time = data;
					data.clear();
					while (true)
					{
						input = fin.get();
						if (input == ',')
							break;
						data.push_back(input);
					}

					temp.likes = std::stoi(data);
					data.clear();
					while (true)
					{
						input = fin.get();
						if (input == '}')
							break;
						data.push_back(input);
					}
					temp.retweets = std::stoi(data);
					temp.name = Users[id]->name;
					temp.id = id;

					Users[id]->mywall.insert(pair<string, wall>(temp.time, temp));
					data.clear();
					break;
				}
			}
		}
	}

	void LoadTimeLine()
	{
		for (auto temp : current_user->following)
		{
			auto itr = temp.second->mywall.begin();
			current_user->timeline.insert(pair<string, wall>((*itr).first, (*itr).second));
		}
	}

	void PrintUsers()
	{
		cout << "ID\tUsers" << endl;
		for (auto temp : Users)
		{
			cout << temp->id << "\t" << temp->name << endl;
		}
	}

	void PrintFollowing()
	{
		cout << "ID\tName" << endl;
		for (auto temp : current_user->following)
		{
			cout << temp.first << "\t " << temp.second->name << endl;
		}
	}

	void PrintFollowers()
	{
		cout << "ID\tName" << endl;
		for (auto temp : current_user->followers)
		{
			cout << temp.first << "\t" << temp.second->name << endl;
		}
	}

	void PrintMyWall()
	{
		for (auto temp : current_user->mywall)
		{
			cout << temp.second.name << " tweeted on " << temp.second.time << " : " << endl << temp.second.tweet;
			cout << endl << endl << "Likes: " << temp.second.likes << "\t Retweets: " << temp.second.retweets << endl << endl;
		}
	}

	void PrintMyTimeline()
	{
		for (auto temp : current_user->timeline)
		{
			cout << temp.second.name << " tweeted on " << temp.second.time << " : " << endl << temp.second.tweet;
			cout << endl << endl << "Likes: " << temp.second.likes << "\t Retweets: " << temp.second.retweets << endl << endl;
		}
	}

	void Menu()
	{
		cout << "1. Follow a user" << endl
			<< "2. Follow back a user" << endl
			<< "3. Print Followers" << endl
			<< "4. Print Following" << endl
			<< "5. Unfollow a user" << endl
			<< "6. Remove Account" << endl
			<< "7. Post on my wall" << endl
			<< "8. Print my wall" << endl
			<< "9. Print my feed" << endl
			<< "10. Logout" << endl;
	}

	bool Start()
	{
		int input;
		string name, password;
		cout << "1. Create Account" << endl
			<< "2. Log in" << endl
			<< "3. Exit" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			cout << "Enter your name: " << endl;
			cin >> name;
			cout << "Enter password: " << endl;
			cin >> password;
			CreateAccount(name, password);
			break;
		case 2:
			Login();
			break;
		case 3:
			return false;
		}
		return true;
	}

	void Run()
	{
		int input;
		while (true)
		{
			if (!Start())
			{
				break;
			}

			while (true)
			{
				Menu();
				cin >> input;
				cout << endl;
				switch (input)
				{
				case 1:
					Follow();
					break;
				case 2:
					FollowBack();
					break;
				case 3:
					PrintFollowers();
					break;
				case 4:
					PrintFollowing();
					break;
				case 5:
					Unfollow();
					break;
				case 6:
					RemoveAccount();
					goto end_loop;
					break;
				case 7:
					PostonmyWall();
					break;
				case 8:
					PrintMyWall();
					break;
				case 9:
					LoadTimeLine();
					PrintMyTimeline();
					break;
				case 10:
					goto end_loop;
				}
				cout << endl << endl;
			}
		end_loop:;
		}
	}
};
