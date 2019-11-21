/*
  ==============================================================================

    Vec3D.h
    Author:  Alan Pawlak
    
    Alan.Pawlak@hud.ac.uk

    Header 3D Vector struct.
 
    Using inline functions, as they are more efficient for simple tasks
    
    Left-handed coordinate system
    (the positive x, y and z axes point right, up and forward, respectively)
 
  ==============================================================================
*/

#pragma once
#include <cmath>

template <typename T>
struct Vec3D {
public:
    // Public to avoid get/set methods
    T x, y, z;
    
    // Constructors and destructors /
    inline Vec3D()                                                      : x(0), y(0), z(0) {}
    inline Vec3D(const T& xValue, const T& yValue, const T& zValue)     : x(xValue), y(yValue), z(zValue) {}
    inline Vec3D(const Vec3D& vec)                                      : x(vec.x), y(vec.y), z(vec.z) {}
    
    ~Vec3D()                                                            {}

    
/*
  ==============================================================================

        Overriding operators
 
  ==============================================================================
*/
    
    // Add
    inline Vec3D operator+ ()                                           { return *this; }
    
    inline Vec3D operator+ (const Vec3D& vec)             \              { return Vec3D(x + vec.x, y + vec.y, z + vec.z); }
    
    inline Vec3D& operator+= (const Vec3D& vec)                         { return *this = *this + vec; }
    
    // Substract
    inline Vec3D operator- ()                                           { return Vec3D(-x, -y, -z); }
    
    inline const Vec3D operator- (const Vec3D& vec)                     { return Vec3D(x - vec.x, y - vec.y, z - vec.z); }
    
    inline Vec3D& operator-= (const Vec3D& vec)                         { return *this = *this - vec; }
    
    // Multiply
    inline Vec3D operator* (const T& val)                               { return Vec3D(x*val, y*val, z*val); }
    
    inline Vec3D& operator*= (const T& val)                             { return *this = *this * val; }
    
    // Divide
    inline Vec3D operator/ (const T& val)                               { return Vec3D(x/val, y/val, z/val); }
    
    inline Vec3D& operator/= (const T& val)                             { return *this = *this / val; }
    
    
    // Equals
    inline Vec3D& operator= (Vec3D vec)                                 { x = vec.x; y = vec.y, z = vec.z; return *this; }

    
    // Indexing
    inline T operator[] (int index) {
        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        return T();
    }
    
    
/*
  ==============================================================================

    Common vector functions
 
  ==============================================================================
 */
    
    // Dot product
    inline T dot(const Vec3D& vec)                      { return x * vec.x + y * vec.y + z * vec.z; }
    
    // Vector square (Dot product with itself)
    inline T square()                                   { return  dot(*this); }
    
    // Cross product
    inline Vec3D cross(const Vec3D& vec)                { return  Vec3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x); }
    
    // Normalise
    void normalise()                                    { *this /= getMagnitude(); }
    
    // Vector length/magnitude
    inline T getMagnitude()                             { return  std::sqrt(square()); }
    
    // Get distance from vector b
    inline T getDistance(const Vec3D& vec)              { Vec3D d = *this - vec; return  d.getMagnitude(); }
    
    // Get elevation angle from vector
    inline double getElevation()                        { return std::asin(y); }
    
    // Get azimuth angle from vector
    double getAzimuth() {
        double az = std::atan(x/z);
        if (z < 0) {
            if (z >= 0) {
                az += M_PI;
            }
            else {
                az -= M_PI;
            }
        }
        if (x == 0 && z == 0) {
            az = 0;
        }
        return az;
    }
    
/*
 ==============================================================================

   Rotation matrices

 ==============================================================================
*/
    
    inline Vec3D rotateX(double angle) {
        
        const double rM_X[3][3] =
        { {1, 0, 0},
          {0, std::cos(angle), -std::sin(angle)},
          {0, std::sin(angle), std::cos(angle)} };

        return Vec3D(x*rM_X[0][0] + y * rM_X[1][0] + z * rM_X[2][0], x*rM_X[0][1] + y * rM_X[1][1] + z * rM_X[2][1], x*rM_X[0][2] + y * rM_X[1][2] + z * rM_X[2][2]);
        }
    
     inline Vec3D rotateY(double angle) {
        
        const double rM_Y[3][3] =
        { {std::cos(angle), 0, std::sin(angle)},
          {0, 1, 0},
          {-std::sin(angle), 0, std::cos(angle)} };
    
        return Vec3D(x*rM_Y[0][0] + y * rM_Y[1][0] + z * rM_Y[2][0], x*rM_Y[0][1] + y * rM_Y[1][1] + z * rM_Y[2][1], x*rM_Y[0][2] + y * rM_Y[1][2] + z * rM_Y[2][2]);
    }
    
     inline Vec3D rotateZ(double angle) {
        double rM_Z[3][3] =
        { {std::cos(angle), -std::sin(angle), 0},
          {std::sin(angle), std::cos(angle), 0},
          {0, 0, 1} };
    
        return Vec3D(x*rM_Z[0][0] + y * rM_Z[1][0] + z * rM_Z[2][0], x*rM_Z[0][1] + y * rM_Z[1][1] + z * rM_Z[2][1], x*rM_Z[0][2] + y * rM_Z[1][2] + z * rM_Z[2][2]);
    }
};
