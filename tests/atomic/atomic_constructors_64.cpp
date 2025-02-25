/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Copyright:	(c) 2018 by Codeplay Software LTD. All Rights Reserved.
//
*******************************************************************************/

#include "../common/common.h"
#include "atomic_constructors_common.h"

#include <climits>
#include <string>

#define TEST_NAME atomic_constructors_64

namespace TEST_NAMESPACE {

using namespace atomic_constructors_common;
using namespace sycl_cts;

/** Check the api for sycl::atomic
 */
class TEST_NAME : public util::test_base {
 public:
  /** Return information about this test
   */
  virtual void get_info(test_base::info &out) const override {
    set_test_info(out, TOSTRING(TEST_NAME), TEST_FILE);
  }

  template <typename T>
  void check_atomics_for_type(util::logger &log, sycl::queue testQueue) {
    /** Check atomic constructors for sycl::target::device
     */
    check_atomics<T, sycl::target::device>{}(log, testQueue);

    /** Check atomic constructors for sycl::target::local
     */
    check_atomics<T, sycl::target::local>{}(log, testQueue);
  }

  /** Execute the test
   */
  virtual void run(util::logger &log) override {
    try {
      auto testQueue = util::get_cts_object::queue();
      auto testDevice = testQueue.get_device();

      /** Check atomics for supported types
       */
      if (testDevice.has(sycl::aspect::atomic64)) {
        if constexpr (sizeof(long) * CHAR_BIT == 64 /*bits*/) {
          check_atomics_for_type<long>(log, testQueue);
          check_atomics_for_type<unsigned long>(log, testQueue);
        }
        check_atomics_for_type<long long>(log, testQueue);
        check_atomics_for_type<unsigned long long>(log, testQueue);
      }

      testQueue.wait_and_throw();

    } catch (const sycl::exception &e) {
      log_exception(log, e);
      auto errorMsg = std::string("a SYCL exception was caught: ") + e.what();
      FAIL(log, errorMsg);
    }
  }
};

// Construction of this proxy will register the above test
util::test_proxy<TEST_NAME> proxy;

}  // namespace TEST_NAMESPACE
