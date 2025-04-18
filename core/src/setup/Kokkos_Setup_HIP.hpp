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

#ifndef KOKKOS_SETUP_HIP_HPP_
#define KOKKOS_SETUP_HIP_HPP_

#if defined(KOKKOS_ENABLE_HIP)

#if defined(KOKKOS_ARCH_AMD_GFX942) && defined(KOKKOS_ARCH_AMD_GFX942_APU)
static_assert(false,
              "Kokkos detected both `KOKKOS_ARCH_AMD_GFX942` and "
              "`KOKKOS_ARCH_AMD_GFX942_APU` which is not allowed.");
#endif

#define KOKKOS_IMPL_HIP_CLANG_WORKAROUND

#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

#define KOKKOS_LAMBDA [=] __host__ __device__
#define KOKKOS_CLASS_LAMBDA [ =, *this ] __host__ __device__

#define KOKKOS_DEDUCTION_GUIDE __host__ __device__

#define KOKKOS_IMPL_FORCEINLINE_FUNCTION __device__ __host__ __forceinline__
#define KOKKOS_IMPL_INLINE_FUNCTION __device__ __host__ inline
#define KOKKOS_IMPL_FUNCTION __device__ __host__
#define KOKKOS_IMPL_HOST_FUNCTION __host__
#define KOKKOS_IMPL_DEVICE_FUNCTION __device__

// clang-format off
#ifdef KOKKOS_ENABLE_HIP_RELOCATABLE_DEVICE_CODE
#define KOKKOS_IMPL_RELOCATABLE_FUNCTION __device__ __host__
#else
#define KOKKOS_IMPL_RELOCATABLE_FUNCTION @"KOKKOS_RELOCATABLE_FUNCTION requires Kokkos_ENABLE_HIP_RELOCATABLE_DEVICE_CODE=ON"
#endif
// clang-format on

// The implementation of hipGraph in ROCm 5.2 is bugged, so we cannot use it.
#if !((HIP_VERSION_MAJOR == 5) && (HIP_VERSION_MINOR == 2))
#define KOKKOS_IMPL_HIP_NATIVE_GRAPH
#endif

#ifdef KOKKOS_ARCH_AMD_GFX942_APU
#define KOKKOS_IMPL_HIP_UNIFIED_MEMORY
#endif

#endif  // #if defined( KOKKOS_ENABLE_HIP )

#endif
