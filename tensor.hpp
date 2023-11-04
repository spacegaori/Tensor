#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iostream>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <vector>
#include <typeinfo>

namespace Neptune {

template<typename Type, std::size_t... Shape>
class Tensor {
private:
    std::vector<std::size_t> shape_ {};
    std::vector<Type> elements_ {};

public:
    template<typename... Args>
    Tensor(Args&&... args) : shape_{ Shape... }, elements_{ args... } { assert(sizeof...(Shape) <= 4); }

    const Type& operator[](std::size_t idx) const
    {
        assert(idx >= 0 && idx < std::size(elements_));
        return elements_.at(idx);
    }

    friend std::ostream& operator<<(std::ostream& out, const Tensor& tensor)
    { 
        std::size_t dim{ sizeof...(Shape) };
        switch (dim)
        {
            case 1:
            {
                std::size_t size{ tensor.shape_[0] };
                out << '[';
                for (std::size_t i{ 0 }; i < size; ++i)
                {
                    out << tensor.elements_.at(i);
                    if (i != (size - 1))
                        out << ' ';
                }
                out << '[';
                break;
            }
            case 2:
            {
                std::size_t rows{ tensor.shape_[0] };
                std::size_t cols{ tensor.shape_[1] };

                out << '[';
                for(std::size_t i{ 0 }; i < rows; ++i)
                {
                    if (i != (0))
                        out << ' ';
                    out << '[';

                    for(std::size_t j{ 0 }; j < cols; ++j)
                    {
                        out << tensor.elements_.at(i*cols+j);
                        if (j != (cols - 1))
                            out << ' ';
                    }
                    out << ']';
                    if (i != (rows - 1))
                        out << '\n';
                }
                out << ']';
                break;
            }

            case 3:
            {
                std::size_t x{ tensor.shape_[0] };
                std::size_t y{ tensor.shape_[1] };
                std::size_t z{ tensor.shape_[2] };

                out << '[';
                for(std::size_t i{ 0 }; i < x; ++i)
                {
                    if (i != (0))
                        out << ' ';
                    out << '[';
                    for(std::size_t j{ 0 }; j < y; ++j)
                    {
                        if (j != (0))
                            out << "  ";
                        out << '[';

                        for(std::size_t k{ 0 }; k < z; ++k)
                        {
                            out << tensor.elements_.at(j*z+k);
                            if (k != (z - 1))
                                out << ' ';
                        }
                        out << ']';
                        if (j != (y - 1))
                            out << '\n';
                    }
                    out << ']';
                    if (i != (x - 1))
                        out << '\n';
                }
                out << ']';

                break;
            }
            case 4:
            {
                std::size_t x{ tensor.shape_[0] };
                std::size_t y{ tensor.shape_[1] };
                std::size_t z{ tensor.shape_[2] };
                std::size_t w{ tensor.shape_[3] };

                out << '[';
                for(std::size_t i{ 0 }; i < x; ++i)
                {
                    if (i != (0))
                        out << ' ';
                    out << '[';
                    for(std::size_t j{ 0 }; j < y; ++j)
                    {
                        if (j != (0))
                            out << "  ";
                        out << "[";

                        for(std::size_t k{ 0 }; k < z; ++k)
                        {
                            if (k != 0)
                                out << "   ";
                            out << '[';
                            for(std::size_t l{ 0 }; l < w; ++l)
                            {
                                out << tensor.elements_.at(j*z+k);
                                if (l != (w - 1))
                                    out << ' ';
                            }
                            out << ']';
                            if (k != (z - 1))
                                out << '\n';
                        }
                        out << ']';
                        if (j != (y - 1))
                            out << '\n';
                    }
                    out << ']';
                    if (i != (x - 1))
                        out << '\n';
                }
                out << ']';

                break;
            }
        }
        return out;
    }

    std::string_view type() const { return typeid(Type).name(); }
    std::size_t capacity() const { return elements_.capacity(); }
    std::size_t shape(std::size_t idx) const { return shape_.at(idx); }
    std::size_t size() const { return elements_.size(); }
};

}

#endif