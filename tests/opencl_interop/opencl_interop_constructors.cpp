/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Copyright:	(c) 2017 by Codeplay Software LTD. All Rights Reserved.
//
*******************************************************************************/

#include "../../util/opencl_helper.h"
#include "../../util/test_base_opencl.h"
#include "../common/common.h"

#define TEST_NAME opencl_interop_constructors

namespace opencl_interop_constructors__ {
using namespace sycl_cts;

class buffer_interop_constructor_kernel;
class image_interop_constructor_kernel_default_event;
class image_interop_constructor_kernel_provided_event;
class sampler_interop_constructor_kernel;

/** tests the constructors for OpenCL inter-op
 */
class TEST_NAME : public sycl_cts::util::test_base_opencl {
 public:
  /** return information about this test
   */
  void get_info(test_base::info &out) const override {
    set_test_info(out, TOSTRING(TEST_NAME), TEST_FILE);
  }

  /** execute this test
   */
  void run(util::logger &log) override {
    try {
      cts_selector ctsSelector;
      const auto ctsContext = util::get_cts_object::context(ctsSelector);
      const auto ctsDevice = ctsContext.get_devices()[0];

      if (ctsContext.is_host()) {
        log.note("OpenCL interop doesn't work on host");
        return;
      }

      std::string kernelSource = R"(
            __kernel void opencl_interop_constructors_kernel(__global float *input)
            {
              input[get_global_id(0)] = get_global_id(0);
            }
            )";
      std::string programBinaryFile =
          "opencl_interop_constructors.bin";
      /** check platform (cl_platform_id) constructor
       */
      {
        sycl::platform platform(m_cl_platform_id);

        cl_platform_id interopPlatformID = platform.get();
        if (interopPlatformID != m_cl_platform_id) {
          FAIL(log, "platform was not constructed correctly");
        }
      }

      /** check device (cl_device_id) constructor
       */
      {
        sycl::device device(m_cl_device_id);

        cl_device_id interopDeviceID = device.get();
        if (interopDeviceID != m_cl_device_id) {
          FAIL(log, "device was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseDevice(interopDeviceID))) {
          FAIL(log, "failed to release OpenCL device");
        }
      }

      /** check context (cl_context) constructor
       */
      {
        sycl::context context(m_cl_context);

        cl_context interopContext = context.get();
        if (interopContext != m_cl_context) {
          FAIL(log, "context was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseContext(interopContext))) {
          FAIL(log, "failed to release OpenCL context");
        }
      }

      /** check context (cl_context, async_handler) constructor
       */
      {
        cts_async_handler asyncHandler;
        sycl::context context(m_cl_context, asyncHandler);

        cl_context interopContext = context.get();
        if (interopContext != m_cl_context) {
          FAIL(log, "context was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseContext(interopContext))) {
          FAIL(log, "failed to release OpenCL context");
        }
      }

      /** check queue (cl_command_queue, const context&) constructor
       */
      {
        sycl::queue queue(m_cl_command_queue, ctsContext);

        cl_command_queue interopQueue = queue.get();
        if (interopQueue != m_cl_command_queue) {
          FAIL(log, "queue was not constructed correctly");
        }

        /** check that queue copy constructor preserve the same OpenCL queue
         */
        sycl::queue queueCopy(queue);
        auto clQueueCopy = queueCopy.get();
        if (interopQueue != clQueueCopy) {
          FAIL(log, "queue destination was not copy constructed correctly");
        }

        if (!CHECK_CL_SUCCESS(log, clReleaseCommandQueue(clQueueCopy))) {
          FAIL(log, "failed to release OpenCL command queue");
        }

        if (!CHECK_CL_SUCCESS(log, clReleaseCommandQueue(interopQueue))) {
          FAIL(log, "failed to release OpenCL command queue");
        }
      }

      /** check queue (cl_command_queue, const context&, async_handler)
       * constructor
       */
      {
        cts_async_handler asyncHandler;
        sycl::queue queue(m_cl_command_queue, ctsContext, asyncHandler);

        cl_command_queue interopQueue = queue.get();
        if (interopQueue != m_cl_command_queue) {
          FAIL(log, "queue was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseCommandQueue(interopQueue))) {
          FAIL(log, "failed to release OpenCL command queue");
        }
      }

      /** check program (context, cl_program) constructor
       */
      {
        cl_program clProgram{};
        if (online_compiler_supported(ctsDevice.get(), log)) {
          if (!create_built_program(kernelSource, ctsContext.get(),
                                    ctsDevice.get(), clProgram, log)) {
            FAIL(log, "create_built_program failed");
          }
        } else {
          if (!create_program_with_binary(programBinaryFile, ctsContext.get(),
                                          ctsDevice.get(), clProgram, log)) {
            std::string errorMsg =
                "create_program_with_binary failed.";
            errorMsg +=
                " Since online compile is not supported, expecting to find " +
                programBinaryFile + " in same path as the executable binary";
            FAIL(log, errorMsg.c_str());
          }
        }

        sycl::program program(ctsContext, clProgram);

        cl_program interopProgram = program.get();
        if (interopProgram != clProgram) {
          FAIL(log, "program was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseProgram(interopProgram))) {
          FAIL(log, "failed to release OpenCL program");
        }
      }

      /** check kernel (cl_kernel, const context&) constructor
       */
      {
        cl_program clProgram{};
        if (online_compiler_supported(ctsDevice.get(), log)) {
          if (!create_built_program(kernelSource, ctsContext.get(),
                                    ctsDevice.get(), clProgram, log)) {
            FAIL(log, "create_built_program failed");
          }
        } else {
          if (!create_program_with_binary(programBinaryFile, ctsContext.get(),
                                          ctsDevice.get(), clProgram, log)) {
            std::string errorMsg =
                "create_program_with_binary failed.";
            errorMsg +=
                " Since online compile is not supported, expecting to find " +
                programBinaryFile + " in same path as the executable binary";
            FAIL(log, errorMsg.c_str());
          }
        }

        cl_kernel clKernel{};
        if (!create_kernel(clProgram, "opencl_interop_constructors_kernel",
                           clKernel, log)) {
          FAIL(log, "create_kernel failed");
        }

        sycl::kernel kernel(clKernel, ctsContext);

        cl_kernel interopKernel = kernel.get();
        if (interopKernel != clKernel) {
          FAIL(log, "kernel was not constructed correctly");
        }
        if (!CHECK_CL_SUCCESS(log, clReleaseKernel(interopKernel))) {
          FAIL(log, "failed to release OpenCL kernel");
        }
      }

      /** check buffer (cl_mem, contex) constructor
       */
      {
        const size_t size = 32;
        int data[size] = {0};
        cl_int error = CL_SUCCESS;

        auto queue = util::get_cts_object::queue(ctsSelector);

        cl_mem clBuffer = clCreateBuffer(
            queue.get_context().get(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
            size * sizeof(int), data, &error);
        if (!CHECK_CL_SUCCESS(log, error)) {
          FAIL(log, "create buffer failed");
        }

        sycl::buffer<int, 1> buffer(clBuffer, queue.get_context());

        // calculate element count, size and range for the interop buffer
        sycl::range<1> interopRange{size};
        size_t interopSize = size * sizeof(int);


        // check the buffer
        if (buffer.is_sub_buffer()) {
          FAIL(log,
               "opencl buffer was not interop constructed properly. "
               "(is_sub_buffer) ");
        }
        if (buffer.get_size() != interopSize) {
          FAIL(log,
               "opencl buffer was not interop constructed properly. (get_size) ");
        }
        if (buffer.get_range() != interopRange) {
          FAIL(
              log,
              "opencl buffer was not interop constructed properly. (get_range) ");
        }
        if (buffer.get_count() != size) {
          FAIL(
              log,
              "opencl buffer was not interop constructed properly. (get_count) ");
        }

        queue.submit([&](sycl::handler &handler) {
          auto accessor =
              buffer.get_access<sycl::access_mode::read_write,
                                sycl::target::device>(
                  handler);
          handler.single_task<class buffer_interop_constructor_kernel_no_event>([]() {});
        });

        error = clReleaseMemObject(clBuffer);
        if (!CHECK_CL_SUCCESS(log, error)) {
          FAIL(log, "failed to release OpenCL buffer");
        }

        queue.wait_and_throw();
      }

      /** check buffer (cl_mem, context, event) constructor
       */
      {
        const size_t size = 32;
        int data[size] = {0};
        cl_int error = CL_SUCCESS;

        auto queue = util::get_cts_object::queue(ctsSelector);

        // create an event to wait for
        sycl::event event = queue.submit([](sycl::handler &cgh) {
          cgh.single_task<class buffer_interop_event>(
              []() {});  // do not do anything here, we only need the event
        });

        cl_mem clBuffer = clCreateBuffer(
            queue.get_context().get(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
            size * sizeof(int), data, &error);
        if (!CHECK_CL_SUCCESS(log, error)) {
          FAIL(log, "create buffer failed");
        }

        sycl::buffer<int, 1> buffer(clBuffer, queue.get_context(), event);

        // calculate element count, size and range for the interop buffer
        sycl::range<1> interopRange{size};
        size_t interopSize = size * sizeof(int);


        // check the buffer
        if (buffer.is_sub_buffer()) {
          FAIL(log,
               "opencl buffer was not interop constructed properly. "
               "(is_sub_buffer) ");
        }
        if (buffer.get_size() != interopSize) {
          FAIL(log,
               "opencl buffer was not interop constructed properly. (get_size) ");
        }
        if (buffer.get_range() != interopRange) {
          FAIL(
              log,
              "opencl buffer was not interop constructed properly. (get_range) ");
        }
        if (buffer.get_count() != size) {
          FAIL(
              log,
              "opencl buffer was not interop constructed properly. (get_count) ");
        }

        queue.submit([&](sycl::handler &handler) {
          auto accessor =
              buffer.get_access<sycl::access_mode::read_write,
                                sycl::target::device>(
                  handler);
          handler.single_task<class buffer_interop_constructor_kernel_with_event>([]() {});
        });

        error = clReleaseMemObject(clBuffer);
        if (!CHECK_CL_SUCCESS(log, error)) {
          FAIL(log, "failed to release OpenCL buffer");
        }

        queue.wait_and_throw();
      }

      /** check image (cl_mem, const context&, event) constructor
       */
      {
        auto queue = util::get_cts_object::queue(ctsSelector);
        if (!queue.get_device()
                 .get_info<sycl::info::device::image_support>()) {
          log.note("Device does not support images");
        } else {
          constexpr size_t imageSideSize = 16;
          /* Size is *4 because image data is 4 channels (RGBA) */
          constexpr auto size = imageSideSize * imageSideSize * 4;
          float data[size] = {0.0f};

          const auto clContext = queue.get_context().get();

          cl_image_format clImageFormat;
          clImageFormat.image_channel_data_type = CL_FLOAT;
          clImageFormat.image_channel_order = CL_RGBA;

          cl_image_desc clImageDesc;
          clImageDesc.image_type = CL_MEM_OBJECT_IMAGE2D;
          clImageDesc.image_width = imageSideSize;
          clImageDesc.image_height = imageSideSize;
          clImageDesc.image_depth = 0;
          clImageDesc.image_array_size = 1;
          clImageDesc.image_row_pitch = 0;
          clImageDesc.image_slice_pitch = 0;
          clImageDesc.num_mip_levels = 0;
          clImageDesc.num_samples = 0;
          clImageDesc.buffer = nullptr;

          cl_int error = CL_SUCCESS;
          // Check constructing image with defaulted event
          {
            cl_mem clImage = clCreateImage(
                clContext, (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR),
                &clImageFormat, &clImageDesc, data, &error);
            if (!CHECK_CL_SUCCESS(log, error)) {
              FAIL(log, "create image failed");
            }

            sycl::image<2> image(clImage, queue.get_context());

            queue.submit([&](sycl::handler &handler) {
              auto accessor =
                  image.get_access<sycl::float4,
                                   sycl::access_mode::read>(handler);
              handler.single_task<
                  class image_interop_constructor_kernel_default_event>(
                  []() {});
            });

            error = clReleaseMemObject(clImage);
            if (!CHECK_CL_SUCCESS(log, error)) {
              FAIL(log, "failed to release OpenCL image");
            }
          }

          // Check constructing image with specified event
          {
            sycl::event event;
            cl_mem clImage = clCreateImage(
                clContext, (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR),
                &clImageFormat, &clImageDesc, data, &error);
            if (!CHECK_CL_SUCCESS(log, error)) {
              FAIL(log, "create image failed");
            }

            sycl::image<2> image(clImage, queue.get_context(), event);

            queue.submit([&](sycl::handler &handler) {
              auto accessor =
                  image.get_access<sycl::float4,
                                   sycl::access_mode::read>(handler);
              handler.single_task<
                  class image_interop_constructor_kernel_provided_event>(
                  []() {});
            });

            error = clReleaseMemObject(clImage);
            if (!CHECK_CL_SUCCESS(log, error)) {
              FAIL(log, "failed to release OpenCL image");
            }
          }
          queue.wait_and_throw();
        }
      }

      /** check sampler (cl_sampler, const context&) constructor
       */
      {
        auto queue = util::get_cts_object::queue(ctsSelector);
        if (!queue.get_device()
                 .get_info<sycl::info::device::image_support>()) {
          log.note("Device does not support images");
        } else {
          cl_sampler clSampler;
          create_sampler(clSampler, log);

          queue.submit([&](sycl::handler &handler) {
            sycl::sampler sampler(clSampler, queue.get_context());

            handler.single_task<class sampler_interop_constructor_kernel>(
                []() {});
          });

          cl_int error = clReleaseSampler(clSampler);
          if (!CHECK_CL_SUCCESS(log, error)) {
            FAIL(log, "failed to release OpenCL sampler");
          }

          queue.wait_and_throw();
        }
      }

      /** check event (cl_event, const context&) constructor
       */
      {
        cl_event clEvent = clCreateUserEvent(ctsContext.get(), nullptr);
        sycl::event event(clEvent, ctsContext);

        cl_event interopEvent = event.get();
        if (interopEvent != clEvent) {
          FAIL(log, "event was not constructed correctly");
        }
      }

    } catch (const sycl::exception &e) {
      log_exception(log, e);
      std::string errorMsg =
          "a SYCL exception was caught: " + std::string(e.what());
      FAIL(log, errorMsg.c_str());
    }
  }
};

// register this test with the test_collection
util::test_proxy<TEST_NAME> proxy;

} /* namespace opencl_interop_constructors__ */
