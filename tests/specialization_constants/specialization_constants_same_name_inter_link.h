/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for specialization constants with same name and internal
//  linkage
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_SPEC_CONST_SAME_NAME_INTER_LINK_H
#define __SYCLCTS_TESTS_SPEC_CONST_SAME_NAME_INTER_LINK_H

#include "../common/common.h"
#include "../common/once_per_unit.h"
#include "specialization_constants_common.h"
#include "specialization_constants_same_name_inter_link_helper.h"

namespace specialization_constants_same_name_inter_link {
using namespace sycl_cts;
using namespace get_spec_const;

template <typename T, int tu_num, typename via_kb>
struct sc_sn_il_kernel;

/** @brief Test suite for specialization constants with same name and internal
 *         linkage
 *  @tparam T Underlying data type, required to specify an actual instance of
 *            the specialization constant
 *  @tparam TestConfig helper class with default values depending on TU number
 *  @tparam via_kb std::true(false)_type like helper type to separate tests
 *                 with or without a kernel_bundle
 */
template <typename T, typename TestConfig, typename via_kb>
class check_specialization_constants_same_name_inter_link_for_type {
 public:
  void operator()(util::logger &log, const std::string &type_name) try {
    {
      using kernel_name = sc_sn_il_kernel<T, TestConfig::tu, via_kb>;
      constexpr auto &spec_const_il = sc_same_name_inter_link<T, via_kb>;
      auto queue = util::get_cts_object::queue();
      const sycl::context ctx = queue.get_context();
      const sycl::device dev = queue.get_device();

      if constexpr (via_kb::value) {
        if (!dev.has(sycl::aspect::online_compiler)) {
          once_per_unit::log(log, "Device does not support online compilation");
          return;
        }
      }
      sycl::range<1> range(1);
      T def_value{get_init_value_helper<T>(0)};
      T ref_def_value{get_init_value_helper<T>(0)};
      T result{get_init_value_helper<T>(0)};
      T ref{get_init_value_helper<T>(0)};
      {
        // Setting ref values according to TU number
        fill_init_values(ref_def_value, TestConfig::tu);
        fill_init_values(ref, TestConfig::ref_val);
        sycl::buffer<T, 1> result_buffer(&result, range);
        queue.submit([&](sycl::handler &cgh) {
          auto res_acc =
              result_buffer.template get_access<sycl::access_mode::write>(cgh);
          // Via kernel_bundle
          if constexpr (via_kb::value) {
            auto kernelId = sycl::get_kernel_id<kernel_name>();
            sycl::kernel_bundle k_bundle =
                sycl::get_kernel_bundle<sycl::bundle_state::input>(ctx, {dev},
                                                                   {kernelId});
            if (!k_bundle.has_kernel(kernelId)) {
              log.note("kernel_bundle doesn't contain target kernel for " +
                       type_name_string<T>::get(type_name) + " (skipped)");
              return;
            }
            // Get default value to make sure the spec const is valid
            def_value =
                k_bundle.template get_specialization_constant<spec_const_il>();

            k_bundle.template set_specialization_constant<spec_const_il>(ref);
            auto exec_bundle = sycl::build(k_bundle);
            cgh.use_kernel_bundle(exec_bundle);
            cgh.single_task<kernel_name>([=](sycl::kernel_handler h) {
              res_acc[0] = h.get_specialization_constant<spec_const_il>();
            });
          } else {
            // No kernel_bundle
            // Get default value to make sure the spec const is valid
            def_value = cgh.get_specialization_constant<spec_const_il>();

            cgh.set_specialization_constant<spec_const_il>(ref);
            cgh.single_task<kernel_name>([=](sycl::kernel_handler h) {
              res_acc[0] = h.get_specialization_constant<spec_const_il>();
            });
          }
        });
      }
      if (!check_equal_values(ref_def_value, def_value))
        FAIL(log, "Wrong linked spec const; (translation unit " +
                      std::to_string(TestConfig::tu) + ") for " +
                      type_name_string<T>::get(type_name));
      if (!check_equal_values(ref, result))
        FAIL(log, "Wrong returned value; (translation unit " +
                      std::to_string(TestConfig::tu) + ") for " +
                      type_name_string<T>::get(type_name));
    }
  } catch (...) {
    std::string message{"translation unit " + std::to_string(TestConfig::tu) +
                        " for " + type_name_string<T>::get(type_name)};
    log.note(message);
    throw;
  }
};

// Test function for core tests
template <int tu_num, typename via_kb>
static void sc_run_test_core(util::logger &log) {
  using namespace spec_const_help;
  try {
#ifndef SYCL_CTS_FULL_CONFORMANCE
    for_all_types<check_specialization_constants_same_name_inter_link_for_type,
                  sc_sn_il_config<tu_num>, via_kb>(
        get_spec_const::testing_types::types, log);
#else
    for_all_types_vectors_marray<
        check_specialization_constants_same_name_inter_link_for_type,
        sc_sn_il_config<tu_num>, via_kb>(get_spec_const::testing_types::types,
                                         log);
#endif
    for_all_types<check_specialization_constants_same_name_inter_link_for_type,
                  sc_sn_il_config<tu_num>, via_kb>(
        get_spec_const::testing_types::composite_types, log);

  } catch (const sycl::exception &e) {
    log_exception(log, e);
    std::string errorMsg =
        "a SYCL exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  } catch (const std::exception &e) {
    std::string errorMsg = "an exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  }
}

// Test function for fp16 tests
template <int tu_num, typename via_kb>
static void sc_run_test_fp16(util::logger &log) {
  using namespace spec_const_help;
  try {
    auto queue = util::get_cts_object::queue();
    if (!queue.get_device().has(sycl::aspect::fp16)) {
      log.note(
          "Device does not support half precision floating point "
          "operations");
      return;
    }
#ifndef SYCL_CTS_FULL_CONFORMANCE
    check_specialization_constants_same_name_inter_link_for_type<
        sycl::half, sc_sn_il_config<tu_num>, via_kb>
        fp16_test{};
    fp16_test(log, "sycl::half");
#else
    for_type_vectors_marray<
        check_specialization_constants_same_name_inter_link_for_type,
        sycl::half, sc_sn_il_config<tu_num>, via_kb>(log, "sycl::half");
#endif

  } catch (const sycl::exception &e) {
    log_exception(log, e);
    std::string errorMsg =
        "a SYCL exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  } catch (const std::exception &e) {
    std::string errorMsg = "an exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  }
}

// Test function for fp64 tests
template <int tu_num, typename via_kb>
static void sc_run_test_fp64(util::logger &log) {
  using namespace spec_const_help;
  try {
    auto queue = util::get_cts_object::queue();
    if (!queue.get_device().has(sycl::aspect::fp64)) {
      log.note(
          "Device does not support double precision floating point "
          "operations");
      return;
    }
#ifndef SYCL_CTS_FULL_CONFORMANCE
    check_specialization_constants_same_name_inter_link_for_type<
        double, sc_sn_il_config<tu_num>, via_kb>
        fp64_test{};
    fp64_test(log, "double");
#else
    for_type_vectors_marray<
        check_specialization_constants_same_name_inter_link_for_type, double,
        sc_sn_il_config<tu_num>, via_kb>(log, "double");
#endif

  } catch (const sycl::exception &e) {
    log_exception(log, e);
    std::string errorMsg =
        "a SYCL exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  } catch (const std::exception &e) {
    std::string errorMsg = "an exception was caught: " + std::string(e.what());
    FAIL(log, errorMsg);
  }
}

}  // namespace specialization_constants_same_name_inter_link

#endif  // __SYCLCTS_TESTS_SPEC_CONST_SAME_NAME_INTER_LINK_H
