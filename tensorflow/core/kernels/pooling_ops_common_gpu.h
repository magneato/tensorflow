/* Copyright 2015 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#if !GOOGLE_CUDA
#error This file must only be included when building with Cuda support
#endif

#ifndef THIRD_PARTY_TENSORFLOW_CORE_KERNELS_POOLING_OPS_COMMON_GPU_H_
#define THIRD_PARTY_TENSORFLOW_CORE_KERNELS_POOLING_OPS_COMMON_GPU_H_

#include "tensorflow/stream_executor/dnn.h"
#include "third_party/eigen3/unsupported/Eigen/CXX11/NeuralNetworks"
#include "third_party/eigen3/unsupported/Eigen/CXX11/Tensor"
#include "tensorflow/core/framework/numeric_op.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/kernels/avgpooling_op.h"
#include "tensorflow/core/kernels/maxpooling_op.h"
#include "tensorflow/core/kernels/ops_util.h"
#include "tensorflow/core/public/tensor_shape.h"
#include "tensorflow/core/util/padding.h"

namespace tensorflow {

// A helper class that launch the cudnn pooling backward operations.
// The original input and output tensors are optional for AvgPoolGrad, but
// mandatory for MaxPoolGrad.
template <typename T>
class DnnPoolingGradOp {
 public:
  typedef GPUDevice Device;
  static void Compute(OpKernelContext* context,
                      perftools::gputools::dnn::PoolingMode pooling_mode,
                      const std::vector<int32>& size,
                      const std::vector<int32>& stride, Padding padding,
                      const Tensor* tensor_in, const Tensor* tensor_out,
                      const Tensor& out_backprop,
                      const TensorShape& tensor_in_shape);
};

}  // namespace tensorflow

#endif  // THIRD_PARTY_TENSORFLOW_CORE_KERNELS_POOLING_OPS_COMMON_GPU_H_
