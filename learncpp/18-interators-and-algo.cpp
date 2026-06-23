#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!! NOT NEEDED MUCH !!!!!!!!!!

{   // <----------- 18.1 ------------>
    // Selection Sort :-
	int array[]{ 30, 50, 20, 10, 40 };
	constexpr int length{ static_cast<int>(std::size(array)) };

	// Step through each element of the array
	for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex){
		// smallestIndex is the index of the smallest element we’ve encountered this iteration
		int smallestIndex{ startIndex };
		for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex) {
			if (array[currentIndex] < array[smallestIndex])
				smallestIndex = currentIndex;
		}
        // swap our start element with our smallest element (this sorts it into the correct place)
		std::swap(array[startIndex], array[smallestIndex]);
	}
    
    // std::sort :-
    #include <algorithm> // for std::sort
	std::sort(std::begin(array), std::end(array));

    // Bubble Sort :-
    for (int iteration{ 0 }; iteration < length-1; ++iteration) {
        int endOfArrayIndex{ length - iteration };
        bool swapped{ false }; // Keep track of whether any elements were swapped this iteration
        // Search through all elements up to the end of the array - 1
        for (int currentIndex{ 0 }; currentIndex < endOfArrayIndex - 1; ++currentIndex) {
            // If the current element is larger than the element after it
            if (array[currentIndex] > array[currentIndex + 1]) {
                std::swap(array[currentIndex], array[currentIndex + 1]); // Swap them
                swapped = true;
            }
        }
        // If we haven't swapped any elements this iteration, we're done early
        if (!swapped) {
            // iteration is 0 based, but counting iterations is 1-based.  So add 1 here to adjust.
            std::cout << "Early termination on iteration: " << iteration+1 << '\n';
            break;
        }
    }
}
{   // <----------- 18.2 ------------>
    std::array arr{ 0, 1, 2, 3, 4, 5, 6 };
    auto begin{ &arr[0] };
    auto end{ begin + std::size(arr) }; // note that this points to one spot beyond the last element
    // for-loop with pointer
    for (auto ptr{ begin }; ptr != end; ++ptr) { // ++ to move to next element
        std::cout << *ptr << ' '; // Indirection to get value of current element
    }

    // Ask our array for the begin and end points (via the begin and end member functions).
    auto begin{ array.begin() };
    auto end{ array.end() };
    // Use std::begin and std::end to get the begin and end points.
    auto begin{ std::begin(array) };
    auto end{ std::end(array) };

	std::vector v{ 1, 2, 3, 4, 5, 6, 7 };
	auto it{ v.begin() };
	++it; // move to second element
	std::cout << *it << '\n';
	it = v.erase(it); // erase the element currently being iterated over, set `it` to next element
	std::cout << *it << '\n'; // now ok, prints 3
}
{   // <----------- 18.3 ------------>
    std::array arr{ 13, 90, 99, 5, 40, 80 };
    int search {}; std::cin >> search;
    // std::find returns an iterator pointing to the found element (or the end of the container)
    // we'll store it in a variable, using type inference to deduce the type of the iterator (since we don't care)
    auto found{ std::find(arr.begin(), arr.end(), search) };
    // Algorithms that don't find what they were looking for return the end iterator.
    // We can access it by using the end() member function.
    if (found == arr.end()){ std::cout << "Could not find " << search << '\n'; }

    // Our function will return true if the element matches
    bool containsNut(std::string_view str){
        // std::string_view::find returns std::string_view::npos if it doesn't find the substring. 
        // Otherwise it returns the index where the substring occurs in str.
        return str.find("nut") != std::string_view::npos;
    }
    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon", "peanut"};
    // Scan our array to see if any elements contain the "nut" substring
    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };
    if (found == arr.end()) std::cout << "No nuts\n";
    else std::cout << "Found " << *found << '\n';   // prints first occ of "nut"
	auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };
	std::cout << "Counted " << nuts << " nut(s)\n";     // prints - 2 nut(s)

    bool greater(int a, int b)
    { return (a > b); }// Order @a before @b if @a is greater than @b.
    // Pass greater to std::sort
    std::sort(arr.begin(), arr.end(), greater);

    // sort accepts a comparison function
    void sort(int* begin, int* end, std::function<bool(int, int)> compare){
        for (auto startElement{ begin }; startElement != end-1; ++startElement) {
            auto smallestElement{ startElement };
            for (auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement) {
                // the comparison function is used to check if the current element should be ordered
                // before the currently "smallest" element.
                if (compare(*currentElement, *smallestElement)) { smallestElement = currentElement; }
            }
            std::swap(*startElement, *smallestElement);
        }
    }

    void doubleNumber(int& i) { i *= 2; }
    std::array arr{ 1, 2, 3, 4 };
    std::for_each(arr.begin(), arr.end(), doubleNumber);
}
{   // <----------- 18.4 ------------>
    #include <chrono> // for std::chrono functions
    
    class Timer {
    private:
        // Type aliases to make accessing nested type easier
        using Clock = std::chrono::steady_clock;
        using Second = std::chrono::duration<double, std::ratio<1> >;
        std::chrono::time_point<Clock> m_beg { Clock::now() };
    public:
        void reset() { m_beg = Clock::now(); }
        double elapsed() const {
            return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
        }
    };
    // Timer t;
    // /*code here*/
    // std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";
}
    return 0;
}