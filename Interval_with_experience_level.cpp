#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using interval = pair<pair<int,int>, int>;

vector<pair<int,int>> count_func(vector<interval> &intervals)
{
    sort(intervals.begin(), intervals.end(),
        [](interval &a, interval &b){
            return a.first.first < b.first.first;
        });
      
    //sort(intervals.begin(), intervals.end());
    vector<interval> merged;

    // start with first interval
    merged.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); i++)
    {
        auto [index1, index2] = merged.back();

        // overlaps
        if (intervals[i].first.first < index1.second)
        {   merged.pop_back();
            index1.second = max(index1.second, intervals[i].first.second);
            index2 = max(index2, intervals[i].second); 
            merged.push_back({{index1.first, index1.second},index2});
        }
        else
        {
            merged.push_back(intervals[i]);
        }
    }

    // count consecutive same-second values
    vector<pair<int,int>> count_exp;
    int count = 1;

    for (int i = 1; i < merged.size(); i++)
    {
        if (merged[i].second == merged[i-1].second)
        {
            count++;
        }
        else
        {
            count_exp.push_back({merged[i-1].second, count});
            count = 1;
        }
    }

    count_exp.push_back({merged.back().second, count});

    return count_exp;
}

int main()
{
    vector<interval> intervals_new = { {{1,3},1}, {{2,4},2}, {{5,6},1} };

    cout << "experience-count pairs:\n";
    auto result = count_func(intervals_new);

    for (auto &p : result)
    {
        cout  << p.first << "  " << p.second << endl;
    }
}
