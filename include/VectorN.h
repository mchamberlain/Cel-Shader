// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/** \file
 * \brief A templated n-dimensional vector class
 * \author ME Chamberlain
 */

#ifndef __VECTORN_H__
#define __VECTORN_H__

#include <math.h>
#include <assert.h>
#include <sstream>
#include <string>

template <typename TYPE, int N>
/** A templated n-dimensional vector class
 * \author ME Chamberlain
 */
class VectorN {
public:
    /** Constructs the zero vector */
    VectorN();

    /** Constructs a vector with the given values
     * @param v0 The first element of the vector
     * @param v1 The second element of the vector
     * @param v2 The third element of the vector
     * @param v3 The fourth element of the vector
     */
    VectorN(TYPE v0, TYPE v1 = 0, TYPE v2 = 0, TYPE v3 = 0);

    /** Constructs a vector from another vector
     * \param v The vector to copy
     */
    VectorN(const VectorN &v);

    /** Constructs a vector from an array
     * \param arr The array to copy the vector values from
     */
    VectorN(const TYPE *arr);

    //TODO: Implement required methods and operators

    /** Gets the value at the given index.
     * @param index The index of the value to fetch.
     * @return A copy of the value at index.
     */
    TYPE get(int index) const;

    /** Sets the value at the given index to the value specified.
     * @param index The index of the entry to set.
     * @param value The new value for the entry at index.
     */
    void set(int index, const TYPE& value);

    /** Creates a string representation of the vector in the format:
     * "(v0, v1, ..., vN-1)".
     * @return A string object containing a textual representation of the vector.
     */
    std::string toString() const;

    /** Copies the values from an array into this vector.
     * @param arr The array to copy values from.
     */
    void copyFrom(const TYPE *arr);

    /** Copies the values in this vector to an array.
     * @param arr The array to copy the values to.
     */
    void copyTo(TYPE* arr) const;

    /** Sets this vector to the zero vector. */
    void setZero();

    /** Test whether this vector is the zero vector.
     * @return true if this vector is the zero vector,
     *         false otherwise.
     */
    bool isZero() const;

    /** Returns the length of this vector.
     * @return the length of this vector.
     */
    TYPE length() const;

    /** Returns the length squared of this vector.
     * @return the length squared of this vector.
     */
    TYPE lengthSq() const;

    /** Sets the length of this vector.
     * @param length The length this vector should get.
     */
    void setLength(const TYPE &length);

    /** Normalize this vector (set its length to one). */
    void unitize();

    /** Calculates the distance form this vector to
     * the one specified.
     * @param vector The end vector for the distance calculation.
     */
    TYPE distanceTo(const VectorN& vector) const;

    /** Calculates the square of the distance form this vector to
     * the one specified.
     * @param vector The end vector for the distance calculation.
     */
    TYPE distanceToSq(const VectorN& vector) const;

    /** Calculates the dot product between this vector and the
     * specified one.
     * @param vector A vector
     * @return The dot product between this vector and the specified one.
     */
    TYPE dot(const VectorN& vector) const;

    /** Computes the cross product between two vectors and
     * returns the result.
     * @param vector The vector to compute this vector's cross product
     *               with.
     * @return The cross product of the this vector and the specified one.
     */
    VectorN cross(const VectorN& vector) const;

    /** Returns a vector perpendicular to this one. For vector
     * (v0, v1) the perpendicular vector is (-v1, v0).
     * @return The vector perpendicular to this one.
     */
    VectorN perp() const;

    /* ===================== OPERATORS ===================== */

    /** The + operator. Adds the values of one vector to another */
	inline VectorN operator +(const VectorN &p) const;

    /** The = operator. Assign a vector to this instance. */
    void operator =(const VectorN& vector);

    /** The += operator. Adds the values of the specified vector to this
     * one in place.
     */
    void operator +=(const VectorN& vector);

    /** The - operator. Subtracts the values of the specified vector from this one */
	inline VectorN operator -(const VectorN &p) const;

    /** The -= operator. Subtracts the values of the specified vector from this
     * one in place.
     */
    void operator -=(const VectorN& vector);

    /** Negate all the elements in this vector and return the result
     * without changing the vector.
     */
    inline VectorN operator-() const;

    /** Scale a vector and return the result without changing the vector. */
    inline VectorN operator *(const TYPE& scalar) const;

    /** Scale this vector */
    void operator *=(const TYPE& scalar);

    /** Inverse scale a vector and return the result without changing the vector. */
    inline VectorN operator /(const TYPE& scalar) const;

    /** Inverse scale this vector */
    void operator /=(const TYPE& scalar);

    /** Returns a reference to the value at the specified index in this vector. */
    TYPE& operator [](int index);

    /** Returns a constant reference to the value at the specified index in this vector. */
    const TYPE& operator [](int index) const;

    /** Test two vectors for equality. True iff every corresponding entry in the vectors are equal. */
    bool operator ==(const VectorN& vector) const;

    /** Test two vectors for inequality. True iff any corresponding entries in the vectors are inequal. */
    bool operator !=(const VectorN& vector) const;

protected:
    /** The vector data */
    TYPE vec[N];
};


/** A 2-dimensional float vector type */
typedef VectorN<float,2>    Vector2f;
/** A 2-dimensional double vector type */
typedef VectorN<double,2>   Vector2d;
/** A 2-dimensional integer vector type */
typedef VectorN<int,2>      Vector2i;

/** A 3-dimensional float vector type */
typedef VectorN<float,3>    Vector3f;
/** A 3-dimensional double vector type */
typedef VectorN<double,3>   Vector3d;
/** A 3-dimensional integer vector type */
typedef VectorN<int,3>      Vector3i;

/** A 4-dimensional float vector type */
typedef VectorN<float,4>    Vector4f;
/** A 4-dimensional double vector type */
typedef VectorN<double,4>   Vector4d;
/** A 4-dimensional integer vector type */
typedef VectorN<int,4>      Vector4i;

// ====== IMPLEMENTATION ======
template<typename TYPE, int N>
VectorN<TYPE, N>::VectorN() {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] = 0;
    }
}

template<typename TYPE, int N>
VectorN<TYPE, N>::VectorN(TYPE v0, TYPE v1, TYPE v2, TYPE v3) {
    if (N >= 1) {
        vec[0] = v0;
    }

    if (N >= 2) {
        vec[1] = v1;
    }

    if (N >= 3) {
        vec[2] = v2;
    }

    if (N >= 4) {
        vec[3] = v3;
    }

}

template<typename TYPE, int N>
VectorN<TYPE, N>::VectorN(const VectorN &v) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] = v.get(i);
    }
}

template<typename TYPE, int N>
VectorN<TYPE, N>::VectorN(const TYPE *arr) {
//        memcpy(vec, arr, N * sizeof(TYPE));
    int i;

    assert(arr != NULL);

    for (i = 0; i < N; i++) {
        vec[i] = arr[i];
    }
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::get(int index) const {
   assert(index < N);

   return vec[index];
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::set(int index, const TYPE& value) {
    assert(index < N);

    vec[index] = value;
}

template<typename TYPE, int N>
std::string VectorN<TYPE, N>::toString() const {
    std::ostringstream oss;
    int i;

    oss << "(";
    for (i = 0; i < N - 1; i++) {
        oss << vec[i] << ", ";
    }
    oss << vec[i] << ")";

    return oss.str();
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::copyFrom(const TYPE *arr) {
    int i;

    assert(arr != NULL);

    for (i = 0; i < N; i++) {
        vec[i] = arr[i];
    }
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::copyTo(TYPE* arr) const {
    int i;

    assert(arr != NULL);

    for (i = 0; i < N; i++) {
        arr[i] = vec[i];
    }
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::setZero() {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] = 0;
    }
}

template<typename TYPE, int N>
bool VectorN<TYPE, N>::isZero() const {
    int i;

    for (i = 0; i < N; i++) {
        if (vec[i] != 0) {
            return false;
        }
    }

    return true;
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::length() const {
    TYPE len;
    int i;

    len = vec[0] * vec[0];

    for (i = 1; i < N; i++) {
        len += vec[i] * vec[i];
    }

    return (TYPE) sqrt(len);
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::lengthSq() const {
    TYPE len;
    int i;

    len = vec[0] * vec[0];

    for (i = 1; i < N; i++) {
        len += vec[i] * vec[i];
    }

    return len;
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::setLength(const TYPE &length) {
    int i;

    unitize();

    for (i = 0; i < N; i++) {
        vec[i] *= length;
    }
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::unitize() {
    TYPE len;
    int i;

    len = length();

    assert(len != 0);

    for (i = 0; i < N; i++) {
        vec[i] /= len;
    }
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::distanceTo(const VectorN& vector) const {
    VectorN diff = (vector - *this);

    return diff.length();
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::distanceToSq(const VectorN& vector) const {
    VectorN diff = (vector - *this);

    return diff.lengthSq();
}

template<typename TYPE, int N>
TYPE VectorN<TYPE, N>::dot(const VectorN& vector) const {
    TYPE dotProduct;
    int i;

    dotProduct = vec[0] * vector.get(0);
    for (i = 1; i < N; i++) {
        dotProduct += vec[i] * vector.get(i);
    }

    return dotProduct;
}

/* ===================== OPERATORS ===================== */

template<typename TYPE, int N>
inline VectorN<TYPE, N> VectorN<TYPE, N>::operator +(const VectorN &p) const {
    VectorN result;
    int i;

    for (i = 0; i < N; i++) {
        result.set(i, vec[i] + p.get(i));
    }

    return result;
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::operator =(const VectorN& vector) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] = vector.get(i);
    }
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::operator +=(const VectorN& vector) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] += vector.get(i);
    }
}

template<typename TYPE, int N>
inline VectorN<TYPE, N> VectorN<TYPE, N>::operator -(const VectorN &p) const {
    VectorN result;
    int i;

    for (i = 0; i < N; i++) {
        result.set(i, vec[i] - p.get(i));
    }

    return result;
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::operator -=(const VectorN& vector) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] -= vector.get(i);
    }
}

template<typename TYPE, int N>
inline VectorN<TYPE, N> VectorN<TYPE, N>::operator-() const {
    VectorN result;
    int i;

    for (i = 0; i < N; i++) {
        result.set(i, -vec[i]);
    }

    return result;
}

template<typename TYPE, int N>
inline VectorN<TYPE, N> VectorN<TYPE, N>::operator *(const TYPE& scalar) const {
    VectorN result;
    int i;

    for (i = 0; i < N; i++) {
        result.set(i, vec[i] * scalar);
    }

    return result;
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::operator *=(const TYPE& scalar) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] *= scalar;
    }
}

template<typename TYPE, int N>
inline VectorN<TYPE, N> VectorN<TYPE, N>::operator /(const TYPE& scalar) const {
    VectorN result;
    int i;

    for (i = 0; i < N; i++) {
        result.set(i, vec[i] / scalar);
    }

    return result;
}

template<typename TYPE, int N>
void VectorN<TYPE, N>::operator /=(const TYPE& scalar) {
    int i;

    for (i = 0; i < N; i++) {
        vec[i] /= scalar;
    }
}

template<typename TYPE, int N>
TYPE& VectorN<TYPE, N>::operator [](int index) {
    assert(((index >= 0) && (index < N)));

    return vec[index];
}

template<typename TYPE, int N>
const TYPE& VectorN<TYPE, N>::operator [](int index) const {
    assert(((index >= 0) && (index < N)));

    return vec[index];
}

template<typename TYPE, int N>
bool VectorN<TYPE, N>::operator ==(const VectorN& vector) const {
    int i;

    for (i = 0; i < N; i++) {
        if (vec[i] != vector.get(i)) {
            return false;
        }
    }

    return true;
}

template<typename TYPE, int N>
bool VectorN<TYPE, N>::operator !=(const VectorN& vector) const {
    int i;

    for (i = 0; i < N; i++) {
        if (vec[i] != vector.get(i)) {
            return true;
        }
    }

    return false;
}

#endif // __VECTORN_H__

// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
