
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

template <typename T, size_t PoolSize = 64*1024*1024>
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
        //: pool_(new char[sizeof(T)*PoolSize])
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
        //free(pool_);
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
        //cout << "p = " << p << "; *p = " << *p << endl;
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

void testDefault(vector<string>& strings, vector<int>& nums) {
    Timer timer;
    
    typedef map<string, int> Dict;
    Dict dict;

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        dict[strings[i]] = nums[i];
    }
    cout << "default insert " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        nums[i] = dict[strings[i]];
    }
    cout << "default read " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (Dict::iterator iter = dict.begin(); iter != dict.end();) {
        dict.erase(iter++);
    }
    cout << "default delete " << timer.getMilliseconds() << "ms" << endl;
}

void testCustom(vector<string>& strings, vector<int>& nums) {
    Timer timer;

    size_t poolSize = 64*1024*1024;
    char* pool = new char[sizeof(int)*poolSize];
    MyAlloc<pair<string, int> > myAlloc(pool);

    typedef map<string, int, less<string>, MyAlloc<pair<string, int> > > MyDict;
    MyDict dict(less<string>(), myAlloc);

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        dict[strings[i]] = nums[i];
    }
    cout << "custom insert " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        nums[i] = dict[strings[i]];
    }
    cout << "custom read " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (MyDict::iterator iter = dict.begin(); iter != dict.end();) {
        dict.erase(iter++);
    }
    cout << "custom delete " << timer.getMilliseconds() << "ms" << endl;
    delete[] pool;
}

void testBoost(vector<string>& strings, vector<int>& nums) {
    Timer timer;

    typedef map<string, int, less<string>, boost::fast_pool_allocator<pair<string, int> > > BoostDict;
    BoostDict dict;

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        dict[strings[i]] = nums[i];
    }
    cout << "boost insert " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (size_t i = 0; i < nums.size(); ++i) {
        nums[i] = dict[strings[i]];
    }
    cout << "boost read " << timer.getMilliseconds() << "ms" << endl;

    timer.reset();
    for (BoostDict::iterator iter = dict.begin(); iter != dict.end();) {
        dict.erase(iter++);
    }
    cout << "boost delete " << timer.getMilliseconds() << "ms" << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <count>" << endl;
        return 1;
    }
    srand(time(NULL));

    int insertCount = atoi(argv[1]);
    vector<string> strings(insertCount);
    vector<int> nums(insertCount);

    for (size_t i = 0; i < insertCount; ++i) {
        strings[i] = randomString();
        nums[i] = randomInt(MaxInt);
    }

    testCustom(strings, nums);
    testDefault(strings, nums);
    testBoost(strings, nums);

    return 0;
}
