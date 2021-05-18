load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "decaf",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["src/*.h"]),
)

cc_test(
  name = "test",
  size = "small",
  srcs = ["test/TestGeneration.test.cpp"],
  deps = ["@com_google_googletest//:gtest_main", "decaf"],
)
