/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Copyright:	(c) 2018 by Codeplay Software LTD. All Rights Reserved.
//
*******************************************************************************/

#define TEST_NAME accessor_constructors_fp64

#include "../common/common.h"
#include "accessor_constructors_buffer_utility.h"
#include "accessor_constructors_image_utility.h"
#include "accessor_constructors_local_utility.h"
#include "accessor_types_fp64.h"

namespace TEST_NAMESPACE {

/** tests the constructors for sycl::accessor
 */
class TEST_NAME : public util::test_base {
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
      auto queue = util::get_cts_object::queue();

      check_all_types_fp64<buffer_accessor_type>::run(queue, log);
      check_all_types_fp64<buffer_accessor_type_placeholder>::run(queue, log);
      check_all_types_fp64<local_accessor_all_dims>::run(queue, log);

      queue.wait_and_throw();
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

}  // namespace TEST_NAMESPACE
