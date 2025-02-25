/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Copyright:	(c) 2017 by Codeplay Software LTD. All Rights Reserved.
//
*******************************************************************************/

#include "../common/common.h"

#define TEST_NAME device_info

namespace device_info__ {

using namespace sycl_cts;

/** tests the info for sycl::device
 */
class TEST_NAME : public util::test_base {
 public:
  /** return information about this test
   */
  void get_info(test_base::info &out) const override {
    set_test_info(out, TOSTRING(TEST_NAME), TEST_FILE);
  }

  /** execute the test
   */
  void run(util::logger &log) override {
    try {
      /** check info::device
       */
      check_enum_class_value(sycl::info::device::device_type);
      check_enum_class_value(sycl::info::device::vendor_id);
      check_enum_class_value(sycl::info::device::max_compute_units);
      check_enum_class_value(sycl::info::device::max_work_item_dimensions);
      check_enum_class_value(sycl::info::device::max_work_item_sizes);
      check_enum_class_value(sycl::info::device::max_work_group_size);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_char);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_short);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_int);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_long);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_float);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_double);
      check_enum_class_value(
          sycl::info::device::preferred_vector_width_half);
      check_enum_class_value(sycl::info::device::native_vector_width_char);
      check_enum_class_value(sycl::info::device::native_vector_width_short);
      check_enum_class_value(sycl::info::device::native_vector_width_int);
      check_enum_class_value(sycl::info::device::native_vector_width_long);
      check_enum_class_value(sycl::info::device::native_vector_width_float);
      check_enum_class_value(
          sycl::info::device::native_vector_width_double);
      check_enum_class_value(sycl::info::device::native_vector_width_half);
      check_enum_class_value(sycl::info::device::max_clock_frequency);
      check_enum_class_value(sycl::info::device::address_bits);
      check_enum_class_value(sycl::info::device::max_mem_alloc_size);
      check_enum_class_value(sycl::info::device::image_support);
      check_enum_class_value(sycl::info::device::max_read_image_args);
      check_enum_class_value(sycl::info::device::max_write_image_args);
      check_enum_class_value(sycl::info::device::image2d_max_height);
      check_enum_class_value(sycl::info::device::image2d_max_width);
      check_enum_class_value(sycl::info::device::image3d_max_height);
      check_enum_class_value(sycl::info::device::image3d_max_width);
      check_enum_class_value(sycl::info::device::image3d_max_depth);
      check_enum_class_value(sycl::info::device::image_max_buffer_size);
      check_enum_class_value(sycl::info::device::image_max_array_size);
      check_enum_class_value(sycl::info::device::max_samplers);
      check_enum_class_value(sycl::info::device::max_parameter_size);
      check_enum_class_value(sycl::info::device::mem_base_addr_align);
      check_enum_class_value(sycl::info::device::half_fp_config);
      check_enum_class_value(sycl::info::device::single_fp_config);
      check_enum_class_value(sycl::info::device::double_fp_config);
      check_enum_class_value(sycl::info::device::global_mem_cache_type);
      check_enum_class_value(
          sycl::info::device::global_mem_cache_line_size);
      check_enum_class_value(sycl::info::device::global_mem_cache_size);
      check_enum_class_value(sycl::info::device::global_mem_size);
      check_enum_class_value(sycl::info::device::max_constant_buffer_size);
      check_enum_class_value(sycl::info::device::max_constant_args);
      check_enum_class_value(sycl::info::device::local_mem_type);
      check_enum_class_value(sycl::info::device::local_mem_size);
      check_enum_class_value(sycl::info::device::error_correction_support);
      check_enum_class_value(sycl::info::device::host_unified_memory);
      check_enum_class_value(
          sycl::info::device::profiling_timer_resolution);
      check_enum_class_value(sycl::info::device::is_endian_little);
      check_enum_class_value(sycl::info::device::is_available);
      check_enum_class_value(sycl::info::device::is_compiler_available);
      check_enum_class_value(sycl::info::device::is_linker_available);
      check_enum_class_value(sycl::info::device::execution_capabilities);
      check_enum_class_value(sycl::info::device::queue_profiling);
      check_enum_class_value(sycl::info::device::built_in_kernels);
      check_enum_class_value(sycl::info::device::platform);
      check_enum_class_value(sycl::info::device::name);
      check_enum_class_value(sycl::info::device::vendor);
      check_enum_class_value(sycl::info::device::driver_version);
      check_enum_class_value(sycl::info::device::profile);
      check_enum_class_value(sycl::info::device::version);
      check_enum_class_value(sycl::info::device::opencl_c_version);
      check_enum_class_value(sycl::info::device::extensions);
      check_enum_class_value(sycl::info::device::printf_buffer_size);
      check_enum_class_value(
          sycl::info::device::preferred_interop_user_sync);
      check_enum_class_value(sycl::info::device::parent_device);
      check_enum_class_value(sycl::info::device::partition_max_sub_devices);
      check_enum_class_value(sycl::info::device::partition_properties);
      check_enum_class_value(
          sycl::info::device::partition_affinity_domains);
      check_enum_class_value(sycl::info::device::partition_type_property);
      check_enum_class_value(
          sycl::info::device::partition_type_affinity_domain);
      check_enum_class_value(sycl::info::device::reference_count);

      /** check info::device_type
       */
      check_enum_class_value(sycl::info::device_type::cpu);
      check_enum_class_value(sycl::info::device_type::gpu);
      check_enum_class_value(sycl::info::device_type::accelerator);
      check_enum_class_value(sycl::info::device_type::custom);
      check_enum_class_value(sycl::info::device_type::automatic);
      check_enum_class_value(sycl::info::device_type::host);
      check_enum_class_value(sycl::info::device_type::all);

      /** check info::partion_property
       */
      check_enum_class_value(sycl::info::partition_property::no_partition);
      check_enum_class_value(
          sycl::info::partition_property::partition_equally);
      check_enum_class_value(
          sycl::info::partition_property::partition_by_counts);
      check_enum_class_value(
          sycl::info::partition_property::partition_by_affinity_domain);

      /** check info::affinity_domain
       */
      check_enum_class_value(
          sycl::info::partition_affinity_domain::not_applicable);
      check_enum_class_value(sycl::info::partition_affinity_domain::numa);
      check_enum_class_value(
          sycl::info::partition_affinity_domain::L1_cache);
      check_enum_class_value(
          sycl::info::partition_affinity_domain::L2_cache);
      check_enum_class_value(
          sycl::info::partition_affinity_domain::L3_cache);
      check_enum_class_value(
          sycl::info::partition_affinity_domain::L4_cache);
      check_enum_class_value(
          sycl::info::partition_affinity_domain::next_partitionable);

      /** check info::local_mem_type
       */
      check_enum_class_value(sycl::info::local_mem_type::none);
      check_enum_class_value(sycl::info::local_mem_type::local);
      check_enum_class_value(sycl::info::local_mem_type::global);

      /** check info::fp_config
       */
      check_enum_class_value(sycl::info::fp_config::denorm);
      check_enum_class_value(sycl::info::fp_config::inf_nan);
      check_enum_class_value(sycl::info::fp_config::round_to_nearest);
      check_enum_class_value(sycl::info::fp_config::round_to_zero);
      check_enum_class_value(sycl::info::fp_config::round_to_inf);
      check_enum_class_value(sycl::info::fp_config::fma);
      check_enum_class_value(
          sycl::info::fp_config::correctly_rounded_divide_sqrt);
      check_enum_class_value(sycl::info::fp_config::soft_float);

      /** check global_mem_cache_type
       */
      check_enum_class_value(sycl::info::global_mem_cache_type::none);
      check_enum_class_value(sycl::info::global_mem_cache_type::read_only);
      check_enum_class_value(sycl::info::global_mem_cache_type::read_write);

      /** check execution_capability
       */
      check_enum_class_value(sycl::info::execution_capability::exec_kernel);
      check_enum_class_value(
          sycl::info::execution_capability::exec_native_kernel);

      /** check get_info parameters
       */
      {
        cts_selector selector;
        auto dev = util::get_cts_object::device(selector);
        check_get_info_param<sycl::info::device,
                             sycl::info::device_type,
                             sycl::info::device::device_type>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::vendor_id>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_compute_units>(log,
                                                                        dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_work_item_dimensions>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::id<3>,
                             sycl::info::device::max_work_item_sizes>(log,
                                                                          dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::max_work_group_size>(log,
                                                                          dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_char>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_short>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_int>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_long>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_float>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_double>(log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::preferred_vector_width_half>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_char>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_short>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_int>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_long>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_float>(
            log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::native_vector_width_double>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::native_vector_width_half>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_clock_frequency>(log,
                                                                          dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::address_bits>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_ulong,
                             sycl::info::device::max_mem_alloc_size>(log,
                                                                         dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::image_support>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_read_image_args>(log,
                                                                          dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_write_image_args>(log,
                                                                           dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image2d_max_height>(log,
                                                                         dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image2d_max_width>(log,
                                                                        dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image3d_max_height>(log,
                                                                         dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image3d_max_width>(log,
                                                                        dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image3d_max_depth>(log,
                                                                        dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image_max_buffer_size>(
            log, dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::image_max_array_size>(log,
                                                                           dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_samplers>(log, dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::max_parameter_size>(log,
                                                                         dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::mem_base_addr_align>(log,
                                                                          dev);
        check_get_info_param<sycl::info::device,
                             std::vector<sycl::info::fp_config>,
                             sycl::info::device::half_fp_config>(log, dev);
        check_get_info_param<sycl::info::device,
                             std::vector<sycl::info::fp_config>,
                             sycl::info::device::single_fp_config>(log,
                                                                       dev);
        check_get_info_param<sycl::info::device,
                             std::vector<sycl::info::fp_config>,
                             sycl::info::device::double_fp_config>(log,
                                                                       dev);
        check_get_info_param<sycl::info::device,
                             sycl::info::global_mem_cache_type,
                             sycl::info::device::global_mem_cache_type>(
            log, dev);
        check_get_info_param<
            sycl::info::device, sycl::cl_uint,
            sycl::info::device::global_mem_cache_line_size>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_ulong,
                             sycl::info::device::global_mem_cache_size>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_ulong,
                             sycl::info::device::global_mem_size>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_ulong,
                             sycl::info::device::max_constant_buffer_size>(
            log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::max_constant_args>(log,
                                                                        dev);
        check_get_info_param<sycl::info::device,
                             sycl::info::local_mem_type,
                             sycl::info::device::local_mem_type>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_ulong,
                             sycl::info::device::local_mem_size>(log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::error_correction_support>(
            log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::host_unified_memory>(log,
                                                                          dev);
        check_get_info_param<
            sycl::info::device, size_t,
            sycl::info::device::profiling_timer_resolution>(log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::is_endian_little>(log,
                                                                       dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::is_available>(log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::is_compiler_available>(
            log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::is_linker_available>(log,
                                                                          dev);
        check_get_info_param<
            sycl::info::device,
            std::vector<sycl::info::execution_capability>,
            sycl::info::device::execution_capabilities>(log, dev);
        check_get_info_param<sycl::info::device, bool,
                             sycl::info::device::queue_profiling>(log, dev);
        check_get_info_param<sycl::info::device,
                             std::vector<std::string>,
                             sycl::info::device::built_in_kernels>(log,
                                                                       dev);
        check_get_info_param<sycl::info::device, sycl::platform,
                             sycl::info::device::platform>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::name>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::vendor>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::driver_version>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::profile>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::version>(log, dev);
        check_get_info_param<sycl::info::device, std::string,
                             sycl::info::device::opencl_c_version>(log,
                                                                       dev);
        check_get_info_param<sycl::info::device,
                             std::vector<std::string>,
                             sycl::info::device::extensions>(log, dev);
        check_get_info_param<sycl::info::device, size_t,
                             sycl::info::device::printf_buffer_size>(log,
                                                                         dev);
        check_get_info_param<
            sycl::info::device, bool,
            sycl::info::device::preferred_interop_user_sync>(log, dev);
        auto SupportedProperties =
            dev.get_info<sycl::info::device::partition_properties>();
        if (std::find(SupportedProperties.begin(), SupportedProperties.end(),
                      sycl::info::partition_property::partition_equally) !=
            SupportedProperties.end()) {

          auto sub_device_partition_equal = dev.create_sub_devices<
              sycl::info::partition_property::partition_equally>(1);

          check_get_info_param<sycl::info::device, sycl::device,
                               sycl::info::device::parent_device>(
              log, sub_device_partition_equal[0]);
        }
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::partition_max_sub_devices>(
            log, dev);
        check_get_info_param<
            sycl::info::device,
            std::vector<sycl::info::partition_property>,
            sycl::info::device::partition_properties>(log, dev);
        check_get_info_param<
            sycl::info::device,
            std::vector<sycl::info::partition_affinity_domain>,
            sycl::info::device::partition_affinity_domains>(log, dev);
        check_get_info_param<sycl::info::device,
                             sycl::info::partition_property,
                             sycl::info::device::partition_type_property>(
            log, dev);
        check_get_info_param<
            sycl::info::device, sycl::info::partition_affinity_domain,
            sycl::info::device::partition_type_affinity_domain>(log, dev);
        check_get_info_param<sycl::info::device, sycl::cl_uint,
                             sycl::info::device::reference_count>(log, dev);
      }

    } catch (const sycl::exception &e) {
      log_exception(log, e);
      std::string errorMsg =
          "a SYCL exception was caught: " + std::string(e.what());
      FAIL(log, errorMsg.c_str());
    }
  }
};

// construction of this proxy will register the above test
util::test_proxy<TEST_NAME> proxy;

} /* namespace device_info__ */
