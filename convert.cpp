#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>
#include "MyPriorityQueue.hpp"
#include <unordered_map>
#include <stack>
#include <iostream>


class Node {
	
	public:
	std::string s;
	int lcd;
	int diff;
	int sum;
	Node(std::string str, int lewis, int dif) {
		s = str;
		lcd = lewis;
		diff = dif;
		sum = lcd + diff;
	}
	bool operator<(const Node& r_node) const {
        if (sum == r_node.sum){
            return lcd < r_node.lcd;
        } else {
			return sum < r_node.sum;
		}
    }

    bool operator == (const Node& r_node) const {
        if (s == r_node.s) {
			return true;
		} else {
			return false;
		}
    }
};

void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


int diff_letters(std::string s1, std::string s2) {
	int res = 0;
	for (int i = 0; i < s1.size() && i < s2.size(); i++) {
		if (s1[i] != s2[i]) {
			res += 1;
		}
	}
	return res;
}


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
	std::vector< std::string > res;
	res.push_back(s1);
	if (s1 == s2) {
		return res;
	}
	res.pop_back();

	MyPriorityQueue<Node> queue;
	std::unordered_map<std::string, std::string> map_history;
	Node frist = Node(s1, 0, diff_letters(s1,s2));

	queue.insert(frist);
	map_history[s1] = "end";

	while (queue.isEmpty() != true && map_history.size() < words.size()) {
		std::string current = queue.min().s;
		queue.extractMin();

		for (int i = 0; i < current.size(); i++) {
            for (char letter = 'a'; letter <= 'z'; letter++) {
				std::string new_word = current;
                new_word[i] = letter;
				if (new_word == current) {
					continue;
				} else if (words.count(new_word) == true && !map_history.count(new_word)) {
					if (new_word == s2) {
						map_history[new_word] = current;
						break;
					} else {
						std::string copy = new_word;
						int depth = 0;
						map_history[new_word] = current;

						while (copy != "end") {
							depth += 1;
							copy = map_history[copy];
						}
						Node new_node = Node(new_word, depth, diff_letters(new_word, s2));
						queue.insert(new_node);
					}
				}
			}
		}
	}
	// for(int i = 0; i < res.size(); i ++){
	// 	std::cout<< "debugging:" << res[i] <<std::endl;
	// }

	std::stack<std::string> final_words;
	std::string temp = s2;
	while (temp != s1) {
		final_words.push(temp);
		temp = map_history[temp];
	}
	final_words.push(s1);
    
	while (final_words.empty() != true) {
		res.push_back(final_words.top());
		final_words.pop();
	}

	return res; 
}
