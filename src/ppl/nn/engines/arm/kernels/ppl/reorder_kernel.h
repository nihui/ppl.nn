// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef _ST_HPC_PPL_NN_ENGINES_ARM_KERNELS_PPL_REORDER_KERNEL_H_
#define _ST_HPC_PPL_NN_ENGINES_ARM_KERNELS_PPL_REORDER_KERNEL_H_

#include "ppl/nn/engines/arm/kernel.h"

namespace ppl { namespace nn { namespace arm {

inline TensorShape PadShapeTo3Dims(const TensorShape& shape) {
    if (shape.GetDimCount() >= 3) {
        return shape;
    }

    std::vector<int64_t> padded_dims(3, 1);
    const uint32_t offset = 3 - shape.GetRealDimCount();
    for (uint32_t i = offset; i < padded_dims.size(); i++) {
        padded_dims[i] = shape.GetDim(i - offset);
    }

    TensorShape padded_shape(shape);
    padded_shape.Reshape(padded_dims);
    return padded_shape;
}

class ReorderKernel : public ArmKernel {
public:
    ReorderKernel(const ir::Node* node) : ArmKernel(node) {}

private:
    ppl::common::RetCode DoExecute(KernelExecContext*) override;
};

}}} // namespace ppl::nn::ARM

#endif
