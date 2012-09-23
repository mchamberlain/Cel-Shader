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

#include "VectorN.h"

//TODO: Include implementations of methods which have specific types,
// e.g. cross (float + double in 3D) and perp (int, float, double in 2D)

/** Computes the cross product between two vectors and
 * returns the result.
 * @param vector The vector to compute this vector's cross product
 *               with.
 * @return The cross product of the this vector and the specified one.
 */
template<>
Vector3f Vector3f::cross(const Vector3f& vector) const {
    Vector3f result;

    result.set(0, vec[1] * vector.get(2) - vec[2] * vector.get(1));
    result.set(1, -vec[0] * vector.get(2) + vec[2] * vector.get(0));
    result.set(2, vec[0] * vector.get(1) - vec[1] * vector.get(0));

    return result;
}

/** Computes the cross product between two vectors and
 * returns the result.
 * @param vector The vector to compute this vector's cross product
 *               with.
 * @return The cross product of the this vector and the specified one.
 */
template<>
Vector3d Vector3d::cross(const Vector3d& vector) const {
    Vector3d result;

    result.set(0, vec[1] * vector.get(2) - vec[2] * vector.get(1));
    result.set(1, -vec[0] * vector.get(2) + vec[2] * vector.get(0));
    result.set(2, vec[0] * vector.get(1) - vec[1] * vector.get(0));

    return result;
}

/** Returns a vector perpendicular to this one. For vector
 * (v0, v1) the perpendicular vector is (-v1, v0).
 * @return The vector perpendicular to this one.
 */
template<>
Vector2i Vector2i::perp() const {
    Vector2i result;

    result.set(0, -vec[1]);
    result.set(1, vec[0]);

    return result;
}

/** Returns a vector perpendicular to this one. For vector
 * (v0, v1) the perpendicular vector is (-v1, v0).
 * @return The vector perpendicular to this one.
 */
template<>
Vector2f Vector2f::perp() const {
    Vector2f result;

    result.set(0, -vec[1]);
    result.set(1, vec[0]);

    return result;
}

/** Returns a vector perpendicular to this one. For vector
 * (v0, v1) the perpendicular vector is (-v1, v0).
 * @return The vector perpendicular to this one.
 */
template<>
Vector2d Vector2d::perp() const {
    Vector2d result;

    result.set(0, -vec[1]);
    result.set(1, vec[0]);

    return result;
}

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
