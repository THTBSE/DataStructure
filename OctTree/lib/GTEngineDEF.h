// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.3 (2014/10/25)

#pragma once

#if defined(WIN32)
#if !defined(_MSC_VER) || _MSC_VER < 1800
#error Microsoft Visual Studio 2013 or later is required.
#endif

// Debug build values (choose_your_value is 0, 1, or 2)
// 0:  Disables checked iterators and disables iterator debugging.
// 1:  Enables checked iterators and disables iterator debugging.
// 2:  (default) Enables iterator debugging; checked iterators are not relevant.
//
// Release build values (choose_your_value is 0 or 1)
// 0:  (default) Disables checked iterators.
// 1:  Enables checked iterators; iterator debugging is not relevant.
//
// #define _ITERATOR_DEBUG_LEVEL choose_your_value

#endif

// Add GTE_EXPORT to project preprocessor options for dynamic library
// configurations to export their symbols.
#if defined(GTE_EXPORT)
    // For the dynamic library configurations.
    #define GTE_IMPEXP __declspec(dllexport)
#else
    // For a client of the dynamic library or for the static library
    // configurations.
    #define GTE_IMPEXP
#endif

// Select the storage convention for matrices and the matrix-vector
// multiplication convention..  Exactly one convention must be enabled
// for each.
//
// By user request, in your code you can define the preprocessor symbol
// GTE_SELECT_CONVENTION_EXTERNALLY.  This is convenient if you want to
// select default conventions different from ours *and* you do not want
// to do so by editing this file when we post new versions of the engine.
// For example, if you want to use only our mathematics template files,
// you can generate a wrapper, say, MyWrapper.h that contains the following:
//
// #pragma once
// #define GTE_SELECT_CONVENTION_EXTERNALLY
// #define GTE_USE_ROW_MAJOR
// #define GTE_USE_VEC_MAT
// #include <GteVector.h>
// #include <GteVector2.h>
// #include <GteVector3.h>
// #include <GteVector4.h>
// #include <GteMatrix.h>
// #include <GteMatrix2x2.h>
// #include <GteMatrix3x3.h>
// #include <GteMatrix4x4.h>
// #include <GteAxisAngle.h>
// #include <GteEulerAngles.h>
// #include <GteQuaternion.h>
// #include <GteRotation.h>
//
// and then include MyWrapper.h in your own source files.
//
// A REALLY BIG WARNING:  Do this at your own risk.  If you include other
// GTEngine .h or .inl files, you must ensure they pick up your preprocessor
// definitions.  If you include GTEngine .cpp files that depend on these
// preprocessor definitions, those files will not pick up your definitions
// unless you edit the files.  Consequently, you will have inconsistent
// conventions in your application that will be dreadfully painful to
// debug.  For example, the Camera class uses these definitions in
// GteCamera.cpp.  But the point of the request for this feature was not
// to have to edit GTEngineDEF.h.  Our advice?  Do not do this.  Just edit
// GTEngineDEF.h each time we ship a new version...

#if !defined(GTE_SELECT_CONVENTION_EXTERNALLY)
// Expose exactly one of these.
#define GTE_USE_ROW_MAJOR
//#define GTE_USE_COL_MAJOR

// Expose exactly one of these.
#define GTE_USE_MAT_VEC
//#define GTE_USE_VEC_MAT
#endif

#if (defined(GTE_USE_ROW_MAJOR) && defined(GTE_USE_COL_MAJOR)) || (!defined(GTE_USE_ROW_MAJOR) && !defined(GTE_USE_COL_MAJOR))
#error Exactly one storage order must be specified.
#endif

#if (defined(GTE_USE_MAT_VEC) && defined(GTE_USE_VEC_MAT)) || (!defined(GTE_USE_MAT_VEC) && !defined(GTE_USE_VEC_MAT))
#error Exactly one multiplication convention must be specified.
#endif
