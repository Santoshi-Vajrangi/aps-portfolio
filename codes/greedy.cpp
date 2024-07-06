#include <iostream>
#include <vector>
#include <algorithm>

// A structure to represent an activity
struct Activity {
    int start;
    int end;
};

// Function to sort activities based on their end times
bool activityCompare(Activity a, Activity b) {
    return a.end < b.end;
}

// Function to find the maximum number of activities that don't overlap
void selectActivities(std::vector<Activity>& activities) {
    // Sort the activities based on their end times
    std::sort(activities.begin(), activities.end(), activityCompare);

    std::cout << "Selected activities are: \n";

    // The first activity always gets selected
    int i = 0;
    std::cout << "(" << activities[i].start << ", " << activities[i].end << ")";

    // Consider rest of the activities
    for (int j = 1; j < activities.size(); j++) {
        // If this activity has start time greater than or equal to the finish time of previously selected activity, then select it
        if (activities[j].start >= activities[i].end) {
            std::cout << ", (" << activities[j].start << ", " << activities[j].end << ")";
            i = j;
        }
    }
    std::cout << std::endl;
}

int main() {
    // Define a list of activities with their start and end times
    std::vector<Activity> activities = {
        {5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}
    };

    // Call the function to select activities
    selectActivities(activities);

    return 0;
}
