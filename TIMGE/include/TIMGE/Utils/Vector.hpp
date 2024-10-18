#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

#include <initializer_list>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

namespace TIMGE
{
    template <typename Type_T, uint32_t DIMENSIONS> class Vector 
    {
      public:
        Vector();
        Vector(const Vector<Type_T, DIMENSIONS>& vector);
        Vector(Vector<Type_T, DIMENSIONS>&& vector);
        Vector(const std::initializer_list<Type_T>& list);
        ~Vector();
        Vector<Type_T, DIMENSIONS>& operator=(const Vector<Type_T, DIMENSIONS>& vector);
        Vector<Type_T, DIMENSIONS>& operator=(Vector<Type_T, DIMENSIONS>&& vector);

        [[nodiscard]] Type_T &operator[](std::size_t index);
        [[nodiscard]] const Type_T &operator[](std::size_t index) const;

        static constexpr std::size_t X = 0;
        static constexpr std::size_t R = 0;
        static constexpr std::size_t U = 0;
        static constexpr std::size_t WIDTH = 0;
        static constexpr std::size_t Y = 1;
        static constexpr std::size_t G = 1;
        static constexpr std::size_t V = 1;
        static constexpr std::size_t HEIGHT = 1;
        static constexpr std::size_t Z = 2;
        static constexpr std::size_t B = 2;
        static constexpr std::size_t Q = 2;
        static constexpr std::size_t DEPTH = 2;
        static constexpr std::size_t W = 3;
        static constexpr std::size_t A = 3;
      private:
        Type_T* mData;
    };

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector()
     : mData{new Type_T[DIMENSIONS]{}}
    {}

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(const Vector<Type_T, DIMENSIONS>& vector)
    {
      for (int i = 0; i < DIMENSIONS; i++) {
        mData[i] = vector.mData[i];
      }
    }

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(Vector<Type_T, DIMENSIONS>&& vector)
     : mData{vector.mData} {
      vector.mData = nullptr;
    }

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::Vector(const std::initializer_list<Type_T>& list)
    {
      // if (list.empty()) {
      //   for (int i = 0; i < DIMENSIONS; i++) {
      //     mData[i] = {};
      //   }
      // }
      // if (list.size() < DIMENSIONS) {
      //   for (int i = 0; i < list.size(); i++) {
      //     mData[i] = *(list.begin() + i);
      //   }
      //   for (int i = list.size(); i < DIMENSIONS; i++) {
      //     mData[i] = {};
      //   }
      // }
      // if (list.size() == DIMENSIONS) {
      //   for (int i = 0; i < DIMENSIONS; i++) {
      //     mData[i] = *(list.begin() + i);
      //   }
      // }
      // if (list.size() > DIMENSIONS) {
      //   throw std::out_of_range("Ur mom is as big as the size of this vector... Too big!");
      // }

      if (list.size() > DIMENSIONS) {
        throw std::out_of_range("Ur mom is as big as the size of this vector... Too big!");
      }

      mData = new Type_T[DIMENSIONS];

      int i = 0;
      for (i = 0; i < list.size(); i++) {
        mData[i] = *(list.begin() + i);
      }
      for (; i < DIMENSIONS; i++) {
        mData[i] = {};
      }
    }
    
    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>::~Vector() {
      delete[] mData;
    }

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>& Vector<Type_T, DIMENSIONS>::operator=(const Vector<Type_T, DIMENSIONS>& vector)
    {
      for (int i = 0; i < DIMENSIONS; i++) {
        mData[i] = vector.mData[i];
      }

      return *this;
    }

    template<typename Type_T, uint32_t DIMENSIONS>
    Vector<Type_T, DIMENSIONS>& Vector<Type_T, DIMENSIONS>::operator=(Vector<Type_T, DIMENSIONS>&& vector) {
      mData = vector.mData;

      delete[] vector.mData;
      vector.mData = nullptr;

      return *this;
    }

    template <typename Type_T, uint32_t DIMENSIONS>
    Type_T &Vector<Type_T, DIMENSIONS>::operator[](std::size_t index) {
      return mData[index];
    }

    template <typename Type_T, uint32_t DIMENSIONS>
    const Type_T &Vector<Type_T, DIMENSIONS>::operator[](std::size_t index) const {
      return mData[index];
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
