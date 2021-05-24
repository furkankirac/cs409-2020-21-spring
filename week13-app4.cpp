// = delete, = default
// unique_ptr<T>, make_unique, get, operator bool, operator *, operator ->
// shared_ptr<T>, make_shared

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
struct Mat
{
    using type = T;
    size_t rows, cols;
    vector<T> data;

    Mat(size_t rows = 0, size_t cols = 0, T init = T{}) : rows{rows}, cols{cols}, data(rows*cols, init) { }

    const T* operator[](size_t r) const { return &data[r*cols]; }
    T* operator[](size_t r) { return &data[r*cols]; }
};

//template<typename T, typename ... Ts>
//auto MAKE_UNIQUE(Ts&& ... ts)
//{
//    return std::unique_ptr<T>(new T(forward<Ts...>(ts)...));
//}

template<typename T>
void func(std::unique_ptr<Mat<T>> m)
{

}

template<typename T>
void func(Mat<T>* m_ptr)
{
    // do performant thing
}

template<typename T>
void func(Mat<T>& m_ptr)
{
    // do performant thing
}

template<typename T>
void func(std::shared_ptr<Mat<T>> m_ptr)
{
    std::cout << m_ptr.use_count() << std::endl;

    // do shared thing
}


int main()
{
    auto m = Mat<int>(1000, 1000, 0);
//    auto m2 = m; // we used copy c-tor
    auto m3 = Mat<int>(1, 1, 0);
//    m3 = m;

//    auto m_unique = std::unique_ptr<Mat<int>>(new Mat<int>(100, 100, 0));
    auto m_unique = std::make_unique<Mat<int>>(100, 100, 0);
//    func(move(m_unique));
    func(m_unique.get());
    func(*m_unique);
    if(m_unique) {

    }

    auto m_shared = std::make_shared<Mat<int>>(100, 100, 0);
    std::cout << m_shared.use_count() << std::endl;
    func(m_shared);
    std::cout << m_shared.use_count() << std::endl;


    return 0;
}
