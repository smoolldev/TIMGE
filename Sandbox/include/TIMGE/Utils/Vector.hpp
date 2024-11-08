#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

#include "TIMGE/Exception.hpp"
#include <initializer_list>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

namespace TIMGE
{
    class VectorException : public Exception
    {
        public:
            VectorException(std::string message);
    };

    template<typename Type_T, std::size_t DIMENSIONS> class Vector 
    {
        public:
            Vector();
            Vector(const Vector<Type_T, DIMENSIONS>& vector);
            Vector(Vector<Type_T, DIMENSIONS>&& vector);
            Vector(const std::initializer_list<Type_T>& list);
            ~Vector();

            [[maybe_unused]] Vector<Type_T, DIMENSIONS>& operator=(const Vector<Type_T, DIMENSIONS>& vector);
            [[maybe_unused]] Vector<Type_T, DIMENSIONS>& operator=(Vector<Type_T, DIMENSIONS>&& vector);
            [[nodiscard]] bool operator<(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] bool operator>(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] bool operator<=(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] bool operator>=(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] bool operator==(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] bool operator!=(const Vector<Type_T, DIMENSIONS>& vector) const;
            [[nodiscard]] Type_T& operator[](std::size_t index);
            [[nodiscard]] const Type_T& operator[](std::size_t index) const;

            std::size_t GetSize() const;

            static constexpr std::size_t X = 0;
            static constexpr std::size_t R = 0;
            static constexpr std::size_t U = 0;
            static constexpr std::size_t WIDTH = 0;
            static constexpr std::size_t MIN_WIDTH = 0;
            static constexpr std::size_t GL_MAJOR = 0;
            static constexpr std::size_t LEFT = 0;
            static constexpr std::size_t NUMERATOR = 0;
            static constexpr std::size_t Y = 1;
            static constexpr std::size_t G = 1;
            static constexpr std::size_t V = 1;
            static constexpr std::size_t D = 1;
            static constexpr std::size_t HEIGHT = 1;
            static constexpr std::size_t MIN_HEIGHT = 1;
            static constexpr std::size_t GL_MINOR = 1;
            static constexpr std::size_t TOP = 1;
            static constexpr std::size_t DENOMINATOR = 1;
            static constexpr std::size_t Z = 2;
            static constexpr std::size_t B = 2;
            static constexpr std::size_t Q = 2;
            static constexpr std::size_t MAX_WIDTH = 2;
            static constexpr std::size_t DEPTH = 2;
            static constexpr std::size_t RIGHT = 2;
            static constexpr std::size_t W = 3;
            static constexpr std::size_t A = 3;
            static constexpr std::size_t MAX_HEIGHT = 3;
            static constexpr std::size_t BOTTOM = 3;
        private:
            Type_T* mData;
    };

    template<typename Type_T, std::size_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector()
     : mData{new Type_T[DIMENSIONS]{}}
    {}

    template<typename Type_T, std::size_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(const Vector<Type_T, DIMENSIONS>& vector)
     : mData{new Type_T[DIMENSIONS]}
    {
        for (int i = 0; i < DIMENSIONS; i++) {
            mData[i] = vector.mData[i];
        }
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(Vector<Type_T, DIMENSIONS>&& vector)
     : mData{vector.mData} {
        vector.mData = nullptr;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(const std::initializer_list<Type_T>& list)
     : mData{new Type_T[DIMENSIONS]{}}
    {
        if (list.size() > DIMENSIONS) {
            throw VectorException("Vector initializer list is too big.");
        }

        int i = 0;
        for (i = 0; i < list.size(); i++) {
            mData[i] = *(list.begin() + i);
        }
        for (; i < DIMENSIONS; i++) {
            mData[i] = {};
        }
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::~Vector() {
        delete[] mData;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[maybe_unused]] Vector<Type_T, DIMENSIONS>& Vector<Type_T, DIMENSIONS>::operator=(const Vector<Type_T, DIMENSIONS>& vector)
    {
        for (int i = 0; i < DIMENSIONS; i++) {
            mData[i] = vector.mData[i];
        }

        return *this;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[maybe_unused]] Vector<Type_T, DIMENSIONS>& Vector<Type_T, DIMENSIONS>::operator=(Vector<Type_T, DIMENSIONS>&& vector)
    {
        Type_T* tmp = mData;
        mData = vector.mData;

        delete[] tmp; 
        vector.mData = nullptr;

        return *this;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator<(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] >= vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator>(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] <= vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator<=(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] > vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator>=(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] < vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator==(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] != vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    [[nodiscard]] bool Vector<Type_T, DIMENSIONS>::operator!=(const Vector<Type_T, DIMENSIONS>& vector) const
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            if (mData[i] == vector.mData[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    Type_T& Vector<Type_T, DIMENSIONS>::operator[](std::size_t index) {
        return mData[index];
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    const Type_T& Vector<Type_T, DIMENSIONS>::operator[](std::size_t index) const {
        return mData[index];
    }

    template<typename Type_T, std::size_t DIMENSIONS>
    std::size_t Vector<Type_T, DIMENSIONS>::GetSize() const {
        return DIMENSIONS;
    }

    using V2f = Vector<float, 2>;
    using V3f = Vector<float, 3>;
    using V4f = Vector<float, 4>;

    using V2d = Vector<double, 2>;
    using V3d = Vector<double, 3>;
    using V4d = Vector<double, 4>;

    using V2i8 = Vector<int8_t, 2>;
    using V3i8 = Vector<int8_t, 3>;
    using V4i8 = Vector<int8_t, 4>;

    using V2ui8 = Vector<uint8_t, 2>;
    using V3ui8 = Vector<uint8_t, 3>;
    using V4ui8 = Vector<uint8_t, 4>;

    using V2i16 = Vector<int16_t, 2>;
    using V3i16 = Vector<int16_t, 3>;
    using V4i16 = Vector<int16_t, 4>;

    using V2ui16 = Vector<uint16_t, 2>;
    using V3ui16 = Vector<uint16_t, 3>;
    using V4ui16 = Vector<uint16_t, 4>;

    using V2i32 = Vector<int32_t, 2>;
    using V3i32 = Vector<int32_t, 3>;
    using V4i32 = Vector<int32_t, 4>;

    using V2ui32 = Vector<uint32_t, 2>;
    using V3ui32 = Vector<uint32_t, 3>;
    using V4ui32 = Vector<uint32_t, 4>;

    using V2i64 = Vector<int64_t, 2>;
    using V3i64 = Vector<int64_t, 3>;
    using V4i64 = Vector<int64_t, 4>;

    using V2ui64 = Vector<uint64_t, 2>;
    using V3ui64 = Vector<uint64_t, 3>;
    using V4ui64 = Vector<uint64_t, 4>;
}

#endif // UTILS_VECTOR_HPP
