//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

/// \file Kokkos_Atomic.hpp
/// \brief Atomic functions
///
/// This header file defines prototypes for the following atomic functions:
///   - exchange
///   - compare and exchange
///   - add
///
/// Supported types include:
///   - signed and unsigned 4 and 8 byte integers
///   - float
///   - double
///
/// They are implemented through GCC compatible intrinsics, OpenMP
/// directives and native CUDA intrinsics.
///
/// Including this header file requires one of the following
/// compilers:
///   - NVCC (for CUDA device code only)
///   - GCC (for host code only)
///   - Intel (for host code only)
///   - A compiler that supports OpenMP 3.1 (for host code only)

#ifndef KOKKOS_ATOMIC_HPP
#define KOKKOS_ATOMIC_HPP
#ifndef KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_ATOMIC
#endif

#include <Kokkos_Macros.hpp>

#include <Kokkos_Atomics_Desul_Wrapper.hpp>
#include <Kokkos_Atomics_Desul_Volatile_Wrapper.hpp>
#include <impl/Kokkos_Utilities.hpp>

// Helper functions for places where we really should have called SeqCst atomics
// anyway These can go away when we call desul unconditionally Non-Desul
// versions are below
namespace Kokkos {
namespace Impl {
using desul::MemoryOrderSeqCst;
using desul::MemoryScopeDevice;

template <class T>
KOKKOS_INLINE_FUNCTION void desul_atomic_dec(T* dest, MemoryOrderSeqCst,
                                             MemoryScopeDevice) {
  return desul::atomic_dec(const_cast<T*>(dest), desul::MemoryOrderSeqCst(),
                           desul::MemoryScopeDevice());
}

template <class T>
KOKKOS_INLINE_FUNCTION void desul_atomic_inc(T* dest, MemoryOrderSeqCst,
                                             MemoryScopeDevice) {
  return desul::atomic_inc(const_cast<T*>(dest), desul::MemoryOrderSeqCst(),
                           desul::MemoryScopeDevice());
}

template <class T>
KOKKOS_INLINE_FUNCTION T
desul_atomic_exchange(T* dest, const Kokkos::Impl::type_identity_t<T> val,
                      MemoryOrderSeqCst, MemoryScopeDevice) {
  return desul::atomic_exchange(const_cast<T*>(dest), val,
                                desul::MemoryOrderSeqCst(),
                                desul::MemoryScopeDevice());
}

template <class T>
KOKKOS_INLINE_FUNCTION T desul_atomic_compare_exchange(
    T* dest, Kokkos::Impl::type_identity_t<const T> compare,
    Kokkos::Impl::type_identity_t<const T> val, MemoryOrderSeqCst,
    MemoryScopeDevice) {
  return desul::atomic_compare_exchange(dest, compare, val,
                                        desul::MemoryOrderSeqCst(),
                                        desul::MemoryScopeDevice());
}

}  // namespace Impl
}  // namespace Kokkos

#ifdef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_ATOMIC
#undef KOKKOS_IMPL_PUBLIC_INCLUDE
#undef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_ATOMIC
#endif
#endif /* KOKKOS_ATOMIC_HPP */
