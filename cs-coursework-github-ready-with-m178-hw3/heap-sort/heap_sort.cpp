#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <algorithm>
using namespace std;

// Creating our custom structure "stats"
// We also are keeping track of # of times we compare, and # of times we swap 2 values
struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
}; // Ending of stats structure

// Our print array function, we establish a vector, using const to hold the function from changing the array
void printArray(const vector<int>& a) {
    cout << "[";
    for (size_t i = 0; i < a.size(); ++i) { // Loop goes trhough every element in the vector
        cout << a[i]; // Prints out current number
        if (i + 1 < a.size()) cout << ", "; // Prints a comma after each number, save the last
    }
    cout << "]"; //last bracket and we end the loop
}

// Our heapify function, fixes part of the heap by makign sure the value at index i follows the max heap rule
// The max heap rule as context info is the rule that the parent value is greater than or equal to its child values
void heapify(vector<int>& a, int heapSize, int i, Stats& stats, bool trace) {
    int largest = i; //start off assuming current index i is the largest valeu
    int left = 2 * i + 1; // calculate the index of the left child
    int right = 2 * i + 2; // calculate the index of the right child

    if (left < heapSize) {
        stats.comparisons++;
        if (a[left] > a[largest]) largest = left;
    } // Checks if the left child exists, adds 1 to comparison counter
      // If the left is bigger than the current largest value, then the largest becomes the left childs index


    if (right < heapSize) {
        stats.comparisons++;
        if (a[right] > a[largest]) largest = right;
    }  // Doing the same type of check with the right child now
    

    if (largest != i) {
        swap(a[i], a[largest]);
        stats.swaps++;
        if (trace) {
            cout << "heapify: swap index " << i << " with index " << largest << " -> ";
            printArray(a);
            cout << '\n';
        }
        heapify(a, heapSize, largest, stats, trace);
    } // We check if one of the children was bigger than the parent, swap the parent with the larger child, and adds to swap counter
      // We print which indexes were swapped, and print the array after the swap
      // We call heapify again, recursion occurs, we fix the heap until the values are in the correct place  
}       

// buildMaxHeap creates the first max heap from an unsorted array.
// This phase is O(n).
void buildMaxHeap(vector<int>& a, Stats& stats, bool trace) {
    if (trace) cout << "Building max heap...\n";
    for (int i = static_cast<int>(a.size()) / 2 - 1; i >= 0; --i) {
        heapify(a, static_cast<int>(a.size()), i, stats, trace);
    } // We print a message to notify us "building max heap..."
      // We start from the last parent node, moving backwards toward the root, leaf nodes dont need heapifying they dont have children
}     // We call heapify on each parent node to build the max heap  

// Following section is the main heap sort function, it sorts the vector and returns the stats.
// We also implement a tracing function, to allow better analysis of sorting and debugging aid, its currently off for easier to read output
Stats heapSort(vector<int>& a, bool trace = false) {
    Stats stats;
    int n = static_cast<int>(a.size());
    // We create a stats object to count comparisons and swaps, and store the array size in n

    if (trace) {
        cout << "Original array: ";
        printArray(a);
        cout << "\n\nSTEP 1: Build max heap\n";
    } // Tracing code

    buildMaxHeap(a, stats, trace);
    // We build the first max heap from the unsorted array

    if (trace) {
        cout << "Max heap: ";
        printArray(a);
        cout << "\n\nSTEP 2: Move max to sorted partition, shrink heap, heapify\n";
    } // Tracing code

    // Repeatedly move the largest item to the sorted partition.
    // This phase is O(n log n).
    for (int end = n - 1; end > 0; --end) { // Loop moves from the end of array backward, each loop places the largest remaining value into its final sorted position
        swap(a[0], a[end]); // Swaps largest value at root index 0 with the last value in the unsorted part
        stats.swaps++; // Counts the swap
        if (trace) {
            cout << "move max to position " << end << " -> ";
            printArray(a);
            cout << "   sorted partition starts at index " << end << '\n';
        } // Tracing code
        heapify(a, end, 0, stats, trace); // Restores the max heap after removing the largest value, the heap size is end so the sorted part is ignored
    }

    if (trace) {
        cout << "\nSorted array: ";
        printArray(a);
        cout << "\n";
    } // More tracing code

    return stats; // We return the comparison and swap counts back to the caller
}


// Following is establishing our run test function to run test cases
void runTest(const string& name, vector<int> data, bool trace = false) { // test name, array, and tracing code turned off
    vector<int> original = data; // we save an original of the data b4 sorting

    auto start = chrono::high_resolution_clock::now(); // recording a start time
    Stats stats = heapSort(data, trace); // calling heap sort on test data, stores stats
    auto stop = chrono::high_resolution_clock::now(); // recording stop time
     
    auto microseconds = chrono::duration_cast<chrono::microseconds>(stop - start).count(); // calculating how long it took

    // Following code section is outputting the stats to our sort
    cout << left << setw(18) << name
        << " n=" << setw(5) << original.size()
        << " comparisons=" << setw(7) << stats.comparisons
        << " swaps=" << setw(7) << stats.swaps
        << " time=" << setw(7) << microseconds << " us"
        << " sorted=" << boolalpha << is_sorted(data.begin(), data.end()) << '\n'; // print whether final array is sorted as true or false
}


// Following code is our test case 
int main() {
    cout << "HEAP SORT DEMONSTRATION\n";
    cout << "Max heap rule: parent nodes are greater than or equal to child nodes.\n";
    cout << "Time complexity: Best/Average/Worst = O(n log n)\n";
    cout << "Build max heap = O(n), heapify = O(log n), extra space = O(1)\n\n";
    // Above is just some text for user ease of understanding

    vector<int> demo = { 9, 4, 7, 1, 3, 6, 2, 8, 5 }; // our original array
    heapSort(demo, true);

    cout << "\nDRIVER TESTS WITH DIFFERENT INPUTS\n";
    runTest("random", { 9, 4, 7, 1, 3, 6, 2, 8, 5 }); 
    runTest("already sorted", { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    runTest("reverse sorted", { 9, 8, 7, 6, 5, 4, 3, 2, 1 });
    runTest("duplicates", { 5, 1, 5, 3, 5, 2, 1, 4 });
    runTest("negative nums", { -3, 10, -1, 0, 7, -8, 2 });
    runTest("one value", { 42 });
    runTest("empty", {});
    // Above is different test scenarios w/ different array values

    vector<int> largeReverse;
    for (int i = 1000; i >= 1; --i) {
        largeReverse.push_back(i);
    }
    runTest("large reverse", largeReverse);
    // another test case w a loop starting at 1000, counting down to 1


    return 0;
}