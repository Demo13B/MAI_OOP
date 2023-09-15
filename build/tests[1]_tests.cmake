add_test([=[Suite1.Test1]=]  /Users/timursalihov/OOP_MAI/LW1/build/tests [==[--gtest_filter=Suite1.Test1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Suite1.Test1]=]  PROPERTIES WORKING_DIRECTORY /Users/timursalihov/OOP_MAI/LW1/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  tests_TESTS Suite1.Test1)
