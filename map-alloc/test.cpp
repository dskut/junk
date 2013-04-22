
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <climits>
#include <boost/pool/pool_alloc.hpp>
using namespace std;

class Timer {
private:
    timespec start_;
public:
    Timer()
    {
        reset();
    }

    void reset() {
        clock_gettime(CLOCK_REALTIME, &start_);
    }

    unsigned long getMilliseconds() const {
        timespec end;
        clock_gettime(CLOCK_REALTIME, &end);
        time_t secs = end.tv_sec - start_.tv_sec;
        long nanosecs = end.tv_nsec - start_.tv_nsec;
        return secs*1000 + nanosecs/1000000;
    }
};

const int MaxInt = 100;
const size_t MaxStringLen = 100;

int randomInt(int max) {
    return (double)rand()/RAND_MAX * (max+1);
}

string randomString() {
    size_t size = randomInt(MaxStringLen);  
    string res(size, '\0');
    for (size_t i = 0; i < size; ++i) {
        res[i] = randomInt(255);
    }
    return res;
}

template <typename T>
class MyAlloc {
public:
    char* pool_;
    size_t next_;

    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <typename U>
    struct rebind {
        typedef MyAlloc<U> other;
    };

    MyAlloc(char* pool) throw()
        : pool_(pool)
        , next_(0)
    {
        //cout << "ctor" << endl;
    }

    MyAlloc(const MyAlloc& other) throw()
        : pool_(other.pool_)
        , next_(other.next_)
    {
        //cout << "copy ctor" << endl;
    }

    template <typename U>
    MyAlloc(const MyAlloc<U>& other) throw()
        : pool_(other.pool_)
        , next_(other.next_)
    {
        //cout << "template ctor" << endl;
    }

    ~MyAlloc() throw() {
        //cout << "detor" << endl;
    }

    pointer address(reference x) const {
        //cout << "address" << endl;
        return &x;
    }

    const_pointer address(const_reference x) const {
        //cout << "address const" << endl;
        return &x;
    }

    pointer allocate(size_type n, allocator<void>::const_pointer hint = 0) {
        //cout << "allocating" << endl;
        pointer res = (pointer)(&pool_[next_]);
        next_ += sizeof(T);
        return res;
    }

    void deallocate(pointer p, size_type n) {
        //cout << "deallocate" << endl;
        (void)p;
        (void)n;
    }

    size_type max_size() const throw() {
        //cout << "max_size" << endl;
        //return PoolSize;
        return INT_MAX;
    }

    void construct(pointer p, const value_type& val) {
        //cout << "construct" << endl;
        new(p) T(val);
    }

    void destroy(pointer p) {
        //cout << "destroy" << endl;
        p->~T();
    }
};

ostream& operator<<(ostream& o, const pair<string, int>& p) {
    o << p.first << "," << p.second;
    return o;
}

template <typename Dict>
void testInsert(Dict& dict, const vector<string>& strings, const vector<int>& nums, const string& prefix) {
    Timer timer;
    for (size_t i = 0; i < nums.size(); ++i) {
        dict.insert(make_pair(strings[i], nums[i]));
    }
    cout << prefix << " insert " << timer.getMilliseconds() << "ms" << endl;
}

template <typename Dict>
void testRead(Dict& dict, const vector<string>& strings, const string& prefix) {
    Timer timer;
    for (size_t i = 0; i < strings.size(); ++i) {
        (void)dict.find(strings[i]);
    }
    cout << prefix << " read " << timer.getMilliseconds() << "ms" << endl;
}

template <typename Dict>
void testDelete(Dict& dict, const string& prefix) {
    Timer timer;
    for (typename Dict::iterator iter = dict.begin(); iter != dict.end();) {
        dict.erase(iter++);
    }
    cout << prefix << " delete " << timer.getMilliseconds() << "ms" << endl;
}

void runDefault(const vector<string>& strings, const vector<int>& nums) {
    typedef map<string, int> Dict;
    Dict dict;
    string prefix = "default";

    testInsert(dict, strings, nums, prefix);
    testRead(dict, strings, prefix);
    testDelete(dict, prefix);
}

void runCustom(const vector<string>& strings, const vector<int>& nums) {
    size_t poolSize = 512*1024*1024;
    char* pool = new char[sizeof(int)*poolSize];
    MyAlloc<pair<string, int> > myAlloc(pool);

    typedef map<string, int, less<string>, MyAlloc<pair<string, int> > > MyDict;
    MyDict dict(less<string>(), myAlloc);

    string prefix = "custom";

    testInsert(dict, strings, nums, prefix);
    testRead(dict, strings, prefix);
    testDelete(dict, prefix);

    delete[] pool;
}

void runBoost(const vector<string>& strings, const vector<int>& nums) {
    typedef map<string, int, less<string>, boost::fast_pool_allocator<pair<string, int> > > BoostDict;
    BoostDict dict;
    string prefix = "boost";

    testInsert(dict, strings, nums, prefix);
    testRead(dict, strings, prefix);
    testDelete(dict, prefix);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "usage: " << argv[0] << " <d,c,b> <count>" << endl;
        return 1;
    }
    srand(time(NULL));

    int insertCount = atoi(argv[2]);
    vector<string> strings(insertCount);
    vector<int> nums(insertCount);

    for (size_t i = 0; i < insertCount; ++i) {
        strings[i] = randomString();
        nums[i] = randomInt(MaxInt);
    }

    char c = argv[1][0];
    if (c == 'c') {
        runCustom(strings, nums);
    } else if (c == 'd') {
        runDefault(strings, nums);
    } else if (c == 'b') {
        runBoost(strings, nums);
    } else {
        cerr << "unknown choice" << endl;
    }

    return 0;
}
